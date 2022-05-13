#include <iostream>
#include <cmath>
#include <cstdint>
#include <cassert>

using namespace std;

/* Задание №1.Создать класс Power, который содержит два вещественных числа. Этот класс должен иметь две переменные-члена для хранения этих вещественных чисел.
Еще создать два метода: один с именем set, который позволит присваивать значения объявленным в классе переменным, второй — calculate,
который будет выводить результат возведения первого числа в степень второго числа. Задать значения этих двух чисел по умолчанию.*/

class Power
{
private:
    int num1 = 5;
    int num2 = 6;

public:

    Power() = default;

    void setNumber(int _num1, int _num2)
    {
        num1 = _num1;
        num2 = _num2;
    }

    void calculateNumber()
    {
        cout << "the result is: " << pow(num1,num2) << endl;

    }

};

/* Задание №2. Написать класс с именем RGBA, который содержит 4 переменные-члена типа std::uint8_t: m_red, m_green, m_blue и m_alpha
(#include cstdint для доступа к этому типу). Задать 0 в качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha.
Создать конструктор со списком инициализации членов, который позволит пользователю передавать значения для m_red, m_blue, m_green и m_alpha.
Написать функцию print(), которая будет выводить значения переменных-членов.*/

class RGBA
{
private:
std::uint8_t m_red = 0;
std::uint8_t m_green = 0;
std::uint8_t m_blue = 0;
std::uint8_t m_alpha = 255;

public:
    RGBA(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 255)
    { m_red = red; m_green = green; m_blue = blue, m_alpha = alpha;};

    void print()
    {
        cout << "Red RGBA = " << static_cast<int>(m_red) << '\n';
        cout << "Green RGBA = " << static_cast<int>(m_green) << '\n';
        cout << "Blue RGBA = " << static_cast<int>(m_blue) << '\n';
        cout << "Alpha RGBA = " << static_cast<int>(m_alpha) << '\n';
    }

};

// Задание №3. Написать класс, который реализует функциональность стека.

class Stack
{
private:
    int array[10];
    int stacklength;

public:
    void reset()
    {
        stacklength = 0;
        for(int i = 0; i < 10; i++)
        {
            array[i] = 0;
        }
    }

    bool push(int val)
    {
        if(stacklength == 10)
            return false;
		array[stacklength++] = val;
		return true;
    }

    int pop()
    {
        assert (stacklength > 0);
		return array[--stacklength];
    }

    void printt()
    {
        cout << " ( ";
        for(int i = 0; i < stacklength; i++)
            {
                cout << array[i];
            }
        cout << " ) \n";
    }
};

int main()
{

/* Задание №1.Создать класс Power, который содержит два вещественных числа. Этот класс должен иметь две переменные-члена для хранения этих вещественных чисел.
Еще создать два метода: один с именем set, который позволит присваивать значения объявленным в классе переменным, второй — calculate,
который будет выводить результат возведения первого числа в степень второго числа. Задать значения этих двух чисел по умолчанию.*/

    cout << "Task 1." << endl;
    Power a;
    a.calculateNumber();
    a.setNumber(3, 4);
    a.calculateNumber();

/* Задание №2. Написать класс с именем RGBA, который содержит 4 переменные-члена типа std::uint8_t: m_red, m_green, m_blue и m_alpha
(#include cstdint для доступа к этому типу). Задать 0 в качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha.
Создать конструктор со списком инициализации членов, который позволит пользователю передавать значения для m_red, m_blue, m_green и m_alpha.
Написать функцию print(), которая будет выводить значения переменных-членов.*/

    cout << '\n';
    cout << "Task 2." << endl;
    RGBA color(0, 128, 128);
    color.print();


// Задание №3. Написать класс, который реализует функциональность стека.

    cout << '\n';
    cout << "Task 3." << endl;
    Stack stack;
    stack.reset();
    stack.printt();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.printt();

    stack.pop();
    stack.printt();

    stack.pop();
    stack.pop();
    stack.printt();

    return 0;
}
