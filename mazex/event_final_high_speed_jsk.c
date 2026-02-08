// ============================================================================
// DEBUG CONFIGURATION 
// ============================================================================
#define DEBUG_ENABLED false
#define DEBUG_PRINT(x) if(DEBUG_ENABLED) Serial.print(x)
#define DEBUG_PRINTLN(x) if(DEBUG_ENABLED) Serial.println(x)

// ============================================================================
// PIN DEFINITIONS
// ============================================================================

// Motor A (Left Motor)
#define PWMA 25
#define AIN1 26
#define AIN2 27

// Motor B (Right Motor)
#define PWMB 14
#define BIN1 32
#define BIN2 13

// Motor Driver Standby
#define STBY 33

// THREE ULTRASONIC SENSORS (No Servo!)
// Left Sensor
#define TRIG_LEFT 18
#define ECHO_LEFT 19

// Center Sensor
#define TRIG_CENTER 21
#define ECHO_CENTER 22

// Right Sensor
#define TRIG_RIGHT 4
#define ECHO_RIGHT 5

// IR Sensors (Active LOW)
#define IR_LEFT 34
#define IR_RIGHT 35

// ============================================================================
// PWM CONFIGURATION
// ============================================================================
#define PWM_FREQ 12000
#define PWM_RESOLUTION 8

// ============================================================================
// TUNABLE PARAMETERS
// ============================================================================

// Motor Speeds

#define MOTOR_SPEED_L 235.53
#define MOTOR_SPEED_R 220.32
#define TURN_SPEED 245
#define REVERSE_SPEED_L 210.25
#define REVERSE_SPEED_R 196.2

// Distance Thresholds (cm)
#define STOP_DISTANCE 23
#define REVERSE_DISTANCE 11
#define MIN_SAFE_DISTANCE 19

// Timing
#define TURN_90_TIME 150
#define TURN_IR 63
#define REVERSE_TIME 120
#define CHECK_INTERVAL 120

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

unsigned long lastCheck = 0;

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  Serial.begin(115200);
  delay(700);
  
  DEBUG_PRINTLN("\n========================================");
  DEBUG_PRINTLN("ESP32 Maze Solver - 3 ULTRASONIC VERSION");
  DEBUG_PRINTLN("No Servo - Simultaneous 3-Way Scanning");
  DEBUG_PRINTLN("========================================\n");
  
  // Motor pins
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  // Motor PWM
  ledcAttach(PWMA, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(PWMB, PWM_FREQ, PWM_RESOLUTION);
  digitalWrite(STBY, HIGH);
  DEBUG_PRINTLN("[INIT] Motors ready");
  
  // LEFT Ultrasonic Sensor
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  digitalWrite(TRIG_LEFT, LOW);
  DEBUG_PRINTLN("[INIT] LEFT ultrasonic ready");
  
  // CENTER Ultrasonic Sensor
  pinMode(TRIG_CENTER, OUTPUT);
  pinMode(ECHO_CENTER, INPUT);
  digitalWrite(TRIG_CENTER, LOW);
  DEBUG_PRINTLN("[INIT] CENTER ultrasonic ready");
  
  // RIGHT Ultrasonic Sensor
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  digitalWrite(TRIG_RIGHT, LOW);
  DEBUG_PRINTLN("[INIT] RIGHT ultrasonic ready");
  
  // IR sensors
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  DEBUG_PRINTLN("[INIT] IR sensors ready");
  
  // Test all sensors
  DEBUG_PRINTLN("\n[TEST] Testing all 3 ultrasonic sensors:");
  float testLeft = measureDistance(TRIG_LEFT, ECHO_LEFT);
  float testCenter = measureDistance(TRIG_CENTER, ECHO_CENTER);
  float testRight = measureDistance(TRIG_RIGHT, ECHO_RIGHT);
  
  DEBUG_PRINT("  LEFT: ");
  DEBUG_PRINT(testLeft);
  DEBUG_PRINTLN(" cm");
  
  DEBUG_PRINT("  CENTER: ");
  DEBUG_PRINT(testCenter);
  DEBUG_PRINTLN(" cm");
  
  DEBUG_PRINT("  RIGHT: ");
  DEBUG_PRINT(testRight);
  DEBUG_PRINTLN(" cm");
  
  DEBUG_PRINTLN("[TEST] Sensor test complete!\n");
  
  DEBUG_PRINTLN("[READY] Starting in 1 seconds...\n");
  delay(1000);
  
  // START MOVING FORWARD IMMEDIATELY
  startForward();
}

