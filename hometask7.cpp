#include <iostream>
#include "Card.hpp"
using namespace std;

/* Задание №1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям.
Перегрузите оператор вывода для данного класса. Создайте два "умных" указателя today и date.
Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы доступа к полям класса Date,
а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода. Затем переместите ресурс,
которым владеет указатель today в указатель date.
Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль. */

class Date
{
private:
    int m_day;
    int m_month;
    int m_year;
public:
    Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}

    int getDay() { return m_day; }
    int getMonth() { return m_month; }
    int getYear() { return m_year; }
    friend ostream& operator<< (ostream &out, const Date &date)
    {
        out << "Date: " << date.m_day << ". " << date.m_month << ". " << date.m_year << "\n";
        return out;
    }
};

template <typename T>
class Smartpointer
{
private:
	T* m_ptr;
public:
	Smartpointer(T* ptr = nullptr) : m_ptr(ptr) {}
	~Smartpointer() { delete m_ptr; }

	Smartpointer(Smartpointer& a)
	{
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
	}

	Smartpointer& operator=(Smartpointer& a)
	{
		if (&a == this)
			return *this;

		delete m_ptr;
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }

	bool isNull() const { return m_ptr == nullptr; }
};

/* Задание №2. По условию предыдущей задачи создайте два умных указателя date1 и date2.

• Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой (сравнение происходит по датам).
  Функция должна вернуть более позднюю дату.
• Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.

Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров. */

const Smartpointer<Date>& compareDates(const Smartpointer<Date>& b, const Smartpointer<Date>& c)
{
	if (b->getYear() > c->getYear())
		return b;
	else if (b->getYear() < c->getYear())
		return c;
	else
	{
		if (b->getMonth() > c->getMonth())
			return b;
		else if (b->getMonth() < c->getMonth())
			return c;
		else
		{
			if (b->getDay() > c->getDay())
				return b;
			else
				return c;
		}
	}
}

void swap(Smartpointer<Date>& b, Smartpointer<Date>& c)
{
	Smartpointer<Date> temp(b);
	b = c;
	c = temp;
}

/* Задание №3. Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. Класс Deck имеет 4 метода:

• vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
• void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
• vold Deal (Hand& aHand) - метод, который раздает в руку одну карту
• void AddltionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать */

class Deck : public Hand
{
public:
	Deck()
	{
	    m_Cards.reserve(52);
	    Populate();
	}

    virtual ~Deck() {}

    void Populate()
    {
        Clear();
        for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
        {
            for (int r = Card::ACE; r <= Card::KING; ++r)
                Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }

    void Shuffle()
    {
        random_shuffle(m_Cards.begin(), m_Cards.end());
    }

    void Deal(Hand& aHand)
    {
        if (!m_Cards.empty())
        {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else
            cout << "Out of cards. Unable to deal.";
    }

    void AdditionalCards(GenericPlayer& aGenericPlayer)
    {
        cout << endl;
        while ( !(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting() )
        {
            Deal(aGenericPlayer);
            cout << aGenericPlayer << endl;

            if (aGenericPlayer.IsBusted())
                aGenericPlayer.Bust();
        }
    }
};

// Задание №4. Реализовать класс Game, который представляет собой основной процесс игры.

class Game
{
public:
	Game(const vector<string>& names)
	{
	    vector<string>::const_iterator pName;
	    for (pName = names.begin(); pName != names.end(); ++pName)
		{
	        m_Players.push_back(Player(*pName));
		}

		srand(static_cast<unsigned int>(time(0)));
	    m_Deck.Populate();
	    m_Deck.Shuffle();
	}

    ~Game() {}

    void Play()
    {
        vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i)
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                m_Deck.Deal(*pPlayer);

            m_Deck.Deal(m_House);
        }

        m_House.FlipFirstCard();

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            cout << *pPlayer << endl;

        cout << m_House << endl;

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            m_Deck.AdditionalCards(*pPlayer);

        m_House.FlipFirstCard();
        cout << endl << m_House;

        m_Deck.AdditionalCards(m_House);

        if (m_House.IsBusted())
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    		{
                if ( !(pPlayer->IsBusted()) )
                    pPlayer->Win();
    		}
        }
        else
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if ( !(pPlayer->IsBusted()) )
                {
                    if (pPlayer->GetTotal() > m_House.GetTotal())
                        pPlayer->Win();
                    else if (pPlayer->GetTotal() < m_House.GetTotal())
                        pPlayer->Lose();
                    else
                        pPlayer->Push();
                }
            }

        }

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            pPlayer->Clear();

        m_House.Clear();
    }

private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

int main()
{
	cout << '\n' << "Task 1.\n" << endl;
	Smartpointer<Date> today(new Date(9, 03, 2022));

	cout << "Day: " << today->getDay() << endl;
	cout << "Month: " << today->getMonth() << endl;
	cout << "Year: " << today->getYear() << endl;
	cout << *today << endl;

	Smartpointer<Date> date;

	cout << "today is " << (today.isNull() ? "null\n" : "not null\n");
	cout << "date is " << (date.isNull() ? "null\n" : "not null\n");

	date = today;

	cout << "today is " << (today.isNull() ? "null\n" : "not null\n");
	cout << "date is " << (date.isNull() ? "null\n" : "not null\n");

	cout << *date << endl;

	cout << '\n' << "Task 2.\n" << endl;

	Smartpointer<Date> date1(new Date(6, 12, 2021));
	Smartpointer<Date> date2(new Date(15, 04, 2022));
	Smartpointer<Date> date3(new Date(21, 01, 2023));

	cout << *compareDates(date1, date2) << endl;
	swap(date2, date3);
	cout << *compareDates(date1, date2) << endl;

	cout << "\t\tWelcome to Blackjack!\n\n";
	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7)
	{
		cout << "How many players? (1 - 7): ";
		cin >> numPlayers;
	}
	vector<string> names;
	string name;
	for (int i = 0; i < numPlayers; ++i)
	{
		cout << "Enter player name: ";
		cin >> name;
		names.push_back(name);
	}
	cout << endl;
	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		aGame.Play();
		cout << "\nDo you want to play again? (Y/N): ";
		cin >> again;
	}
    return 0;
}
