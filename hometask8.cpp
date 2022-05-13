#include <iostream>

using namespace std;

/* Задание №1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и запускать исключение DivisionByZero,
если второй параметр равен 0. В функции main выводить результат вызова функции div в консоль, а также ловить исключения. */

class DivisionByZero
{
private:
    string m_message;
public:
    DivisionByZero(string message = "") : m_message(message) {}
    string getMessage() { return m_message; }
};

namespace my
{
template <typename T>
T div (T nominator, T denominator)
{
    if(denominator == 0) throw DivisionByZero("Division by zero");

    return nominator/denominator;
}
}

/* Задание №2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, инициализирующий x значением параметра.
Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным параметром a.
Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a.
В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n.
Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0.
В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения. */

class Ex
{
public:
    double m_x;
    Ex(double x) : m_x(x) {}
};

class Bar
{
private:
    double m_y;
public:
    Bar(double y = 0.0) : m_y(y) {}
    void set(double a)
    {
        if(m_y + a > 100) throw Ex(a * m_y);
        else m_y = a;
    }
};

/* Задание №3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10,
у которого есть метод, означающий задание переместиться на соседнюю позицию.
Эти методы должны запускать классы-исключения OffTheField, если робот должен уйти с сетки, и IllegalCommand,
если подана неверная команда (направление не находится в нужном диапазоне).
Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения.
Написать функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов,
а также выводящую подробную информацию о всех возникающих ошибках. */

class OffTheField
{
	int new_x;
	int new_y;
	string message;
public:
	OffTheField(int n_x, int n_y) :	new_x(n_x), new_y(n_y), message("")
	{
		if (new_x > 10 || new_x < 1 || new_y > 10 || new_y < 1)
		{
			message += "Error! The robot is out of the field!\n";
		}
	}
	const string& getMessage() const
	{
		return message;
	}
};

class IllegalCommand
{
private:
	int cur_x;
	int cur_y;
	int new_x;
	int new_y;
	string message;
public:
	IllegalCommand(int c_x, int c_y, int n_x, int n_y) : cur_x(c_x), cur_y(c_y), new_x(n_x), new_y(n_y), message("")
	{
		if (abs(cur_x - new_x) > 1 || abs(cur_y - new_y) > 1)
		{
			message += "Error! THe step is too big! You can step for one cell only!\n";
		}
		if (cur_x == new_x || cur_y == new_y)
		{
			message += "Error! You cannot step to the same place!\n";
		}
	}
	const string& getMessage() const
	{
		return message;
	}
};

class Robot
{
private:
    int m_x, m_y;
public:
    Robot(int x = 1, int y = 1) : m_x(x), m_y(y) { cout << "The initial position of the robot is: " << m_x << ";" << m_y << endl; }
    void move(int x, int y)
    {
        m_x = x; m_y = y;
        if (abs(m_x - x) > 1 && abs(m_y - y) > 1 && (m_x == x && m_y == y))
			throw IllegalCommand(m_x, m_y, x, y);
		if (x > 10 && x < 1 && y > 10 && y < 1)
			throw OffTheField(x, y);
		cout << "The robot moved from " << m_x << ";" << m_y << " to " << x << ";" << y << endl;
    }
};


int main()
{
    cout << "\nTask 1.\n" << endl;
    try
    {
        cout << my::div(9, 3) << endl;
        cout << my::div(2.6, 1.3) << endl;
        cout << my::div (6, 0) << endl;
    }
    catch (DivisionByZero& str)
    {
        cerr << str.getMessage() << endl;
    }

    cout << "\nTask 2.\n" << endl;
    Bar a;
    int n;
    try
    {
        while(true)
        {
            cout << "Enter a number: " << endl;
            cin >> n;
            if(n == 0) break;
            a.set(n);
        }
    }
    catch (Ex& b)
    {
        cout << b.m_x << endl;
    }

    cout << "\nTask 3.\n" << endl;
	int x, y;
	Robot R;

	for(int i = 0; i < 10; i++)
	{
		std::cin >> x >> y;

		if (x == 0 && y == 0)
			break;

		try
		{
			R.move(x, y);
		}
		catch (const IllegalCommand& e)
		{
			cerr << e.getMessage() << endl;
		}
		catch (const OffTheField& e)
		{
			cerr << e.getMessage() << endl;
		}
	}

    return 0;
}
