#include <iostream>
#include <string>
#include<limits>
#include "Card.hpp"
using namespace std;

/* Задание №1. Создать программу, которая считывает целое число типа int.
И поставить «защиту от дурака»: если пользователь вводит что-то кроме одного целочисленного значения,
нужно вывести сообщение об ошибке и предложить ввести число еще раз. */

void intCheck()
{
    int a;
    cout << "Enter an integer number: " << endl;
    cin >> a;
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"You have entered wrong input"<<endl;
            cout << "Enter an integer again: " << endl;
            cin>>a;
        }
        if(!cin.fail())
        break;
    }
    cout << "the number is: " << a << endl;
    return;
}

// Задание №2. Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода строки и сбрасывает буфер.

template< class CharT, class Traits >
basic_ostream<CharT, Traits>& endll( basic_ostream<CharT, Traits>& os )
{
    os.put(os.widen('\n'));
    os.put(os.widen('\n'));
    os.flush();

    return os;
}

/* Задание №3. Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода:

• virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса.
  Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false.
• void Win() const- выводит на экран имя игрока и сообщение, что он выиграл.
• void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
• void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью. */

class Player : public GenericPlayer
{
public:
    Player(const string& name = "") : GenericPlayer(name) {}
    virtual ~Player();
    virtual bool IsHitting() const
    {
        cout << m_Name << "One more card? (Y/N): ";
        char answer;
        cin >> answer;
        return (answer == 'y' || answer == 'Y');
    }
    void Win() const { cout << m_Name << " wins.\n"; }
    void Lose() const { cout << m_Name << " loses.\n"; }
    void Push() const{ cout << m_Name << " pushes.\n"; }
};

/* Задание №4. Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
• virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта. Если у дилера не больше 16 очков, то он берет еще одну карту.
• void FlipFirstCard() - метод переворачивает первую карту дилера. */

class House : public GenericPlayer
{
    House(const string& name = "House");
    virtual ~House();
    virtual bool IsHitting() const { return (GetSum() <= 16);}
    void FlipFirstCard()
    {
        if (!(Cards.empty()))
        {
            Cards[0]->Flip();
        }
        else
        {
            cout << "No card to flip!\n";
        }
    }
};

/* Задание №5. Написать перегрузку оператора вывода для класса Card.
Если карта перевернута рубашкой вверх (мы ее не видим), вывести ХХ, если мы ее видим, вывести масть и номинал карты.
Также для класса GenericPlayer написать перегрузку оператора вывода, который должен отображать имя игрока и его карты, а также общую сумму очков его карт. */

ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9",
                           "10", "J", "Q", "K"};
    const string SUITS[] = {"c", "d", "h", "s"};
    if (aCard.IsFaceUp)
        os << RANKS[aCard.Rank] << SUITS[aCard.Suit];
    else
        os << "XX";
    return os;
}

int main()
{
    cout << '\n';
    cout << "Task 1." << endl;
    intCheck();

    cout << '\n';
    cout << "Task 2." << endl;
    cout << "Hello" << endll << "world" << endll;
    return 0;
}