// ============================================================================
// MAIN LOOP - SIMPLIFIED CONTINUOUS MOVEMENT
// ============================================================================

void loop() {
  // Read IR sensors NOW (only when we need to make decision)
  bool leftWall = !digitalRead(IR_LEFT);
  bool rightWall = !digitalRead(IR_RIGHT);
  
  // Check front distance periodically WITHOUT stopping motors
  if (millis() - lastCheck >= CHECK_INTERVAL) {
    lastCheck = millis();
    
    float distance = measureDistance(TRIG_CENTER, ECHO_CENTER);
    
    #if DEBUG_ENABLED
    Serial.print("[MOVING] Front distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    #endif

    // IR SENSOR LOGIC (your original logic preserved)
    if (rightWall != 0 && leftWall != 0) {
      DEBUG_PRINTLN("\n[ALERT] Both walls detected! Reversing...");
      stopMotors();
      delay(30);
      
      // Reverse
      reverseMotors();
      delay(REVERSE_TIME); 
      stopMotors();
      delay(50);
      
      DEBUG_PRINTLN("[REVERSE] Complete, now scanning...");
      
    }
    else if (rightWall != 0) {
      DEBUG_PRINT(" | Right: ");
      DEBUG_PRINTLN(rightWall ? "WALL" : "OPEN");
      
      DEBUG_PRINTLN("[MOTOR] Turning RIGHT 90°");
      
      digitalWrite(AIN1,HIGH );
      digitalWrite(AIN2, LOW );
      ledcWrite(PWMA, 100 );
      
      digitalWrite(BIN1,LOW );
      digitalWrite(BIN2,HIGH);
      ledcWrite(PWMB, TURN_SPEED);
      
      delay(TURN_IR);
      startForward();
      delay(50);
      
    }
    else if (leftWall != 0) {
      DEBUG_PRINT("[IR] Left: ");
      DEBUG_PRINT(leftWall ? "WALL" : "OPEN");
      
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      ledcWrite(PWMA, 100 );
      
      digitalWrite(BIN1,HIGH );
      digitalWrite(BIN2, LOW);
      ledcWrite(PWMB,TURN_SPEED );
      
      delay(TURN_IR);
      startForward();
      delay(50);
      
    }
    
    // ===== ONLY STOP WHEN OBSTACLE DETECTED =====
    if (distance > 0 && distance < STOP_DISTANCE) {
      
      // CASE 1: TOO CLOSE - Reverse first
      if (distance < REVERSE_DISTANCE) {
        DEBUG_PRINTLN("\n[ALERT] TOO CLOSE! Reversing...");
        stopMotors();
        delay(50);
        
        // Reverse
        reverseMotors();
        delay(REVERSE_TIME);
        stopMotors();
        delay(50);
        
        DEBUG_PRINTLN("[REVERSE] Complete, now scanning...");
      }
      // CASE 2: Normal obstacle - just stop
      else {
        DEBUG_PRINTLN("\n[OBSTACLE] Detected, stopping...");
        stopMotors();
        delay(150);
      }
      
      // SCAN ALL 3 DIRECTIONS SIMULTANEOUSLY
      float distances[3];
      scanAllDirections(distances);
      
      // Make decision based on BOTH scan results AND IR sensors
      makeDecision(distances, leftWall, rightWall);
      
      // Resume forward movement immediately
      delay(150);
      startForward();
    }
  }
  
  // Motors keep running continuously - no other logic here!
}

// ============================================================================
// MOTOR CONTROL
// ============================================================================

void startForward() {
  DEBUG_PRINTLN("[MOTOR] Starting CONTINUOUS forward movement\n");
  
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  ledcWrite(PWMA, MOTOR_SPEED_L);
  
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  ledcWrite(PWMB, MOTOR_SPEED_R);
}

void stopMotors() {
  DEBUG_PRINTLN("[MOTOR] Stopping");
  ledcWrite(PWMA, 0);
  ledcWrite(PWMB, 0);
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void reverseMotors() {
  DEBUG_PRINTLN("[MOTOR] Reversing");
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  ledcWrite(PWMA, REVERSE_SPEED_L);
  
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  ledcWrite(PWMB, REVERSE_SPEED_R);
}

void turnLeft() {
  DEBUG_PRINTLN("[MOTOR] Turning LEFT 90°");
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  ledcWrite(PWMA, TURN_SPEED);
  
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  ledcWrite(PWMB, TURN_SPEED);
  
  delay(TURN_90_TIME);
  stopMotors();
  delay(100);
}

void turnRight() {
  DEBUG_PRINTLN("[MOTOR] Turning RIGHT 90°");
  
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  ledcWrite(PWMA, TURN_SPEED);
  
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  ledcWrite(PWMB, TURN_SPEED);
  
  delay(TURN_90_TIME);
  stopMotors();
  delay(100);
}

void turnAround() {
  DEBUG_PRINTLN("[MOTOR] U-TURN (180°)");
  
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  ledcWrite(PWMA, TURN_SPEED);
  
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  ledcWrite(PWMB, TURN_SPEED);
  
  delay(TURN_90_TIME * 2);
  stopMotors();
  delay(100);
}

// ============================================================================
// SENSOR FUNCTIONS - IMPROVED WITH MULTIPLE READINGS
// ============================================================================

// Helper function to take single raw reading
float getSingleReading(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 10000);
  
  if (duration == 0) {
    return 999;   // treat as OPEN space
  }

  float distance = (duration / 2.0) * 0.0343;

  if (distance <= 0 || distance > 400) {
    return 400;   // invalid or too far
  }

  return distance;
}

// Helper function to sort 3 values for median calculation
void sortThree(float arr[3]) {
  if (arr[0] > arr[1]) {
    float temp = arr[0];
    arr[0] = arr[1];
    arr[1] = temp;
  }
  if (arr[1] > arr[2]) {
    float temp = arr[1];
    arr[1] = arr[2];
    arr[2] = temp;
  }
  if (arr[0] > arr[1]) {
    float temp = arr[0];
    arr[0] = arr[1];
    arr[1] = temp;
  }
}

// Main distance measurement function with 3 readings and median filter
float measureDistance(int trigPin, int echoPin) {
  float readings[3];
  
  // Take 3 readings
  for(int i = 0; i < 3; i++) {
    readings[i] = getSingleReading(trigPin, echoPin);
    if(i < 2) {  // Don't delay after last reading
      delay(10);  // Small delay between readings
    }
  }
  
  // Sort and return median (middle value)
  sortThree(readings);
  
  #if DEBUG_ENABLED
  Serial.print("    [Readings: ");
  Serial.print(readings[0]);
  Serial.print(", ");
  Serial.print(readings[1]);
  Serial.print(", ");
  Serial.print(readings[2]);
  Serial.print(" → Median: ");
  Serial.print(readings[1]);
  Serial.println("]");
  #endif
  
  return readings[1];  // Return median value
}

void scanAllDirections(float distances[3]) {
  DEBUG_PRINTLN("\n[SCAN] ========== 3-WAY SCAN (SIMULTANEOUS) ==========");
  
  // Small delay between sensor readings to avoid interference
  delay(60);
  
  // Scan LEFT sensor (now takes 3 readings internally)
  DEBUG_PRINTLN("[SCAN] Reading LEFT sensor (3 samples)...");
  distances[0] = measureDistance(TRIG_LEFT, ECHO_LEFT);
  DEBUG_PRINT("  Final Distance: ");
  DEBUG_PRINT(distances[0]);
  DEBUG_PRINTLN(" cm");
  
  delay(60);  // Small delay to prevent ultrasonic interference
  
  // Scan CENTER sensor (now takes 3 readings internally)
  DEBUG_PRINTLN("[SCAN] Reading CENTER sensor (3 samples)...");
  distances[1] = measureDistance(TRIG_CENTER, ECHO_CENTER);
  DEBUG_PRINT("  Final Distance: ");
  DEBUG_PRINT(distances[1]);
  DEBUG_PRINTLN(" cm");
  
  delay(60);  // Small delay to prevent ultrasonic interference
  
  // Scan RIGHT sensor (now takes 3 readings internally)
  DEBUG_PRINTLN("[SCAN] Reading RIGHT sensor (3 samples)...");
  distances[2] = measureDistance(TRIG_RIGHT, ECHO_RIGHT);
  DEBUG_PRINT("  Final Distance: ");
  DEBUG_PRINT(distances[2]);
  DEBUG_PRINTLN(" cm");
  
  DEBUG_PRINTLN("[SCAN] ===================================\n");
}

// ============================================================================
// DECISION LOGIC - YOUR MAX DISTANCE LOGIC (PRESERVED)
// ============================================================================

void makeDecision(float distances[3], bool leftWall, bool rightWall) {
  float leftDist = distances[0];
  float centerDist = distances[1];
  float rightDist = distances[2];
  float max = 0;

  // Find maximum distance (YOUR LOGIC - UNCHANGED)
  for(int i = 0; i < 3; i++) {
    if(max <= distances[i]) {
      max = distances[i];
    }
  }
  
  DEBUG_PRINTLN("[DECISION] Analyzing paths...");
  DEBUG_PRINT("  Left: ");
  DEBUG_PRINT(leftDist);
  DEBUG_PRINT(" cm | Center: ");
  DEBUG_PRINT(centerDist);
  DEBUG_PRINT(" cm | Right: ");
  DEBUG_PRINT(rightDist);
  DEBUG_PRINTLN(" cm");
  
  DEBUG_PRINT("  MAX distance: ");
  DEBUG_PRINT(max);
  DEBUG_PRINTLN(" cm");
  
  DEBUG_PRINTLN("\n[DECISION] Checking options in priority order:");
  
  // YOUR ORIGINAL LOGIC (PRESERVED)
  // Option 1: CENTER has max distance
  if (centerDist >= max) {
    DEBUG_PRINTLN("  ✓ CENTER path has MAX distance");
    DEBUG_PRINTLN("[DECISION] → CONTINUE FORWARD\n");
    // No turn needed - will resume forward in loop
  }
  // Option 2: LEFT has max distance
  else if (leftDist >= max) {
    DEBUG_PRINTLN("  ✓ LEFT path has MAX distance");
    DEBUG_PRINTLN("[DECISION] → TURNING RIGHT (to face left path)\n");
    turnRight();  // Your original logic
  }
  // Option 3: RIGHT has max distance
  else if (rightDist >= max) {
    DEBUG_PRINTLN("  ✓ RIGHT path has MAX distance");
    DEBUG_PRINTLN("[DECISION] → TURNING LEFT (to face right path)\n");
    turnLeft();  // Your original logic
  }
  // Option 4: Dead end - all paths blocked
  else {
    DEBUG_PRINTLN("  ✗ All paths blocked - DEAD END");
    DEBUG_PRINTLN("[DECISION] → U-TURN (180°)\n");
    turnAround();
  }
}