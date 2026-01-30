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

// THREE ULTRASONIC SENSORS
#define TRIG_LEFT 18
#define ECHO_LEFT 19
#define TRIG_CENTER 21
#define ECHO_CENTER 22
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
// TUNABLE PARAMETERS - OPTIMIZED FOR ACCURACY
// ============================================================================

// Motor Speeds - CALIBRATED
#define MOTOR_SPEED_L 211.25
#define MOTOR_SPEED_R 195.5
#define TURN_SPEED 220
#define REVERSE_SPEED_L 169
#define REVERSE_SPEED_R 215.05

// Distance Thresholds (cm) - IMPROVED
#define STOP_DISTANCE 20          // Increased for earlier detection
#define REVERSE_DISTANCE 12       
#define MIN_SAFE_DISTANCE 18      
#define WALL_THRESHOLD 12         // NEW: Distance to consider as wall

// CURVE DETECTION - NEW
#define CURVE_DETECTION_DIFF 14    // cm difference between L/R to detect curve
#define GENTLE_CURVE_DIFF 9      // Small difference = gentle curve
#define SHARP_CURVE_DIFF 19       // Large difference = sharp curve

// Speed Adjustments for Curves - NEW
#define CURVE_SPEED_L 185         // Slower speed for curve navigation
#define CURVE_SPEED_R 175
#define GENTLE_CURVE_FACTOR 0.95  // 90% speed
#define SHARP_CURVE_FACTOR 0.80   // 75% speed

// Timing - OPTIMIZED
#define TURN_90_TIME 128
#define TURN_IR 69
#define REVERSE_TIME 120
#define CHECK_INTERVAL 90         // Faster checking (was 130)
#define CURVE_CHECK_INTERVAL 50   // Even faster for curves

// Sensor Filtering - NEW
#define FILTER_SAMPLES 5          // Increased from 3 for better accuracy
#define SENSOR_TIMEOUT 12000      // Increased timeout

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

unsigned long lastCheck = 0;
unsigned long lastCurveCheck = 0;

// Sensor history for better filtering - NEW
float leftHistory[FILTER_SAMPLES] = {0};
float centerHistory[FILTER_SAMPLES] = {0};
float rightHistory[FILTER_SAMPLES] = {0};
int historyIndex = 0;

// Curve detection state - NEW
bool inCurve = false;
int curveDirection = 0; // -1=left, 0=straight, 1=right

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  Serial.begin(115200);
  delay(700);
  
  DEBUG_PRINTLN("\n========================================");
  DEBUG_PRINTLN("ESP32 MAZE SOLVER - HIGH ACCURACY");
  DEBUG_PRINTLN("With Curve Detection & Smooth Navigation");
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
  
  // Ultrasonic Sensors
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  digitalWrite(TRIG_LEFT, LOW);
  
  pinMode(TRIG_CENTER, OUTPUT);
  pinMode(ECHO_CENTER, INPUT);
  digitalWrite(TRIG_CENTER, LOW);
  
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  digitalWrite(TRIG_RIGHT, LOW);
  DEBUG_PRINTLN("[INIT] All ultrasonic sensors ready");
  
  // IR sensors
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  DEBUG_PRINTLN("[INIT] IR sensors ready");
  
  // Calibration - NEW
  DEBUG_PRINTLN("\n[CALIBRATION] Initializing sensor baseline...");
  calibrateSensors();
  
  // Test sensors
  DEBUG_PRINTLN("\n[TEST] Testing all 3 ultrasonic sensors:");
  float testLeft = measureDistanceFiltered(TRIG_LEFT, ECHO_LEFT);
  float testCenter = measureDistanceFiltered(TRIG_CENTER, ECHO_CENTER);
  float testRight = measureDistanceFiltered(TRIG_RIGHT, ECHO_RIGHT);
  
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
  DEBUG_PRINTLN("[READY] Starting in 2 seconds...\n");
  delay(2000);
  
  // START MOVING
  startForward();
}

