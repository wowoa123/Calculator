#include "Calculator.h"

Calculator::Calculator(uint8_t rs, uint8_t rw, uint8_t enable,
                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                       char keys[4][4], byte row[], byte col[],
                       byte rows, byte cols):mlcd(rs, rw, enable, d0, d1, d2, d3),
                       mcustomKeypad(makeKeymap(keys), row, col, rows, cols),
                       result(0), num_size(0), sign_size(0)
{
    for (int i = 0; i != max; ++i)
    {
        data[i] = 0;
        sign[i] = 0;
    }
}

LiquidCrystal *Calculator::returnLcd()
{
    return &mlcd;
}

Keypad *Calculator::returnKeypad()
{
    return &mcustomKeypad;
}

double Calculator::setResult(double i)
{
    result = i;
    return result;
}

void Calculator::reset()
{
    for (int i = 0; i != max; ++i)
        data[i] = 0;
    result = 0;
    num_size = 0;
}

double Calculator::mplus(int a, int b)
{
    double r = data[a] + data[b];
    data[a] = r;
    data[b] = 0;
    //去掉零值
    for (int i = b; i != num_size; ++i)
        data[i] = data[i + 1];
    num_size -= 1;
    //去掉对应符号
    for (int i = a; i != sign_size; ++i)
        sign[i] = sign[i + 1];
    sign_size -= 1;
    return r;
}

double Calculator::msub(int a, int b)
{
    double r = data[a] - data[b];
    data[a] = r;
    data[b] = 0;
    //去掉零值
    for (int i = b; i != num_size; ++i)
        data[i] = data[i + 1];
    num_size -= 1;
    //去掉对应符号
    for (int i = a; i != sign_size; ++i)
        sign[i] = sign[i + 1];
    sign_size -= 1;
    return r;
}

double Calculator::mmult(int a, int b)
{
    double r = data[a] * data[b];
    data[a] = r;
    data[b] = 0;
    //去掉零值
    for (int i = b; i != num_size; ++i)
        data[i] = data[i + 1];
    num_size -= 1;
    //去掉对应符号
    for (int i = a; i != sign_size; ++i)
        sign[i] = sign[i + 1];
    sign_size -= 1;
    return r;
}

double Calculator::mdiv(int a, int b)
{
    double r = data[a] / data[b];
    data[a] = r;
    data[b] = 0;
    //去掉零值
    for (int i = b; i != num_size; ++i)
        data[i] = data[i + 1];
    num_size -= 1;
    //去掉对应符号
    for (int i = a; i != sign_size; ++i)
        sign[i] = sign[i + 1];
    sign_size -= 1;
    return r;
}

void Calculator::data_init(char ch[], int ch_size)
{
    int begin = 0;
    int end = ch_size;

    while (begin != end)
    {
        begin = num_begin(ch, begin, end);

        if (begin != end)
        {
            int after = num_end(ch, begin, end);
            data[num_size++] = charToNum(ch, begin, after);
            begin = after;
        }
    }

    for (int i = 0; i != ch_size; ++i)
    {
        if (!notOp(ch[i]))
            sign[sign_size++] = ch[i];
    }

    for (int i = 0; i != num_size; ++i)
    {
        Serial.println(data[i]);
    }
}

double Calculator::calculator()
{
    int i = 0;
    while (i != sign_size)
    {
        if (sign[i] == '*')
            mmult(i, i + 1);
        else if (sign[i] == '/')
            mdiv(i, i + 1);
        else
            i += 1;
    }

    i = 0;
    while (i != sign_size)
    {
        if (sign[i] == '+')
            mplus(i, i + 1);
        else if (sign[i] == '-')
            msub(i, i + 1);
        else
            i += 1;
    }

    result += data[0];
    return result;
}

int enter(LiquidCrystal *lcd, Keypad *customKeypad, char ch[], int ch_size)
{
    int i = 0;
    //确认是否按下等号
    bool flag = false;
    while (!flag)
    {
        char key = 0;
        while (true)
        {
            key = customKeypad->getKey();
            if (key != 0)
                break;
        }
        switch (key)
        {
         case '=':
            flag = true;
            break;
         default:
            if (i != ch_size)
            {
                ch[i++] = key;
                lcd->print(key);
                if (i != ch_size - 1)
                {
                    lcd->setCursor(i, 0);
                }
            }
        }
    }

    return i;
}

int num_begin(char ch[], int begin, int end)
{
    for (int i = begin; i != end; ++i)
    {
        if (notOp(ch[i]))
            return i;
    }
    return end;
}

int num_end(char ch[], int begin, int end)
{
    if (!notOp(ch[begin]) && begin == 0)
        return num_end(ch, begin + 1, end);
    for (int i = begin; i != end; ++i)
    {
        if (!notOp(ch[i]))
            return i;
    }
    return end;
}

bool notOp(char ch)
{
    static const char op[4] = {'+', '-', '*', '/'};
    for (int i = 0; i != 4; ++i)
    {
        if (ch == op[i])
            return false;
    }
    return true;
}

double charToNum(char ch[], int begin, int end)
{
    double tmp[end - begin] = {0};
    int dot = 0;
    bool no_dot = true;
    for (int i = 0, j = begin; i != (end - begin); ++i, ++j)
    {
        if (ch[j] == '.')
        {
            tmp[i] = 0;
            dot = i;
            no_dot = false;
        }
        else
            tmp[i] = ch[j] - '0';
    }

    if (no_dot)
    {
        for (int i = 0; i != (end - begin); ++i)
        {
            for (int j = 0; j != ((end - begin) - i - 1); ++j)
            {
                tmp[i] *= 10;
            }
        }
    }
    else
    {
        for (int i = 0; i != dot; ++i)
        {
            for (int j = 0; j != (dot - i - 1); ++j)
            {
                tmp[i] *= 10;
            }
        }

        for (int i = dot + 1; i != (end - begin); ++i)
        {
            for (int j = dot; j != i; ++j)
            {
                tmp[i] /= 10;
            }
        }
    }

    double r = 0;
    for (int i = 0; i != (end - begin); ++i)
    {
        r += tmp[i];
    }

    return r;
}
