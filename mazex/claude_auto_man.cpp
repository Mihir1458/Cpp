/*
 * ============================================================================
 *  PREMIUM IoT HAZARD SURVEILLANCE ROVER DASHBOARD
 *  ESP32 | ESPAsyncWebServer | WebSockets | DHT11 | Autonomoous + Manual Mode
 * ============================================================================
 *  HARDWARE PINS (match reference schematic):
 *    Motor A (Left)  : PWMA=25, AIN1=26, AIN2=27
 *    Motor B (Right) : PWMB=14, BIN1=32, BIN2=13, STBY=33
 *    Ultrasonic Left : TRIG=18, ECHO=19
 *    Ultrasonic Ctr  : TRIG=22, ECHO=21
 *    Ultrasonic Right: TRIG=4,  ECHO=5
 *    IR Left         : 34   IR Right: 35
 *    DHT11           : 23
 *    Flame Sensor    : 15  (LOW = flame detected)
 *    Buzzer          : 12
 * ============================================================================
 *  DEPENDENCIES (install via Library Manager):
 *    - ESPAsyncWebServer  (me-no-dev)
 *    - AsyncTCP           (me-no-dev)
 *    - DHT sensor library (Adafruit)
 *    - Adafruit Unified Sensor
 * ============================================================================
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <DHT.h>
#include <ArduinoJson.h>

// ============================================================================
// NETWORK CONFIG  –  AP mode, no router needed
// ============================================================================
const char* AP_SSID     = "CHETAK";
const char* AP_PASSWORD = "Eklavya55";

// ============================================================================
// PIN DEFINITIONS
// ============================================================================
#define PWMA 25
#define AIN1 26
#define AIN2 27
#define PWMB 14
#define BIN1 32
#define BIN2 13
#define STBY 33

#define TRIG_LEFT   18
#define ECHO_LEFT   19
#define TRIG_CENTER 22
#define ECHO_CENTER 21
#define TRIG_RIGHT   4
#define ECHO_RIGHT   5

#define IR_LEFT   34
#define IR_RIGHT  35

#define DHT_PIN   23
#define DHT_TYPE  DHT11
#define FLAME_PIN 15
#define BUZZER_PIN 12

// ============================================================================
// PWM / MOTOR PARAMS
// ============================================================================
#define PWM_FREQ       12000
#define PWM_RESOLUTION 8

#define MOTOR_SPEED_L   210
#define MOTOR_SPEED_R   196
#define TURN_SPEED      220
#define REVERSE_SPEED_L 169
#define REVERSE_SPEED_R 215

#define STOP_DISTANCE    23
#define REVERSE_DISTANCE 11
#define TURN_90_TIME    135
#define TURN_IR          63
#define REVERSE_TIME    120
#define CHECK_INTERVAL  120

// ============================================================================
// HAZARD THRESHOLDS
// ============================================================================
#define TEMP_THRESHOLD  45
#define HUM_THRESHOLD   80
#define SENSOR_INTERVAL 800   // ms between sensor broadcasts
#define ENABLE_STARTUP_TONE 1 // Set to 0 only if GPIO12 buzzer wiring causes boot trouble
#define IR_BUZZ_INTERVAL 450  // ms between IR warning beeps
#define IR_BUZZ_TIME      90  // ms beep duration for IR wall warning

// ============================================================================
// GLOBALS
// ============================================================================
DHT dht(DHT_PIN, DHT_TYPE);
AsyncWebServer server(80);
AsyncWebSocket  ws("/ws");
// ===== FUNCTION PROTOTYPES =====

// Motor
void startForward();
void stopMotors();
void reverseMotors();
void turnLeft();
void turnRight();
void turnLeftContinuous();
void turnRightContinuous();

// Autonomous + Hazard
void runAutonomous();
void handleHazard();
void delayWithMonitoring(unsigned long ms);

// Sensors
void readAndBroadcastSensors(bool force);
float getSingleReading(int trigPin, int echoPin);
float measureDistance(int trigPin, int echoPin);
void scanAllDirections(float d[3]);
void makeDecision(float d[3], bool leftWall, bool rightWall);
void turnAround();

// --- mode ---
volatile bool autonomousMode = false;   // false = manual, true = auto

// --- sensor state ---
float    temperature    = 0;
float    humidity       = 0;
float    distLeft       = 999;
float    distCenter     = 999;
float    distRight      = 999;
bool     flameDetected  = false;
bool     irLeft         = false;
bool     irRight        = false;
bool     hazardActive   = false;

// --- timing ---
unsigned long lastCheck      = 0;
unsigned long lastSensorBcast= 0;
unsigned long lastIrBuzz     = 0;

// ============================================================================
// HTML / CSS / JS  (stored in program flash)
// ============================================================================
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Rover Control</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700;900&family=JetBrains+Mono:wght@300;400;600&display=swap" rel="stylesheet">
<style>
  :root{
    --bg:#0a0a0f;
    --surface:#111118;
    --glass:rgba(255,255,255,0.04);
    --border:rgba(255,255,255,0.08);
    --accent:#00e5ff;
    --accent2:#7b2fff;
    --danger:#ff3b3b;
    --warn:#ff9500;
    --ok:#00e676;
    --text:#e0e0e0;
    --muted:#666;
    --glow-accent:0 0 18px rgba(0,229,255,0.45);
    --glow-danger:0 0 22px rgba(255,59,59,0.6);
    --glow-warn:0 0 22px rgba(255,149,0,0.6);
    --glow-ok:0 0 18px rgba(0,230,118,0.5);
  }
  *{box-sizing:border-box;margin:0;padding:0}
  body{
    background:var(--bg);
    color:var(--text);
    font-family:'JetBrains Mono',monospace;
    min-height:100vh;
    overflow-x:hidden;
  }
  /* ---- grid noise overlay ---- */
  body::before{
    content:'';position:fixed;inset:0;
    background-image:repeating-linear-gradient(0deg,transparent,transparent 39px,rgba(0,229,255,0.03) 40px),
                     repeating-linear-gradient(90deg,transparent,transparent 39px,rgba(0,229,255,0.03) 40px);
    pointer-events:none;z-index:0;
  }
  #app{position:relative;z-index:1;max-width:1100px;margin:0 auto;padding:24px 16px 60px}

  /* ---- header ---- */
  header{display:flex;align-items:center;justify-content:space-between;margin-bottom:28px;flex-wrap:wrap;gap:12px}
  .logo{font-family:'Orbitron',sans-serif;font-weight:900;font-size:1.35rem;letter-spacing:3px;color:var(--accent);text-shadow:var(--glow-accent)}
  .logo span{color:var(--accent2)}
  .ws-badge{font-size:.7rem;padding:4px 10px;border-radius:20px;border:1px solid var(--muted);color:var(--muted);transition:.3s}
  .ws-badge.online{border-color:var(--ok);color:var(--ok);box-shadow:var(--glow-ok)}

  /* ---- section title ---- */
  .sec-title{font-family:'Orbitron',sans-serif;font-size:.65rem;letter-spacing:4px;color:var(--muted);margin-bottom:14px;text-transform:uppercase}

  /* ---- glass card ---- */
  .card{
    background:var(--glass);
    border:1px solid var(--border);
    border-radius:14px;
    padding:18px 20px;
    backdrop-filter:blur(10px);
    transition:box-shadow .35s, border-color .35s;
  }
  .card.alert-danger{border-color:var(--danger)!important;box-shadow:var(--glow-danger)!important;animation:pulse-danger 1.2s infinite}
  .card.alert-warn  {border-color:var(--warn)!important;box-shadow:var(--glow-warn)!important;animation:pulse-warn 1.2s infinite}

  @keyframes pulse-danger{0%,100%{box-shadow:0 0 16px rgba(255,59,59,0.5)}50%{box-shadow:0 0 34px rgba(255,59,59,0.9)}}
  @keyframes pulse-warn  {0%,100%{box-shadow:0 0 16px rgba(255,149,0,0.5)}50%{box-shadow:0 0 34px rgba(255,149,0,0.9)}}

  /* ---- sensor grid ---- */
  .sensor-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(155px,1fr));gap:14px;margin-bottom:24px}
  .s-card{
    background:var(--glass);
    border:1px solid var(--border);
    border-radius:12px;
    padding:16px 14px;
    display:flex;flex-direction:column;gap:6px;
    transition:box-shadow .35s, border-color .35s;
  }
  .s-card .s-label{font-size:.6rem;letter-spacing:3px;color:var(--muted);text-transform:uppercase}
  .s-card .s-value{font-family:'Orbitron',sans-serif;font-size:1.5rem;font-weight:700;color:var(--accent)}
  .s-card .s-unit {font-size:.65rem;color:var(--muted)}
  .s-card .s-dot  {width:10px;height:10px;border-radius:50%;background:var(--muted);margin-top:2px;transition:background .3s,box-shadow .3s}
  .s-dot.on {background:var(--ok);box-shadow:var(--glow-ok)}
  .s-dot.err{background:var(--danger);box-shadow:var(--glow-danger)}
  .s-dot.warn{background:var(--warn);box-shadow:var(--glow-warn)}

  /* ---- distance bars ---- */
  .dist-row{display:flex;gap:10px;align-items:flex-end;margin-bottom:24px}
  .dist-col{flex:1;display:flex;flex-direction:column;align-items:center;gap:6px}
  .dist-bar-wrap{width:100%;height:120px;background:rgba(255,255,255,0.04);border-radius:8px;display:flex;align-items:flex-end;overflow:hidden;border:1px solid var(--border)}
  .dist-bar{width:100%;background:linear-gradient(180deg,var(--accent),var(--accent2));border-radius:6px;transition:height .4s cubic-bezier(.4,0,.2,1);min-height:4px}
  .dist-label{font-size:.58rem;letter-spacing:2px;color:var(--muted);text-transform:uppercase}
  .dist-val{font-family:'Orbitron',sans-serif;font-size:.85rem;color:var(--accent)}

  /* ---- mode toggle ---- */
  .mode-row{display:flex;align-items:center;gap:18px;margin-bottom:24px}
  .mode-label{font-size:.7rem;letter-spacing:3px;color:var(--muted);text-transform:uppercase;min-width:70px}
  .toggle-wrap{display:flex;align-items:center;gap:12px}
  .toggle{position:relative;width:68px;height:34px;cursor:pointer}
  .toggle input{opacity:0;width:0;height:0}
  .slider{
    position:absolute;inset:0;
    background:rgba(255,255,255,0.08);
    border:1px solid var(--border);
    border-radius:34px;
    transition:.35s;
  }
  .slider::before{
    content:'';position:absolute;width:26px;height:26px;
    left:4px;bottom:3px;
    background:var(--muted);border-radius:50%;
    transition:.35s;
    box-shadow:0 2px 6px rgba(0,0,0,0.5);
  }
  input:checked + .slider{background:rgba(0,229,255,0.15);border-color:var(--accent);box-shadow:var(--glow-accent)}
  input:checked + .slider::before{transform:translateX(34px);background:var(--accent)}
  .mode-name{font-family:'Orbitron',sans-serif;font-size:.8rem;letter-spacing:2px;color:var(--accent);min-width:110px}

  /* ---- hazard banner ---- */
  #hazard-banner{
    display:none;
    background:linear-gradient(90deg,rgba(255,59,59,0.15),rgba(255,149,0,0.1));
    border:1px solid var(--danger);
    border-radius:12px;
    padding:14px 20px;
    margin-bottom:20px;
    font-family:'Orbitron',sans-serif;
    font-size:.8rem;
    letter-spacing:2px;
    color:var(--danger);
    box-shadow:var(--glow-danger);
    animation:pulse-danger 1.2s infinite;
  }
  #hazard-banner.show{display:flex;align-items:center;gap:12px}

  .ir-alert{
    display:none;
    margin-bottom:20px;
    padding:14px 18px;
    border:1px solid var(--warn);
    border-radius:8px;
    background:linear-gradient(90deg,rgba(255,149,0,0.22),rgba(255,59,59,0.14));
    box-shadow:var(--glow-warn);
    font-family:'Orbitron',sans-serif;
    font-size:.78rem;
    letter-spacing:2px;
    color:var(--warn);
    animation:pulse-warn 1s infinite;
  }
  .ir-alert.show{display:flex;align-items:center;justify-content:space-between;gap:12px}
  body.ir-detected{box-shadow:inset 0 0 0 3px rgba(255,149,0,.62),inset 0 0 38px rgba(255,59,59,.24)}
  body.ir-detected::after{
    content:'';
    position:fixed;
    inset:0;
    border:3px solid rgba(255,149,0,.75);
    box-shadow:inset 0 0 34px rgba(255,59,59,.35);
    pointer-events:none;
    z-index:3;
  }

  /* ---- one-line drive status ---- */
  .drive-line{
    display:grid;
    grid-template-columns:repeat(3,1fr);
    gap:10px;
    margin-bottom:20px;
  }
  .drive-cell{
    min-height:70px;
    border:1px solid var(--border);
    border-radius:8px;
    background:rgba(255,255,255,.045);
    padding:12px 10px;
    display:flex;
    flex-direction:column;
    justify-content:center;
    gap:5px;
    text-align:center;
    transition:border-color .25s,box-shadow .25s,background .25s;
  }
  .drive-cell .dir{font-family:'Orbitron',sans-serif;font-size:.7rem;letter-spacing:3px;color:var(--muted)}
  .drive-cell .cm{font-family:'Orbitron',sans-serif;font-size:1.15rem;color:var(--accent)}
  .drive-cell .state{font-size:.58rem;letter-spacing:2px;color:var(--muted)}
  .drive-cell.warn{border-color:var(--warn);box-shadow:var(--glow-warn);background:rgba(255,149,0,.10)}
  .drive-cell.danger{border-color:var(--danger);box-shadow:var(--glow-danger);background:rgba(255,59,59,.12)}
  .drive-cell.best{border-color:var(--ok);box-shadow:var(--glow-ok)}

  .guide-box{
    border:1px solid rgba(0,229,255,.35);
    border-radius:8px;
    padding:14px 16px;
    margin-bottom:16px;
    background:rgba(0,229,255,.06);
  }
  .guide-label{font-size:.58rem;letter-spacing:3px;color:var(--muted);text-transform:uppercase;margin-bottom:6px}
  .guide-action{font-family:'Orbitron',sans-serif;font-size:1.1rem;letter-spacing:2px;color:var(--accent);text-shadow:var(--glow-accent)}
  .guide-note{font-size:.62rem;color:var(--muted);margin-top:6px;letter-spacing:1px}
  .guide-box.warn{border-color:var(--warn);box-shadow:var(--glow-warn);background:rgba(255,149,0,.1)}
  .guide-box.danger{border-color:var(--danger);box-shadow:var(--glow-danger);background:rgba(255,59,59,.11)}
  .dp-btn.recommended{border-color:var(--ok);box-shadow:var(--glow-ok);color:var(--ok)}

  /* ---- dpad ---- */
  .dpad-section{margin-top:4px}
  .dpad-wrap{display:flex;justify-content:center;margin-top:8px}
  .dpad{display:grid;grid-template-columns:60px 60px 60px;grid-template-rows:60px 60px 60px;gap:6px}
  .dp-btn{
    background:var(--glass);
    border:1px solid var(--border);
    border-radius:10px;
    color:var(--text);
    font-size:1.4rem;
    cursor:pointer;
    display:flex;align-items:center;justify-content:center;
    transition:background .15s,box-shadow .15s,transform .1s;
    user-select:none;
    -webkit-tap-highlight-color:transparent;
  }
  .dp-btn:active,.dp-btn.pressed{
    background:rgba(0,229,255,0.15);
    border-color:var(--accent);
    box-shadow:var(--glow-accent);
    transform:scale(.93);
  }
  .dp-btn.stop-btn{border-color:var(--danger);color:var(--danger);font-size:.75rem;font-family:'Orbitron',sans-serif;letter-spacing:1px}
  .dp-btn.stop-btn:active{box-shadow:var(--glow-danger);background:rgba(255,59,59,0.15)}
  .dp-empty{visibility:hidden}
  .manual-hint{text-align:center;font-size:.6rem;letter-spacing:2px;color:var(--muted);margin-top:10px}
  .manual-disabled{opacity:.35;pointer-events:none}

  /* ---- footer ---- */
  footer{margin-top:40px;text-align:center;font-size:.58rem;letter-spacing:3px;color:var(--muted)}

  /* ---- responsive ---- */
  @media(max-width:500px){
    .dpad{grid-template-columns:52px 52px 52px;grid-template-rows:52px 52px 52px}
    .drive-line{grid-template-columns:1fr;gap:8px}
    .dist-row{flex-direction:column;align-items:stretch}
    .dist-bar-wrap{height:60px}
    .dist-bar{height:100%!important;width:var(--fill,20%)!important}
  }
