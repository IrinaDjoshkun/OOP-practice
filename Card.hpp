#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Card
{
protected:
    enum CardRank {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE = 1};
	enum CardSuit {CLUBS, DIAMONDS, HEARTS, SPADES};
	CardRank Rank;
	CardSuit Suit;
	bool FaceUp;
public:
    Card(CardRank r, CardSuit s, bool fup) : Rank(r), Suit(s), FaceUpDown(fup) {}
    int GetValue(Card &card)
    {
        switch (card.Rank)
            {
                case TWO:		return 2;
                case THREE:		return 3;
                case FOUR:		return 4;
                case FIVE:		return 5;
                case SIX:		return 6;
                case SEVEN:		return 7;
                case EIGHT:		return 8;
                case NINE:		return 9;
                case TEN:		return 10;
                case JACK:  	return 10;
                case QUEEN:	    return 10;
                case KING:	    return 10;
                case ACE:		return 1;
            }

            return 0;
	}

	void Flip()
	{
        FaceUp = !FaceUp;
	}
};

class Hand
{
protected:
    vector<Card*> Cards;
public:
    Hand(){ Cards.reserve(7); };
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
        for (it = Cards.begin(); it != Cards.end(); ++it)
        { summ += (*it)->GetValue(); }

		bool containsAce = false;
		for (it = Cards.begin(); it != Cards.end(); ++it)
			if ((*it)->GetValue() == Card::ACE)
				containsAce = true;
		if (containsAce && total <= 11) total += 10;
        return summ;
    }
};

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


