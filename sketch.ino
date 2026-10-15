#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

// 3x3 test grid. Each pushbutton stands in for the Hall sensor under one cell.
const int cellPins[9] = {13, 12, 14, 27, 26, 25, 33, 32, 16};
#define CONFIRM_PIN 4
#define BUZZ_PIN 18
#define LED_PIN 19

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
Adafruit_NeoPixel px(9, LED_PIN, NEO_GRB + NEO_KHZ800);

int pawn = -1;   // cell index 0..8, -1 = not placed
int player = 0;  // 0 = blue, 1 = red

bool adjacent(int a, int b) {
  return abs(a / 3 - b / 3) + abs(a % 3 - b % 3) == 1;
}

void show() {
  px.clear();
  if (pawn >= 0) {
    for (int i = 0; i < 9; i++)
      if (adjacent(pawn, i)) px.setPixelColor(i, px.Color(0, 80, 0));  // legal moves = green
    px.setPixelColor(pawn, player ? px.Color(100, 0, 0) : px.Color(0, 0, 100));
  }
  px.show();
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("QUORIDOR 3x3 test");
  oled.print("Turn: ");
  oled.println(player ? "Player 2 (red)" : "Player 1 (blue)");
  oled.print("Pawn cell: ");
  if (pawn >= 0) oled.println(pawn + 1); else oled.println("-");
  oled.println("Green = legal moves");
  oled.println("Yellow btn = end turn");
  oled.display();
}

void setup() {
  for (int i = 0; i < 9; i++) pinMode(cellPins[i], INPUT_PULLUP);
  pinMode(CONFIRM_PIN, INPUT_PULLUP);
  pinMode(BUZZ_PIN, OUTPUT);
  Wire.begin(21, 22);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  px.begin();
  show();
}

void loop() {
  for (int i = 0; i < 9; i++) {
    if (digitalRead(cellPins[i]) == LOW) {
      if (pawn < 0 || adjacent(pawn, i)) {
        pawn = i;
        tone(BUZZ_PIN, 1200, 60);
        show();
      } else {
        tone(BUZZ_PIN, 200, 200);  // illegal move
      }
      while (digitalRead(cellPins[i]) == LOW) delay(10);
    }
  }
  if (digitalRead(CONFIRM_PIN) == LOW) {
    player ^= 1;
    tone(BUZZ_PIN, 800, 100);
    show();
    while (digitalRead(CONFIRM_PIN) == LOW) delay(10);
  }
}