</style>
</head>
<body>
<div id="app">

  <!-- HEADER -->
  <header>
    <div class="logo">ROVER<span>.</span>OS</div>
    <span id="ws-badge" class="ws-badge">CONNECTING…</span>
  </header>

  <!-- HAZARD BANNER -->
  <div id="hazard-banner">
    <span>⚠</span>
    <span id="hazard-msg">HAZARD DETECTED</span>
  </div>

  <div id="ir-alert" class="ir-alert">
    <span id="ir-alert-main">IR EDGE DETECTED</span>
    <span id="ir-alert-side">CHECK LEFT / RIGHT</span>
  </div>

  <!-- MODE TOGGLE -->
  <div class="card" style="margin-bottom:24px">
    <div class="sec-title">Operation Mode</div>
    <div class="mode-row">
      <span class="mode-label">Manual</span>
      <label class="toggle">
        <input type="checkbox" id="mode-toggle">
        <span class="slider"></span>
      </label>
      <span class="mode-name" id="mode-display">MANUAL</span>
    </div>
  </div>

  <!-- ENVIRONMENT SENSORS -->
  <div class="sec-title">Environment & Safety</div>
  <div class="sensor-grid">
    <div class="s-card" id="card-temp">
      <div class="s-label">Temperature</div>
      <div class="s-value" id="val-temp">--</div>
      <div class="s-unit">°C</div>
    </div>
    <div class="s-card" id="card-hum">
      <div class="s-label">Humidity</div>
      <div class="s-value" id="val-hum">--</div>
      <div class="s-unit">% RH</div>
    </div>
    <div class="s-card" id="card-flame">
      <div class="s-label">Flame</div>
      <div class="s-dot" id="dot-flame"></div>
      <div class="s-unit" id="txt-flame">NO FLAME</div>
    </div>
    <div class="s-card" id="card-ir-l">
      <div class="s-label">IR Left</div>
      <div class="s-dot" id="dot-ir-l"></div>
      <div class="s-unit" id="txt-ir-l">CLEAR</div>
    </div>
    <div class="s-card" id="card-ir-r">
      <div class="s-label">IR Right</div>
      <div class="s-dot" id="dot-ir-r"></div>
      <div class="s-unit" id="txt-ir-r">CLEAR</div>
    </div>
  </div>

  <!-- ONE-LINE L C R DRIVE STATUS -->
  <div class="sec-title">Drive Line: L / C / R</div>
  <div class="drive-line">
    <div class="drive-cell" id="nav-left">
      <div class="dir">L</div>
      <div class="cm" id="nav-left-cm">-- cm</div>
      <div class="state" id="nav-left-state">CLEAR</div>
    </div>
    <div class="drive-cell" id="nav-center">
      <div class="dir">C</div>
      <div class="cm" id="nav-center-cm">-- cm</div>
      <div class="state" id="nav-center-state">CLEAR</div>
    </div>
    <div class="drive-cell" id="nav-right">
      <div class="dir">R</div>
      <div class="cm" id="nav-right-cm">-- cm</div>
      <div class="state" id="nav-right-state">CLEAR</div>
    </div>
  </div>

  <!-- ULTRASONIC DISTANCE BARS -->
  <div class="sec-title">Obstacle Distance (cm)</div>
  <div class="dist-row" style="margin-bottom:28px">
    <div class="dist-col">
      <div class="dist-bar-wrap"><div class="dist-bar" id="bar-left" style="height:5%"></div></div>
      <div class="dist-val" id="val-left">-- cm</div>
      <div class="dist-label">Left</div>
    </div>
    <div class="dist-col">
      <div class="dist-bar-wrap"><div class="dist-bar" id="bar-center" style="height:5%"></div></div>
      <div class="dist-val" id="val-center">-- cm</div>
      <div class="dist-label">Center</div>
    </div>
    <div class="dist-col">
      <div class="dist-bar-wrap"><div class="dist-bar" id="bar-right" style="height:5%"></div></div>
      <div class="dist-val" id="val-right">-- cm</div>
      <div class="dist-label">Right</div>
    </div>
  </div>

  <!-- MANUAL CONTROL -->
  <div class="card dpad-section" id="manual-panel">
    <div class="sec-title">Manual Control</div>
    <div class="guide-box" id="guide-box">
      <div class="guide-label">Live Manual Guidance</div>
      <div class="guide-action" id="guide-action">FORWARD CLEAR</div>
      <div class="guide-note" id="guide-note">Use the highlighted control for safest motion.</div>
    </div>
    <div class="dpad-wrap">
      <div class="dpad" id="dpad">
        <div class="dp-empty"></div>
        <button class="dp-btn" id="btn-fwd"   data-cmd="F" title="Forward">▲</button>
        <div class="dp-empty"></div>
        <button class="dp-btn" id="btn-left"  data-cmd="L" title="Left">◀</button>
        <button class="dp-btn stop-btn" id="btn-stop" data-cmd="S" title="Stop">STOP</button>
        <button class="dp-btn" id="btn-right" data-cmd="R" title="Right">▶</button>
        <div class="dp-empty"></div>
        <button class="dp-btn" id="btn-back"  data-cmd="B" title="Backward">▼</button>
        <div class="dp-empty"></div>
      </div>
    </div>
    <div class="manual-hint">HOLD to move · RELEASE to stop</div>
  </div>

  <footer>ROVER·OS v2.0 &nbsp;|&nbsp; ESP32 DASHBOARD &nbsp;|&nbsp; WebSocket Live</footer>
