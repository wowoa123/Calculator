自制的arduino简易计算器库，arduino ide版本为1.8.4，需要预先下载LiquidCrystal.h和Keypad.h。<br>

用4*4按键输入，在lcd1602上显示输入和结果，使用的是四线连接模式，用的是arduino uno。可以实现加减乘除四种运算，在算出结果后继续按运算符可以继续运算，按除运算符外的其他字符则清空。<br>

理论上可以用于其他显示屏和非4*4按键，不过需要修改头文件构造函数，类内的数据数组大小也可能需要调整。<br><br>

初始化:<br>
初始化calculator对象需要传递lcd的端口，keypad的映射图以及他的端口和他的维数。<br>
如果使用的不是4*4按键需要修改头文件中的构造函数。<br><br>

非类成员函数:<br>
int enter(Calculator &calu, LiquidCrystal *lcd, Keypad *customKeypad, char ch[], int ch_size)<br>
参数为calculator对象，其内的lcd和keypad对象，一个保存输入的数组和最大输入的大小，返回实际输入大小。<br><br>

bool notOp(char ch)<br>
判断是不是运算符。<br><br>

bool have_error(char ch[], int ch_size)<br>
检查输入是否有错。<br><br><br>

类成员函数:<br>
LiquidCrystal *returnLcd()<br>
Keypad *returnKeypad()<br>
返回指向calculator对象内的lcd和keypad对象的指针。<br><br>

bool returnModel()<br>
查看是不是处于累计运算模式。<br><br>

bool setModel(bool b)<br>
修改模式。<br><br>

char saveSign(char ch)<br>
保存输出Ans后的第一个运算符。<br><br>

double setResult(double n)<br>
修改对象内的结果。<br><br>

void reset()<br>
重置对象内除模式和saveSign保存的符号外的所有数据。<br><br>

void data_init(char ch[], int ch_size)<br>
初始化内置数据数组和运算符数组。<br><br>

double calculator()<br>
计算结果。<br>
