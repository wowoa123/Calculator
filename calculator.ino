#include <Calculator.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <MsTimer2.h>

const int max_size = 16;
const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {{'7', '8', '9', '/'},
                         {'4', '5', '6', '*'},
                         {'1', '2', '3', '-'},
                         {'0', '.', '=', '+'}};

byte row[rows] = {14, 15, 16, 17};
byte col[cols] = {2, 3, 4, 5};

Calculator calu(10, 11, 12, 6, 7, 8, 9, keys, row, col, rows, cols);
LiquidCrystal * lcd = calu.returnLcd();
Keypad * customKeypad = calu.returnKeypad();

void setup() {
  // put your setup code here, to run once:
  lcd->begin(16, 2);
  lcd->setCursor(0, 0);
  Serial.begin(9600);
}

void loop() {
  char in[max_size] = {0};
  int in_size = enter(lcd, customKeypad, in, max_size);
  calu.data_init(in, in_size);
  lcd->setCursor(0, 1);
  double r = calu.calculator();
  lcd->print(r);
  char key = 0;
  bool flag = false;
  while (!flag)
  {
    key = customKeypad->getKey();
    if (!notOp(key))
    {
      lcd->clear();
      lcd->setCursor(0, 0);
      lcd->print("Ans");
      lcd->setCursor(3, 0);
      lcd->print(key);
      lcd->setCursor(4, 0);
      calu.reset();
      calu.setResult(r);
      flag = true;
    }
    else if (key != 0)
    {
      lcd->clear();
      lcd->setCursor(0, 0);
      calu.reset();
      flag = true;
    }
  }
}