</div>

<script>
// =====================================================================
// WebSocket
// =====================================================================
let ws;
const MAX_DIST = 100; // cm ceiling for bar scaling

function connect(){
  ws = new WebSocket('ws://' + location.host + '/ws');
  ws.onopen    = ()=>{ document.getElementById('ws-badge').textContent='LIVE';
                        document.getElementById('ws-badge').classList.add('online'); };
  ws.onclose   = ()=>{ document.getElementById('ws-badge').textContent='OFFLINE';
                        document.getElementById('ws-badge').classList.remove('online');
                        setTimeout(connect, 2000); };
  ws.onerror   = ()=> ws.close();
  ws.onmessage = e => {
    try{ handleData(JSON.parse(e.data)); }catch(_){}
  };
}

function sendCmd(cmd){
  if(ws && ws.readyState===1) ws.send(cmd);
}

// =====================================================================
// Data Handler
// =====================================================================
function handleData(d){
  // -- temp
  const temp = parseFloat(d.temp);
  document.getElementById('val-temp').textContent = isNaN(temp)?'ERR':temp.toFixed(1);
  const tCard = document.getElementById('card-temp');
  tCard.className = 's-card' + (temp > 45 ? ' alert-danger' : temp > 38 ? ' alert-warn' : '');

  // -- humidity
  const hum = parseFloat(d.hum);
  document.getElementById('val-hum').textContent = isNaN(hum)?'ERR':hum.toFixed(1);
  const hCard = document.getElementById('card-hum');
  hCard.className = 's-card' + (hum > 80 ? ' alert-warn' : '');

  // -- flame
  const flame = d.flame;
  const fdot  = document.getElementById('dot-flame');
  document.getElementById('txt-flame').textContent = flame ? 'FLAME!' : 'CLEAR';
  fdot.className = 's-dot ' + (flame ? 'err' : 'on');
  document.getElementById('card-flame').className = 's-card' + (flame ? ' alert-danger' : '');

  // -- IR
  setIR('l', d.ir_left);
  setIR('r', d.ir_right);

  // -- distances
  setBar('left',   d.d_left);
  setBar('center', d.d_center);
  setBar('right',  d.d_right);
  updateDriveUI(d);

  // -- hazard banner
  const hazard = flame || temp > 45 || hum > 80;
  const banner = document.getElementById('hazard-banner');
  if(hazard){
    banner.classList.add('show');
    let msg = [];
    if(flame)    msg.push('FLAME');
    if(temp>45)  msg.push('HIGH TEMP ('+temp.toFixed(1)+'°C)');
    if(hum>80)   msg.push('HIGH HUM ('+hum.toFixed(1)+'%)');
    document.getElementById('hazard-msg').textContent = '⚠ ' + msg.join(' | ');
  } else {
    banner.classList.remove('show');
  }
}