// ============================================================================
// MAIN LOOP - ENHANCED WITH CURVE DETECTION
// ============================================================================

void loop() {
  unsigned long currentTime = millis();
  
  // Read IR sensors
  bool leftWall = !digitalRead(IR_LEFT);
  bool rightWall = !digitalRead(IR_RIGHT);
  
 /* // FAST CURVE DETECTION - runs more frequently
  if (currentTime - lastCurveCheck >= CURVE_CHECK_INTERVAL) {
    lastCurveCheck = currentTime;
    
    float leftDist = measureDistanceFiltered(TRIG_LEFT, ECHO_LEFT);
    float rightDist = measureDistanceFiltered(TRIG_RIGHT, ECHO_RIGHT);
    
    detectAndHandleCurve(leftDist, rightDist);
  }*/
  
  // OBSTACLE DETECTION - runs at normal interval
  if (currentTime - lastCheck >= CHECK_INTERVAL) {
    lastCheck = currentTime;
    
    float centerDist = measureDistanceFiltered(TRIG_CENTER, ECHO_CENTER);
    
    #if DEBUG_ENABLED
    Serial.print("[MOVING] Front: ");
    Serial.print(centerDist);
    Serial.println(" cm");
    #endif

    // IR SENSOR LOGIC
    if (rightWall && leftWall) {
      DEBUG_PRINTLN("\n[ALERT] Both walls - Reversing!");
      stopMotors();
      delay(30);
      
      reverseMotors();
      delay(REVERSE_TIME); 
      stopMotors();
      delay(50);
      
      DEBUG_PRINTLN("[REVERSE] Complete");
    }
    else if (rightWall) {
      DEBUG_PRINTLN("[IR] Right wall detected - Turning LEFT");
      
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      ledcWrite(PWMA, 100);
      
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      ledcWrite(PWMB, TURN_SPEED);
      
      delay(TURN_IR);
      startForward();
    }
    else if (leftWall) {
      DEBUG_PRINTLN("[IR] Left wall detected - Turning RIGHT");
      
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      ledcWrite(PWMA, 100);
      
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      ledcWrite(PWMB, TURN_SPEED);
      
      delay(TURN_IR);
      startForward();
    }
    
    // OBSTACLE DETECTED
    if (centerDist > 0 && centerDist < STOP_DISTANCE) {
      
      if (centerDist < REVERSE_DISTANCE) {
        DEBUG_PRINTLN("\n[ALERT] TOO CLOSE! Reversing...");
        stopMotors();
        delay(50);
        
        reverseMotors();
        delay(REVERSE_TIME);
        stopMotors();
        delay(50);
        
        DEBUG_PRINTLN("[REVERSE] Complete");
      }
      else {
        DEBUG_PRINTLN("\n[OBSTACLE] Stopping for decision...");
        stopMotors();
        delay(150);
      }
      
      // ENHANCED SCANNING
      float distances[3];
      scanAllDirectionsEnhanced(distances);
      
      // SMART DECISION
      makeSmartDecision(distances, leftWall, rightWall);
      
      delay(100);
      startForward();
    }
  }
}

// ============================================================================
// CALIBRATION - NEW FUNCTION
// ============================================================================

void calibrateSensors() {
  // Fill history buffers with initial readings
  for(int i = 0; i < FILTER_SAMPLES; i++) {
    leftHistory[i] = getSingleReading(TRIG_LEFT, ECHO_LEFT);
    delay(20);
    centerHistory[i] = getSingleReading(TRIG_CENTER, ECHO_CENTER);
    delay(20);
    rightHistory[i] = getSingleReading(TRIG_RIGHT, ECHO_RIGHT);
    delay(20);
  }
  DEBUG_PRINTLN("[CALIBRATION] Complete");
}

// ============================================================================
// CURVE DETECTION AND HANDLING - NEW FUNCTION
// ============================================================================

