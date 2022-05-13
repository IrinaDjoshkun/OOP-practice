#include <iostream>
#include "Card.hpp"
using namespace std;

/* Задание №1. Реализовать шаблон класса Pair1,
который позволяет пользователю передавать данные одного типа парами.*/

template<class T>
class Pair1
{
private:
    T* arrayData;
public:
    Pair1(T v1, T v2)
    {
        arrayData = new T[2];
        *arrayData = v1;
        *(arrayData+1) = v2;
    }
    ~Pair1() { delete[] arrayData; }

    T first() const { return *arrayData; }
    T second() const { return *(arrayData+1); }
};

// Задание №2. Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.

template<class T1, class T2>
class Pair
{
protected:
    T1 m_first;
    T2 m_second;
public:
    Pair(T1 first, T2 second) : m_first(first), m_second(second) {}
    const T1 &first() const { return m_first; }
	const T2 &second() const { return m_second; }
};

/* Задание №3. Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа.
Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, а второй — любого типа данных. */

template<typename T>
class StringValuePair : public Pair <string, T>
{
public:
	StringValuePair(const string &str,const T &t) : Pair<string, T>(str,t) { }
};

/* Задание №4. Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс GenericPlayer,
который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер.
Создать класс GenericPlayer, в который добавить поле name - имя игрока. Также добавить 3 метода:

• IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
• IsBoosted() - возвращает bool значение, есть ли у игрока перебор
• Bust() - выводит на экран имя игрока и объявляет, что у него перебор. */

class GenericPlayer : public Hand
{
protected:
    string m_Name;
public:
    GenericPlayer(string name) : m_Name(name) { }
    virtual bool IsHitting() const = 0;
    bool IsBusted() const { return (GetTotal() > 21); }
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
    void Bust() const {	cout << m_Name << " перебор.\n"; }
};

int main()
{
    cout << "Task No.1" << endl;
    Pair1<int> pint(6, 9);
    cout << "Pair: " << pint.first() << ' ' << pint.second() << '\n';

    const Pair1<double> pdouble(3.4, 7.8);
    cout << "Pair: " << pdouble.first() << ' ' << pdouble.second() << '\n';

    cout << '\n';
    cout << "Task No.2" << endl;
	Pair<int, double> p1(6, 7.8);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double, int> p2(3.4, 5);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    cout << '\n';
    cout << "Task No.3" << endl;
    StringValuePair<int> svp("Amazing", 7);
    cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    return 0;
}