function setIR(side, active){
  const dot = document.getElementById('dot-ir-'+side);
  const txt = document.getElementById('txt-ir-'+side);
  dot.className = 's-dot ' + (active ? 'err' : 'on');
  txt.textContent = active ? 'WALL' : 'CLEAR';
  document.getElementById('card-ir-'+side).className = 's-card' + (active ? ' alert-danger' : '');
}

function setBar(dir, raw){
  const val = parseFloat(raw);
  const safe = isNaN(val)||val>999 ? MAX_DIST : Math.min(val, MAX_DIST);
  const pct  = Math.max(3, (safe/MAX_DIST)*100);
  document.getElementById('bar-'+dir).style.height = pct+'%';
  document.getElementById('val-'+dir).textContent  = (isNaN(val)||val>999?'---':val.toFixed(1))+' cm';
  // colour feedback
  const bar = document.getElementById('bar-'+dir);
  if(safe < 15)      bar.style.background='linear-gradient(180deg,#ff3b3b,#ff6b6b)';
  else if(safe < 30) bar.style.background='linear-gradient(180deg,#ff9500,#ffb300)';
  else               bar.style.background='linear-gradient(180deg,var(--accent),var(--accent2))';
}

function cleanDistance(raw){
  const val = parseFloat(raw);
  if(isNaN(val) || val > 999) return MAX_DIST;
  return Math.min(val, MAX_DIST);
}