void detectAndHandleCurve(float leftDist, float rightDist) {
  float difference = abs(leftDist - rightDist);
  
  // Detect curve type
  if (difference < GENTLE_CURVE_DIFF) {
    // STRAIGHT PATH
    if (inCurve) {
      DEBUG_PRINTLN("[CURVE] Exiting curve - resuming normal speed");
      inCurve = false;
      curveDirection = 0;
      startForward(); // Resume normal speed
    }
  }
  else if (difference < SHARP_CURVE_DIFF) {
    // GENTLE CURVE
    if (!inCurve || curveDirection == 0) {
      DEBUG_PRINTLN("[CURVE] Gentle curve detected - adjusting speed");
      inCurve = true;
    }
    
    // Determine direction and adjust
    if (leftDist < rightDist) {
      // Curving LEFT - slow down left motor
      curveDirection = -1;
      adjustSpeedForCurve(GENTLE_CURVE_FACTOR, -1);
    } else {
      // Curving RIGHT - slow down right motor
      curveDirection = 1;
      adjustSpeedForCurve(GENTLE_CURVE_FACTOR, 1);
    }
  }
  else {
    // SHARP CURVE
    if (!inCurve) {
      DEBUG_PRINTLN("[CURVE] Sharp curve detected - significant speed reduction");
      inCurve = true;
    }
    
    if (leftDist < rightDist) {
      curveDirection = -1;
      adjustSpeedForCurve(SHARP_CURVE_FACTOR, -1);
    } else {
      curveDirection = 1;
      adjustSpeedForCurve(SHARP_CURVE_FACTOR, 1);
    }
  }
}

// ============================================================================
// ADJUST SPEED FOR CURVE - NEW FUNCTION
// ============================================================================

void adjustSpeedForCurve(float speedFactor, int direction) {
  int baseSpeedL = MOTOR_SPEED_L * speedFactor;
  int baseSpeedR = MOTOR_SPEED_R * speedFactor;
  
  int leftSpeed, rightSpeed;
  
  if (direction < 0) {
    // Curving LEFT - reduce left motor more
    leftSpeed = baseSpeedL * 0.35; //85
    rightSpeed = baseSpeedR;
  
  }
  else if (direction > 0) {
    // Curving RIGHT - reduce right motor more
    leftSpeed = baseSpeedL;
    rightSpeed = baseSpeedR * 0.35; //85
    
  }
  else {
    // Straight
    leftSpeed = baseSpeedL;
    rightSpeed = baseSpeedR;
  }
  
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  ledcWrite(PWMA, leftSpeed);
  
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  ledcWrite(PWMB, rightSpeed);
  delay(90);
}

// ============================================================================
// MOTOR CONTROL
// ============================================================================

void startForward() {
  DEBUG_PRINTLN("[MOTOR] Forward movement");
  
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
  delay(50);
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
  delay(50);
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
// SENSOR FUNCTIONS - ENHANCED WITH BETTER FILTERING
// ============================================================================

float getSingleReading(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, SENSOR_TIMEOUT);
  
  if (duration == 0) {
    return 999;
  }

  float distance = (duration / 2.0) * 0.0343;

  if (distance <= 0 || distance > 400) {
    return 400;
  }

  return distance;
}

// ENHANCED: Median + Moving Average Filter
float measureDistanceFiltered(int trigPin, int echoPin) {
  float readings[FILTER_SAMPLES];
  
  // Take multiple readings
  for(int i = 0; i < FILTER_SAMPLES; i++) {
    readings[i] = getSingleReading(trigPin, echoPin);
    if(i < FILTER_SAMPLES - 1) {
      delay(5);
    }
  }
  
  // Sort for median
  for(int i = 0; i < FILTER_SAMPLES - 1; i++) {
    for(int j = i + 1; j < FILTER_SAMPLES; j++) {
      if(readings[i] > readings[j]) {
        float temp = readings[i];
        readings[i] = readings[j];
        readings[j] = temp;
      }
    }
  }
  
  // Return median (middle value)
  return readings[FILTER_SAMPLES / 2];
}

