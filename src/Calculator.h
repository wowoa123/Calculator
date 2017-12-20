#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <Keypad.h>
#include <LiquidCrystal.h>

class Calculator {
private:
    static const int max = 10;
    double data[max];
    int num_size;
    char sign[max];
    int sign_size;
    LiquidCrystal mlcd;
    Keypad mcustomKeypad;
    double result;
    bool addModel;
    char addSign;
public:
    //lcd四线模式接口和4*4按键的初始化
    Calculator(uint8_t, uint8_t, uint8_t, uint8_t,
               uint8_t, uint8_t, uint8_t, char[4][4], byte[], byte[], byte, byte);
    LiquidCrystal *returnLcd();
    Keypad *returnKeypad();
    bool returnModel();
    char returnSign();
    bool setModel(bool b);
    //累计运算时的第一个符号
    char saveSign(char ch);
    double setResult(double n);
    void reset();
    double mplus(int a, int b);
    double msub(int a, int b);
    double mmult(int a, int b);
    double mdiv(int a, int b);
    void data_init(char ch[], int ch_size);
    double calculator();
};

bool notOp(char ch);
int num_begin(char ch[], int begin, int end);
int num_end(char ch[], int begin, int end);
double charToNum(char ch[], int begin, int end);
int enter(Calculator &calu, LiquidCrystal *lcd, Keypad *customKeypad, char ch[], int ch_size);
bool have_error(char ch[], int ch_size);

#endif // CALCULATOR_H