function formatDistance(raw){
  const val = parseFloat(raw);
  return (isNaN(val) || val > 999 ? '---' : val.toFixed(1)) + ' cm';
}

function setDriveCell(dir, raw, blocked, best){
  const safe = cleanDistance(raw);
  const cell = document.getElementById('nav-'+dir);
  document.getElementById('nav-'+dir+'-cm').textContent = formatDistance(raw);
  let state = 'CLEAR';
  let cls = 'drive-cell';
  if(blocked || safe < 15){
    state = blocked ? 'IR WALL' : 'TOO CLOSE';
    cls += ' danger';
  } else if(safe < 30){
    state = 'SLOW';
    cls += ' warn';
  } else if(best){
    state = 'BEST PATH';
    cls += ' best';
  }
  document.getElementById('nav-'+dir+'-state').textContent = state;
  cell.className = cls;
}

function updateDriveUI(d){
  const irL = !!d.ir_left;
  const irR = !!d.ir_right;
  const left = cleanDistance(d.d_left);
  const center = cleanDistance(d.d_center);
  const right = cleanDistance(d.d_right);
  const best = Math.max(left, center, right);

  setDriveCell('left', d.d_left, irL, left >= best && !irL);
  setDriveCell('center', d.d_center, false, center >= best);
  setDriveCell('right', d.d_right, irR, right >= best && !irR);

  const irActive = irL || irR;
  const irAlert = document.getElementById('ir-alert');
  document.body.classList.toggle('ir-detected', irActive);
  irAlert.classList.toggle('show', irActive);
  if(irActive){
    document.getElementById('ir-alert-main').textContent = 'IR WALL DETECTED';
    document.getElementById('ir-alert-side').textContent =
      irL && irR ? 'LEFT + RIGHT BLOCKED' : irL ? 'LEFT SIDE BLOCKED' : 'RIGHT SIDE BLOCKED';
  }

  updateGuide(irL, irR, left, center, right);
}

