#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <set>
#include "Card.hpp"

using namespace std;

/* Задание №1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
• для удаления последнего элемента массива (аналог функции pop_back() в векторах)
• для удаления первого элемента массива (аналог pop_front() в векторах)
• для сортировки массива
• для вывода на экран элементов.*/

class ArrayInt
{
private:
    int m_length;
    int* m_data;
public:
    ArrayInt(): m_length(0), m_data(nullptr) {}
    ArrayInt(int length) : m_length(length)
    {
        assert(length >= 0);
        if(length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }
    void m_sort(int* m_data, int first, int last)
    {
        int i = first, j = last;
        int temp;
        int x = m_data[(first + last) / 2];
        do
        {
            while (m_data[i] < x) i++;
            while (m_data[j] > x) j--;
            if (i <= j)
            {
                if (i < j)
                {
                    temp=m_data[i];
                    m_data[i]=m_data[j];
                    m_data[j]=temp;
                }
                i++;
                j--;
            }
        }
        while (i <= j);
            if (i < last)
                m_sort(m_data, i, last);
            if (first < j)
                m_sort(m_data, first,j);
    }
    void sort() { m_sort(m_data, 0, m_length - 1); }

    ~ArrayInt() { delete[] m_data; }
    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }
    int getLength() { return m_length;}
    void resize(int new_length)
    {
        if(m_length <=0)
        {
            erase();
            return;
        }
        int* newData = new int[new_length];
        int CopyElements = 0;
        if(new_length > m_length)
            CopyElements = m_length;
        else CopyElements = new_length;
        for(size_t i = 0; i < CopyElements; i++)
        {
            newData[i] = m_data[i];
        }
        delete[]m_data;
        m_data = newData;
        m_length = new_length;
    }
    void pop_back() { resize(m_length - 1);}
    void pop_front()
    {
    	int *data = new int[m_length - 1];
        for (int index=1; index < m_length ; ++index)
            data[index - 1] = m_data[index];
        delete[] m_data;
        m_data = data;
        --m_length;
    }
    void at(int index, int data)
    {
        if(index>=0 && index<=m_length)
            m_data[index] = data;
    }
    void push_back(int value)
    {
        int* newData = new int[m_length + 1];
        int CopyElements = m_length;
        for(size_t i = 0; i < CopyElements; i++)
        {
            newData[i] = m_data[i];
        }
        newData[m_length] = value;
        delete[]m_data;
        m_data = newData;
        m_length++;
    }
    friend ostream& operator<<(ostream&, ArrayInt&);
    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }
};

ostream& operator<<(ostream& s, ArrayInt& f)
{
    int length = f.getLength();
    for (int i = 0; i < length; ++i)
        { s << f[i] << (((length == 1) || (length - 1 == i)) ? "" : ", "); }
    return s;
}

/* Задание №3. Реализовать класс Hand, который представляет собой коллекцию карт. В классе будет одно поле:
вектор указателей карт (удобно использовать вектор, т.к. это по сути динамический массив,
а тип его элементов должен быть - указатель на объекты класса Card). Также в классе Hand должно быть 3 метода:

• метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
• метод Clear, который очищает руку от карт
• метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть возможность того, что туз может быть равен 11).*/

class Hand
{
protected:
    vector<Card*> Cards;
public:
    Hand(){};
    void Add(Card* pCard) { Cards.push_back(pCard); }
    void Clear();
    {
        vector<Card*>::iterator it = Cards.begin();
        for (it = Cards.begin(); it != Cards.end(); ++it)
        {
            delete *it;
            *it = nullptr;
        }
        Cards.clear();
    }
    int GetSum()
    {
        int summ = 0;
        vector<Card*>::const_iterator it;
        for (it = Cards.begin(); it != Cards.end(); ++iter)
        { summ += (*it)->GetValue(); }
        return summ;
    }
};

int main()
{
    cout << "Task No.1" << endl;
    cout << '\n';
	ArrayInt A;
	A.push_back(26);
	A.push_back(19);
	A.push_back(65);
	A.push_back(43);
	A.push_back(27);
	cout << "Original array: " << A << endl;
	A.sort();
	cout << "Sorted array: " << A << endl;
	A.pop_back();
	cout << "After deleting the last element: " << A << endl;
	A.pop_front();
	cout << "After deleting the first element: " << A << endl;

    // Задание №2. Дан вектор чисел, требуется выяснить, сколько среди них различных. Постараться использовать максимально быстрый алгоритм.
    cout << "Task No.2" << endl;
    cout << '\n';
    vector<int> v = {2, 2, 5, 6, 8, 9, 4, 3, 6, 8, 7};
	set<int> s(v.begin(), v.end());
	cout << s.size() << " different values in " << v.size() << endl;
    return 0;
}