// ENHANCED: Scan with better accuracy
void scanAllDirectionsEnhanced(float distances[3]) {
  DEBUG_PRINTLN("\n[SCAN] ========== ENHANCED 3-WAY SCAN ==========");
  
  delay(50);
  
  // Multiple scans and average for maximum accuracy
  float leftSum = 0, centerSum = 0, rightSum = 0;
  int validScans = 0;
  
  for(int scan = 0; scan < 2; scan++) {
    float L = measureDistanceFiltered(TRIG_LEFT, ECHO_LEFT);
    delay(50);
    float C = measureDistanceFiltered(TRIG_CENTER, ECHO_CENTER);
    delay(50);
    float R = measureDistanceFiltered(TRIG_RIGHT, ECHO_RIGHT);
    delay(50);
    
    if(L < 900 && C < 900 && R < 900) {
      leftSum += L;
      centerSum += C;
      rightSum += R;
      validScans++;
    }
  }
  
  if(validScans > 0) {
    distances[0] = leftSum / validScans;
    distances[1] = centerSum / validScans;
    distances[2] = rightSum / validScans;
  } else {
    distances[0] = measureDistanceFiltered(TRIG_LEFT, ECHO_LEFT);
    distances[1] = measureDistanceFiltered(TRIG_CENTER, ECHO_CENTER);
    distances[2] = measureDistanceFiltered(TRIG_RIGHT, ECHO_RIGHT);
  }
  
  DEBUG_PRINT("  LEFT: ");
  DEBUG_PRINT(distances[0]);
  DEBUG_PRINT(" cm | CENTER: ");
  DEBUG_PRINT(distances[1]);
  DEBUG_PRINT(" cm | RIGHT: ");
  DEBUG_PRINT(distances[2]);
  DEBUG_PRINTLN(" cm");
  
  DEBUG_PRINTLN("[SCAN] ===================================\n");
}

// ============================================================================
// SMART DECISION LOGIC - ENHANCED
// ============================================================================

void makeSmartDecision(float distances[3], bool leftWall, bool rightWall) {
  float leftDist = distances[0];
  float centerDist = distances[1];
  float rightDist = distances[2];
  
  DEBUG_PRINTLN("[DECISION] Analyzing paths...");
  DEBUG_PRINT("  L:");
  DEBUG_PRINT(leftDist);
  DEBUG_PRINT(" C:");
  DEBUG_PRINT(centerDist);
  DEBUG_PRINT(" R:");
  DEBUG_PRINT(rightDist);
  DEBUG_PRINTLN(" cm");
  
  // Find max with preference for CENTER (for stability)
  float maxDist = centerDist;
  int direction = 1; // 0=left, 1=center, 2=right
  
  // Center is preferred if within 20% of max
  if(leftDist > maxDist * 1.4) {
    maxDist = leftDist;
    direction = 0;
  }
  if(rightDist > maxDist * 1.4) {
    maxDist = rightDist;
    direction = 2;
  }
  
  DEBUG_PRINT("  Best path: ");
  
  // Make decision
  if(direction == 1 && centerDist > MIN_SAFE_DISTANCE) {
    DEBUG_PRINTLN("CENTER - Continue forward");
    // No turn needed
  }
  else if(direction == 0 && leftDist > MIN_SAFE_DISTANCE) {
    DEBUG_PRINTLN("LEFT - Turning RIGHT to face it");
    turnRight();
  }
  else if(direction == 2 && rightDist > MIN_SAFE_DISTANCE) {
    DEBUG_PRINTLN("RIGHT - Turning LEFT to face it");
    turnLeft();
  }
  else {
    DEBUG_PRINTLN("BLOCKED - U-Turn");
    turnAround();
  }
}