function updateGuide(irL, irR, left, center, right){
  let action = 'FORWARD CLEAR';
  let note = 'Center path is open. Move forward slowly.';
  let level = '';
  let button = 'btn-fwd';

  if(irL && irR){
    action = 'REVERSE';
    note = 'Both IR sensors detect walls. Back away first.';
    level = 'danger';
    button = 'btn-back';
  } else if(irL){
    action = 'STEER RIGHT';
    note = 'Left IR detects a wall. Keep distance from the left side.';
    level = 'warn';
    button = 'btn-right';
  } else if(irR){
    action = 'STEER LEFT';
    note = 'Right IR detects a wall. Keep distance from the right side.';
    level = 'warn';
    button = 'btn-left';
  } else if(center < 15){
    action = 'REVERSE';
    note = 'Center obstacle is very close. Back up before turning.';
    level = 'danger';
    button = 'btn-back';
  } else if(center < 30){
    if(left > right){
      action = 'STEER LEFT';
      button = 'btn-left';
    } else {
      action = 'STEER RIGHT';
      button = 'btn-right';
    }
    note = 'Center is tight. Turn toward the clearer side.';
    level = 'warn';
  } else if(left > center && left > right + 10){
    action = 'LEFT SIDE CLEAR';
    note = 'Left has the most space if you need to turn.';
    button = 'btn-left';
  } else if(right > center && right > left + 10){
    action = 'RIGHT SIDE CLEAR';
    note = 'Right has the most space if you need to turn.';
    button = 'btn-right';
  }

  document.getElementById('guide-action').textContent = action;
  document.getElementById('guide-note').textContent = note;
  document.getElementById('guide-box').className = 'guide-box' + (level ? ' '+level : '');
  document.querySelectorAll('.dp-btn').forEach(btn => btn.classList.remove('recommended'));
  document.getElementById(button)?.classList.add('recommended');
}

// =====================================================================
// Mode Toggle
// =====================================================================
document.getElementById('mode-toggle').addEventListener('change', function(){
  const auto = this.checked;
  document.getElementById('mode-display').textContent = auto ? 'AUTONOMOUS' : 'MANUAL';
  document.getElementById('dpad').className = auto ? 'dpad manual-disabled' : 'dpad';
  sendCmd(auto ? 'AUTO' : 'MANUAL');
});

// =====================================================================
// DPad — hold = move, release = stop
// =====================================================================
const MOVE_CMDS = ['F','B','L','R'];
document.querySelectorAll('.dp-btn').forEach(btn => {
  const cmd = btn.dataset.cmd;

  const press = ()=>{
    btn.classList.add('pressed');
    sendCmd(cmd);
  };
  const release = ()=>{
    btn.classList.remove('pressed');
    if(cmd !== 'S') sendCmd('S');
  };

  btn.addEventListener('mousedown',  press);
  btn.addEventListener('mouseup',    release);
  btn.addEventListener('mouseleave', release);
  btn.addEventListener('touchstart', e=>{ e.preventDefault(); press(); }, {passive:false});
  btn.addEventListener('touchend',   e=>{ e.preventDefault(); release(); }, {passive:false});
});

// =====================================================================
// Keyboard shortcuts (WASD / arrows)
// =====================================================================
const keyMap = { ArrowUp:'F', KeyW:'F', ArrowDown:'B', KeyS:'B',
                 ArrowLeft:'L', KeyA:'L', ArrowRight:'R', KeyD:'R', Space:'S' };
const keysDown = new Set();
document.addEventListener('keydown', e=>{
  const cmd = keyMap[e.code];
  if(!cmd || keysDown.has(e.code)) return;
  keysDown.add(e.code);
  sendCmd(cmd);
  const btnId = {F:'btn-fwd',B:'btn-back',L:'btn-left',R:'btn-right',S:'btn-stop'}[cmd];
  if(btnId) document.getElementById(btnId)?.classList.add('pressed');
});
document.addEventListener('keyup', e=>{
  const cmd = keyMap[e.code];
  if(!cmd) return;
  keysDown.delete(e.code);
  if(cmd !== 'S') sendCmd('S');
  const btnId = {F:'btn-fwd',B:'btn-back',L:'btn-left',R:'btn-right',S:'btn-stop'}[cmd];
  if(btnId) document.getElementById(btnId)?.classList.remove('pressed');
});

connect();
</script>
</body>
</html>
)rawliteral";


