自制的arduino简易计算器库，arduino ide版本为1.8.4，需要预先下载LiquidCrystal.h和Keypad.h。

用4*4按键输入，在lcd1602上显示输入和结果，使用的是四线连接模式，用的是arduino uno。

理论上可以用于其他显示屏和非4*4按键，不过需要修改头文件构造函数，类内的数据数组大小也可能需要调整。

初始化:

初始化calculator对象需要传递lcd的端口，keypad的映射图以及他的端口和他的维数。

如果使用的不是4*4按键需要修改头文件中的构造函数。

非类成员函数:

int enter(Calculator &calu, LiquidCrystal *lcd, Keypad *customKeypad, char ch[], int ch_size)
参数为calculator对象，其内的lcd和keypad对象，一个保存输入的数组和最大输入的大小，返回实际输入大小。

bool notOp(char ch)
判断是不是运算符。

bool have_error(char ch[], int ch_size)
检查输入是否有错。

类成员函数:

LiquidCrystal *returnLcd()   Keypad *returnKeypad()
返回指向calculator对象内的lcd和keypad对象的指针。

bool returnModel()
查看是不是处于累计运算模式。

bool setModel(bool b)
修改模式。

char saveSign(char ch)
保存输出Ans后的第一个运算符。

double setResult(double n)
修改对象内的结果。

void reset()
重置对象内除模式和saveSign保存的符号外的所有数据。

void data_init(char ch[], int ch_size)
初始化内置数据数组和运算符数组。

double calculator()
计算结果。
