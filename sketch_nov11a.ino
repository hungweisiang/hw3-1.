int R = 3;
int G = 5;
int B = 6;
int button = 2;

int mode = 0;
int lastReading = LOW;
int buttonState = LOW;

unsigned long debounceTime = 0;
unsigned long lightTime = 0;

int phase = 0;
int rainbow = 0;

void color(int r, int g, int b) {
  analogWrite(R, 255 - r);
  analogWrite(G, 255 - g);
  analogWrite(B, 255 - b);
}

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(button, INPUT);

  color(255, 255, 255);
}

void loop() {

  int reading = digitalRead(button);

  if (reading != lastReading) {
    debounceTime = millis();
  }

  if (millis() - debounceTime > 50) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        mode = (mode + 1) % 4;
        phase = 0;
        lightTime = millis();
      }
    }
  }

  lastReading = reading;

  // 模式0：彩虹漸變
  if (mode == 0) {
    if (millis() - lightTime >= 15) {
      lightTime = millis();
      rainbow++;

      if (rainbow >= 768) rainbow = 0;

      if (rainbow < 256) {
        color(255, rainbow, 0);
      }
      else if (rainbow < 512) {
        color(511 - rainbow, 255, rainbow - 256);
      }
      else {
        color(0, 767 - rainbow, 255);
      }
    }
  }

  // 模式1：彩色慢速交替
  else if (mode == 1) {
    if (millis() - lightTime >= 500) {
      lightTime = millis();
      phase++;
    }

    int colors[][3] = {
      {255, 0, 0},
      {255, 100, 0},
      {255, 255, 0},
      {0, 255, 0},
      {0, 0, 255},
      {150, 0, 255},
      {255, 255, 255}
    };

    int i = phase % 7;
    color(colors[i][0], colors[i][1], colors[i][2]);
  }

  // 模式2：彩色快速閃爍
  else if (mode == 2) {
    if (millis() - lightTime >= 150) {
      lightTime = millis();
      phase++;
    }

    int colors[][3] = {
      {255, 0, 0},
      {0, 255, 0},
      {0, 0, 255},
      {255, 255, 0},
      {255, 0, 255},
      {0, 255, 255}
    };

    int i = phase % 6;
    color(colors[i][0], colors[i][1], colors[i][2]);
  }

  // 模式3：啦啦隊派對燈光
  else if (mode == 3) {
    if (millis() - lightTime >= 100) {
      lightTime = millis();
      phase++;
    }

    int colors[][3] = {
      {255, 0, 0},
      {255, 255, 255},
      {0, 0, 255},
      {255, 0, 255},
      {0, 255, 0},
      {255, 255, 0},
      {0, 255, 255},
      {0, 0, 0}
    };

    int i = phase % 8;
    color(colors[i][0], colors[i][1], colors[i][2]);
  }
}