// ============================================================================
// WebSocket event handler
// ============================================================================
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {

  if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->opcode == WS_TEXT) {
      String msg;
      msg.reserve(len);
      for (size_t i = 0; i < len; i++) {
        msg += (char)data[i];
      }
      msg.trim();

      if (msg == "AUTO") {
        autonomousMode = true;
        stopMotors();
      } else if (msg == "MANUAL") {
        autonomousMode = false;
        stopMotors();
      } else if (!autonomousMode) {
        // Manual movement commands
        if      (msg == "F") startForward();
        else if (msg == "B") reverseMotors();
        else if (msg == "L") { turnLeftContinuous(); }
        else if (msg == "R") { turnRightContinuous(); }
        else if (msg == "S") stopMotors();
      }
    }
  }
}

// ============================================================================
// BROADCAST sensor JSON over WebSocket
// ============================================================================
void broadcastSensors() {
  if (ws.count() == 0) return;

  StaticJsonDocument<256> doc;
  doc["temp"]     = isnan(temperature) ? -1 : temperature;
  doc["hum"]      = isnan(humidity)    ? -1 : humidity;
  doc["flame"]    = flameDetected;
  doc["ir_left"]  = irLeft;
  doc["ir_right"] = irRight;
  doc["d_left"]   = distLeft  > 300 ? 300 : distLeft;
  doc["d_center"] = distCenter> 300 ? 300 : distCenter;
  doc["d_right"]  = distRight > 300 ? 300 : distRight;

  String out;
  serializeJson(doc, out);
  ws.textAll(out);
}

// ============================================================================
// READ + BROADCAST SENSORS
// ============================================================================
void readAndBroadcastSensors(bool force) {
  if (!force && millis() - lastSensorBcast < SENSOR_INTERVAL) return;
  lastSensorBcast = millis();

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (!isnan(t)) temperature = t;
  if (!isnan(h)) humidity = h;

  flameDetected = (digitalRead(FLAME_PIN) == LOW);
  irLeft = !digitalRead(IR_LEFT);
  irRight = !digitalRead(IR_RIGHT);

  distLeft = getSingleReading(TRIG_LEFT, ECHO_LEFT);
  distCenter = getSingleReading(TRIG_CENTER, ECHO_CENTER);
  distRight = getSingleReading(TRIG_RIGHT, ECHO_RIGHT);

  hazardActive = flameDetected || temperature > TEMP_THRESHOLD || humidity > HUM_THRESHOLD;

  if (!hazardActive && (irLeft || irRight) && millis() - lastIrBuzz >= IR_BUZZ_INTERVAL) {
    lastIrBuzz = millis();
    tone(BUZZER_PIN, irLeft && irRight ? 1900 : 1500, IR_BUZZ_TIME);
  }

  broadcastSensors();

  Serial.printf("T:%.1f H:%.1f Flame:%d IRL:%d IRR:%d L:%.1f C:%.1f R:%.1f\n",
                temperature, humidity, flameDetected, irLeft, irRight,
                distLeft, distCenter, distRight);
}

void delayWithMonitoring(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    ws.cleanupClients();
    readAndBroadcastSensors(false);
    delay(5);
  }
}

// ============================================================================
// SETUP
// ============================================================================
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("ROVER.OS booting...");

  // --- Wi-Fi Access Point first, so CHETAK appears before rover hardware init ---
  WiFi.mode(WIFI_AP);
  bool apStarted = WiFi.softAP(AP_SSID, AP_PASSWORD, 1, 0, 4);
  Serial.print("AP started: "); Serial.println(apStarted ? "YES" : "NO");
  Serial.print("AP SSID: "); Serial.println(AP_SSID);
  Serial.print("AP IP: "); Serial.println(WiFi.softAPIP());

  // --- WebSocket ---
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  // --- Serve HTML ---
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send_P(200, "text/html", INDEX_HTML);
  });

  server.begin();
  Serial.println("Server started.");

  // --- Motor pins ---
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, LOW);
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, LOW);
  ledcAttach(PWMA, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(PWMB, PWM_FREQ, PWM_RESOLUTION);
  stopMotors();
  digitalWrite(STBY, HIGH);
  Serial.println("Motor pins ready.");

  // --- Ultrasonic ---
  pinMode(TRIG_LEFT,   OUTPUT); pinMode(ECHO_LEFT,   INPUT);
  pinMode(TRIG_CENTER, OUTPUT); pinMode(ECHO_CENTER, INPUT);
  pinMode(TRIG_RIGHT,  OUTPUT); pinMode(ECHO_RIGHT,  INPUT);
  Serial.println("Ultrasonic pins ready.");

  // --- IR ---
  pinMode(IR_LEFT,  INPUT);
  pinMode(IR_RIGHT, INPUT);
  Serial.println("IR pins ready.");

  // --- DHT / Flame / Buzzer ---
  pinMode(FLAME_PIN, INPUT);
  Serial.println("Flame pin ready.");
  digitalWrite(BUZZER_PIN, LOW);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println("Buzzer pin ready.");
  dht.begin();
  Serial.println("DHT ready.");
  Serial.println("Safety sensors ready.");

  // --- Startup tone ---
#if ENABLE_STARTUP_TONE
  tone(BUZZER_PIN, 800,  150); delay(200);
  tone(BUZZER_PIN, 1200, 150); delay(200);
  tone(BUZZER_PIN, 1800, 200); delay(300);
  noTone(BUZZER_PIN);
#endif

  readAndBroadcastSensors(true);
}

// ============================================================================
// LOOP
// ============================================================================
void loop() {
  ws.cleanupClients();
  readAndBroadcastSensors(false);

  // ---- Autonomous mode logic ----
  if (autonomousMode) {
    runAutonomous();
  }
}

