#include <iostream>

using namespace std;

/* Задача №1. Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг).
Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб). Для всех классов создать конструкторы.
Для класса Figure добавить чисто виртуальную функцию area() (площадь).
Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.*/

class Figure
{
private:
    int a = 0;
public:
    Figure() = default;
    virtual void area() = 0;
};

class Parallelogram : public Figure
{
protected:
    int height;
    int length;
public:
    Parallelogram(int a, int b) : height(a), length(b) {}
    virtual void area () override { cout << "The Parallelogram area is: " << height * length << endl;}
};

class Circle : public Figure
{
private:
    int R;
    int P;
public:
    Circle(int radius) : R(radius) {}
    virtual void area () override { cout << "The circle area is " << 3.14 * R * R << endl;}
};

class Rectangle : public Parallelogram
{
public:
    Rectangle(int a, int b) : Parallelogram (a,b) {}
    virtual void area () override { cout << "The Rectangle area is: " << height * length << endl;}
};

class Square : public Parallelogram
{
public:
    Square(int a, int b) : Parallelogram (a,b) {}
    virtual void area () override { cout << "The Square area is: " << height * length << endl;}
};

class Rhombus : public Parallelogram
{
public:
    Rhombus(int a, int b) : Parallelogram (a,b) {}
    virtual void area () override { cout << "The Rhombus area is: " << height * length << endl;}
};

/* Задание №2.  Создать класс Car (автомобиль) с полями company (компания) и model (модель).
Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус). От этих классов наследует класс Minivan (минивэн).
Создать конструкторы для каждого из классов, чтобы они выводили данные о классах.
Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. Обратить внимание на проблему «алмаз смерти».*/

class Car
{
protected:
    string company;
    string model;
public:
    Car(string _company, string _model) : company(_company), model(_model)
    { cout << "Car company: " << company << '\n' << "Model: " << model << endl;}
};

class PassengerCar : virtual public Car
{
public:
    PassengerCar(string _company, string _model) : Car(_company, _model)
    { cout << '\n' << "Passengers car company: " << company << '\n' << "Model: " << model << endl;}
};

class Bus : virtual public Car
{
public:
    Bus(string _company, string _model) : Car(_company, _model)
    { cout << '\n' <<  "Bus company: " << company << '\n' << "Model: " << model << endl;}
};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan(string _company, string _model) : PassengerCar(_company, _model), Bus(_company, _model), Car(_company, _model)
    { cout << '\n' <<  "Minivan company: " << company << '\n' << "Model: " << model << endl;}
};

// Задание №3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2). Предусмотреть, чтобы знаменатель не был равен 0.

class Fraction
{
protected:
    int chisl;
    int znam;
public:
    Fraction(int c = 1, int z = 1) { chisl = c; znam = z; }
    int chislitel() { return chisl; }
    int znminatel() { return znam; }

    Fraction operator+(Fraction b);
    friend Fraction operator-(Fraction a, Fraction b);
    Fraction operator-() { return Fraction(-chisl, znam);}
    friend bool operator>=(Fraction a, Fraction b);
    friend bool operator<=(Fraction a, Fraction b);
    friend bool operator==(Fraction a, Fraction b);
    friend bool operator!=(Fraction a, Fraction b);
    void print() { cout << chisl << '/' << znam; }
};

Fraction operator*(Fraction a, Fraction b);
Fraction operator/(Fraction a, Fraction b);

Fraction Fraction::operator+(Fraction b)
{
    int szn = znam * b.znam;
    int sch = chisl * b.znam + b.chisl * znam;
    Fraction sum(sch, szn);
    return sum;
}

Fraction operator-(Fraction a, Fraction b)
{
    int dzn = a.znam * b.znam;
    int ddrb = a.chisl * b.znam - b.chisl * a.znam;
    Fraction differnc(ddrb, dzn);
    return differnc;
}

Fraction operator*(Fraction a, Fraction b)
{
    int mult1 = a.chislitel() * b.chislitel();
    int mult2 = a.znminatel() * b.znminatel();
    return Fraction(mult1, mult2);
}

Fraction operator/(Fraction a, Fraction b)
{
    if(b.chislitel() == 0)
    {
        cout << "Divisor is zero" << endl;
        exit(1);
    }
    return a * Fraction(b.znminatel(), b.chislitel());
}

bool operator>=(Fraction a, Fraction b)
{
    int nc = a.chisl * b.znam;
    int mr = b.chisl * a.znam;
    if (a.znam * b.znam && nc > mr)
    {
        return true;
    }
    return false;
}

bool operator<=(Fraction a, Fraction b)
{
    int nc = a.chisl * b.znam;
    int mr = b.chisl * a.znam;
    if (a.znam * b.znam && nc < mr)
    {
        return true;
    }
    return false;
}

bool operator==(Fraction a, Fraction b)
{
    int nc = a.chisl * b.znam;
    int mr = b.chisl * a.znam;
    if (a.znam * b.znam && nc == mr)
    {
        return true;
    }
    return false;
}

bool operator!=(Fraction a, Fraction b)
{
    int nc = a.chisl * b.znam;
    int mr = b.chisl * a.znam;
    if (a.znam * b.znam && nc != mr)
    {
        return true;
    }
    return false;
}

/*  Задание №4. Создать класс Card, описывающий карту в игре БлэкДжек.
У этого класса должно быть три поля: масть, значение карты и положение карты (вверх лицом или рубашкой).
Сделать поля масть и значение карты типом перечисления (enum). Положение карты - тип bool. Также в этом классе должно быть два метода:
метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1. */

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

int main()
{
    cout << "\nTask No.1" << endl;
    cout << '\n';

    Parallelogram PLLL(3,6);
    PLLL.area();
    Circle Crcl(5);
    Crcl.area();
    Rectangle Rctgl(5,4);
    Rctgl.area();
    Square Scqr(5,5);
    Scqr.area();
    Rhombus Rmbs(3,6);
    Rmbs.area();

    cout << "\nTask No.2" << endl;
    cout << '\n';

    // Car C("BMW", "X5");
    // PassengerCar P("Toyota", "camry");
    // Bus B("Azur", "B2");
    Minivan M("Volkswagen", "transporter");

    cout << "\nTask No.3" << endl;
    cout << '\n';

    Fraction f1(2, 3);
    Fraction f2(4, 5);
    Fraction fplus;
    Fraction fminus;
    Fraction fmultiply;
    Fraction fdivide;
    Fraction funmin;
    cout << "f1 = "; f1.print(); cout << endl;
    cout << "f2 = "; f2.print(); cout << endl;
    fplus = f1.operator+(f2); // Явный вызов функции-оператора +
    cout << "Sum = "; fplus.print(); cout << endl;
    fminus = operator-(f1, f2);
    cout << "Difference = "; fminus.print(); cout << endl;
    fmultiply = operator*(f1, f2); // Явный вызов функции-оператора *
    cout << "Multiplication = "; fmultiply.print(); cout << endl;
    fdivide = operator/(f1, f2);
    cout << "Division = "; fdivide.print(); cout << endl;
    funmin = f1.operator-();
    cout << "Minus = "; funmin.print(); cout << endl;
    cout << "Comparison:" << endl;
    cout << "F1 >= F2 - " << ((f1 >= f2) ? "true" : "false") << endl;
    cout << "F1 <= F2 - " << ((f1 <= f2) ? "true" : "false") << endl;
    cout << "F1 == F2 - " << ((f1 == f2) ? "true" : "false") << endl;
    cout << "F1 != F2 - " << ((f1 != f2) ? "true" : "false") << endl;

    return 0;
}
