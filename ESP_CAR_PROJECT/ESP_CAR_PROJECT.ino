#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int RFF = D1;
int RFB = D2;
int RBF = D3;
int RBB = D4;
int LFF = D5;
int LFB = D6;
int LBF = D7;
int LBB = D8;

ESP8266WebServer server(80);
char command = '0';

void sendUI() {
  //UI CODE IS WRITTEN BY CHAT GPT I DECIDED AND CODED LOGIC
  server.send(200, "text/html", R"rawliteral(
// ===========================================================
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Wireless Gamepad</title>
  <style>
    body {
      font-family: sans-serif;
      background: #111;
      color: #0f0;
      display: flex;
      flex-direction: column;
      align-items: center;
      user-select: none;
      -webkit-user-select: none;
      touch-action: manipulation;
    }
    h1 { margin-top: 20px; }
    .buttons {
      margin-top: 30px;
      display: grid;
      grid-template-columns: 80px 80px 80px;
      gap: 10px;
    }
    button {
      padding: 20px;
      font-size: 20px;
      cursor: pointer;
      background: #222;
      color: #0f0;
      border: 2px solid #0f0;
      border-radius: 10px;
    }
    #debug {
      margin-top: 30px;
      padding: 10px;
      background: #222;
      border: 1px solid #0f0;
      width: 250px;
      text-align: center;
    }
  </style>
</head>
<body>
  <h1>Gamepad UI</h1>
  <div class="buttons">
    <div></div>
    <button id="btnU">↑</button>
    <div></div>

    <button id="btnL">←</button>
    <button id="btnS">○</button>
    <button id="btnR">→</button>

    <div></div>
    <button id="btnD">↓</button>
    <div></div>
  </div>
  <div id="debug">Waiting...</div>

<script>
  let uiCommand = '0';
  let lastSent = '';
  let manualControl = false;
  let lastGamepadCommand = '0';

  function send(cmd) {
    if (cmd !== lastSent) {
      document.getElementById('debug').innerText = `Sent: ${cmd}`;
      lastSent = cmd;
    }

    fetch(`/${cmd}`).catch(() => {
      document.getElementById('debug').innerText = "Failed to send";
    });
  }

  const bindings = {
    'up': 'U',
    'down': 'D',
    'left': 'L',
    'right': 'R',
    'a': 'A',
    'b': 'B',
    'x': 'X',
    'y': 'Y'
  };

  function press(key) {
    manualControl = true;
    uiCommand = bindings[key];
    send(uiCommand);
  }

  function release() {
    manualControl = false;
    send('0'); // Stop signal
  }

  document.getElementById('btnU').addEventListener('touchstart', () => press('up'));
  document.getElementById('btnD').addEventListener('touchstart', () => press('down'));
  document.getElementById('btnL').addEventListener('touchstart', () => press('left'));
  document.getElementById('btnR').addEventListener('touchstart', () => press('right'));
  document.getElementById('btnS').addEventListener('touchstart', () => press('a'));

  document.getElementById('btnU').addEventListener('touchend', release);
  document.getElementById('btnD').addEventListener('touchend', release);
  document.getElementById('btnL').addEventListener('touchend', release);
  document.getElementById('btnR').addEventListener('touchend', release);
  document.getElementById('btnS').addEventListener('touchend', release);

  window.addEventListener("gamepadconnected", () => {
    setInterval(() => {
      if (manualControl) return;

      const gp = navigator.getGamepads()[0];
      if (!gp) return;

      let ly = gp.axes[1];
      let rx = gp.axes[2];
      let cmd = '0';

      if (ly < -0.5) cmd = 'U';
      else if (ly > 0.5) cmd = 'D';
      else if (rx < -0.5) cmd = 'L';
      else if (rx > 0.5) cmd = 'R';

      // Fix: Only send if the command has changed
      if (cmd !== lastGamepadCommand) {
        uiCommand = cmd;
        send(cmd);
        lastGamepadCommand = cmd;
      }
    }, 50); // Reduced interval for faster response
  });
</script>

</body>
</html>

)rawliteral");
}

void handleCommand() {
  String path = server.uri();
  if (path.length() == 2) {
    command = path.charAt(1);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP("ESP-8266", "12345678");
  server.on("/", sendUI);
  server.onNotFound(handleCommand);
  server.begin();
  //pin set up
  int pins[] = {RFF, RFB, RBF, RBB, LFF, LFB, LBF, LBB};
  for (int i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
}
}
//change power1 to change motor speed upto 1023
void start(
  int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1,
  int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1,
  int power1 = 500, int power2 = 0
) {
  if (pin1 != -1) analogWrite(pin1, power1);
  if (pin2 != -1) analogWrite(pin2, power2);
  if (pin3 != -1) analogWrite(pin3, power1);
  if (pin4 != -1) analogWrite(pin4, power2);
  if (pin5 != -1) analogWrite(pin5, power1);
  if (pin6 != -1) analogWrite(pin6, power2);
  if (pin7 != -1) analogWrite(pin7, power1);
  if (pin8 != -1) analogWrite(pin8, power2);


}


void loop() {
  server.handleClient();

  switch (command) {
  case 'U':
    start(RFF, RFB, RBF, RBB, LFF, LFB, LBF, LBB);
    break;
  case 'D':
    start(RFB, RFF, RBB, RBF ,LFB ,LFF ,LBB ,LBF);
    break;
  case 'R':
    start(RFF, RFB, RBF, RBB,LFB ,LFF ,LBB ,LBF);
    break;
  case 'L':
    start(RFB, RFF, RBB, RBF ,LFF , LFB, LBF, LBB);
    break;
  case '0':
    start(RFF, RFB, RBF, RBB, LFF, LFB, LBF, LBB,0);
    break;
}

}