// ============================================================================
// AUTONOMOUS LOGIC  (ported from reference code)
// ============================================================================
void runAutonomous() {
  // Hazard override
  if (hazardActive) {
    handleHazard();
    return;
  }

  if (millis() - lastCheck >= CHECK_INTERVAL) {
    lastCheck = millis();

    float dist = measureDistance(TRIG_CENTER, ECHO_CENTER);

    if (irLeft && irRight) {
      stopMotors();  delayWithMonitoring(30);
      reverseMotors(); delayWithMonitoring(REVERSE_TIME);
      stopMotors();  delayWithMonitoring(50);
    } else if (irRight) {
      // pivot left
      digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);  ledcWrite(PWMA, 100);
      digitalWrite(BIN1, LOW);  digitalWrite(BIN2, HIGH); ledcWrite(PWMB, TURN_SPEED);
      delayWithMonitoring(TURN_IR);
      startForward();
    } else if (irLeft) {
      // pivot right
      digitalWrite(AIN1, LOW);  digitalWrite(AIN2, HIGH); ledcWrite(PWMA, 100);
      digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);  ledcWrite(PWMB, TURN_SPEED);
      delayWithMonitoring(TURN_IR);
      startForward();
    }

    if (dist > 0 && dist < STOP_DISTANCE) {
      if (dist < REVERSE_DISTANCE) {
        stopMotors(); delayWithMonitoring(50);
        reverseMotors(); delayWithMonitoring(REVERSE_TIME);
        stopMotors(); delayWithMonitoring(50);
      } else {
        stopMotors(); delayWithMonitoring(150);
      }

      float d[3];
      scanAllDirections(d);
      makeDecision(d, irLeft, irRight);

      delayWithMonitoring(150);
      startForward();
    } else {
      startForward();
    }
  }
}

// ============================================================================
// HAZARD HANDLER
// ============================================================================
void handleHazard() {
  tone(BUZZER_PIN, 2000);

  stopMotors();  delayWithMonitoring(100);
  reverseMotors(); delayWithMonitoring(REVERSE_TIME);
  stopMotors();  delayWithMonitoring(100);

  turnAround();

  float d[3];
  scanAllDirections(d);
  makeDecision(d, irLeft, irRight);

  noTone(BUZZER_PIN);
  hazardActive = false;

  delayWithMonitoring(100);
  startForward();
}

// ============================================================================
// MOTOR FUNCTIONS
// ============================================================================
void startForward() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);  ledcWrite(PWMA, MOTOR_SPEED_L);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);  ledcWrite(PWMB, MOTOR_SPEED_R);
}

void stopMotors() {
  ledcWrite(PWMA, 0);
  ledcWrite(PWMB, 0);
}

void reverseMotors() {
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH); ledcWrite(PWMA, REVERSE_SPEED_L);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH); ledcWrite(PWMB, REVERSE_SPEED_R);
}

void turnLeft() {
  digitalWrite(AIN1, LOW);  digitalWrite(AIN2, HIGH); ledcWrite(PWMA, TURN_SPEED);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);  ledcWrite(PWMB, TURN_SPEED);
  delayWithMonitoring(TURN_90_TIME);
  stopMotors();
}

void turnRight() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);  ledcWrite(PWMA, TURN_SPEED);
  digitalWrite(BIN1, LOW);  digitalWrite(BIN2, HIGH); ledcWrite(PWMB, TURN_SPEED);
  delayWithMonitoring(TURN_90_TIME);
  stopMotors();
}

void turnAround() {
  turnRight();
  turnRight();
}

// Continuous (non-blocking) versions for manual mode
void turnLeftContinuous() {
  digitalWrite(AIN1, LOW);  digitalWrite(AIN2, HIGH); ledcWrite(PWMA, TURN_SPEED);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);  ledcWrite(PWMB, TURN_SPEED);
}

void turnRightContinuous() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);  ledcWrite(PWMA, TURN_SPEED);
  digitalWrite(BIN1, LOW);  digitalWrite(BIN2, HIGH); ledcWrite(PWMB, TURN_SPEED);
}

// ============================================================================
// SENSOR FUNCTIONS
// ============================================================================
float getSingleReading(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long dur = pulseIn(echoPin, HIGH, 12000);
  if (dur == 0) return 999;
  return (dur / 2.0) * 0.0343;
}

float measureDistance(int trigPin, int echoPin) {
  float a = getSingleReading(trigPin, echoPin); delay(10);
  float b = getSingleReading(trigPin, echoPin); delay(10);
  float c = getSingleReading(trigPin, echoPin);
  return (a + b + c) / 3.0;
}

void scanAllDirections(float d[3]) {
  delayWithMonitoring(60); d[0] = measureDistance(TRIG_LEFT,   ECHO_LEFT);
  delayWithMonitoring(60); d[1] = measureDistance(TRIG_CENTER, ECHO_CENTER);
  delayWithMonitoring(60); d[2] = measureDistance(TRIG_RIGHT,  ECHO_RIGHT);
}

void makeDecision(float d[3], bool leftWall, bool rightWall) {
  (void)leftWall;
  (void)rightWall;
  float mx = d[0];
  if (d[1] > mx) mx = d[1];
  if (d[2] > mx) mx = d[2];

  if      (d[1] >= mx) return;      // center is clearest, keep going
  else if (d[0] >= mx) turnRight(); // left is clearest, turn right
  else if (d[2] >= mx) turnLeft();  // right is clearest, turn left
  else                 turnAround();
}
