#include <iostream>
#include <cstring>

using namespace std;

/* Задание №1. Создать класс Person (человек) с полями: имя, возраст, пол и вес. Определить методы переназначения имени, изменения возраста и веса.
Создать производный класс Student (студент), имеющий поле года обучения. Определить методы переназначения и увеличения этого значения.
Создать счетчик количества созданных студентов. В функции main() создать несколько (не больше трёх) студентов. Вывести информацию о них. */

class Person {

protected:
  string name = "Irina";
  int age = 23;
  string sex = "female";
  int weight = 65;
public:
  Person () = default;
  void set(string m_name, int m_age, string m_sex, int m_weight) { name = m_name; age = m_age; sex = m_sex; weight = m_weight; }
  /*void changeName()
  {
    string _name;
    cout << "Input name: " << endl;
    cin >> _name;
    memset(name,' ', strlen(name)+1);
    strcpy(name,_name);
  }*/
  void changeAge()
  {
    cout << "Input age: " << endl;
    cin >> age;
  }
  void changeWeight()
  {
    cout << "Input weight: " << endl;
    cin >> weight;
  }
  void print()
  {
    cout << '\n';
    cout << "Name is: " << name << endl;
    cout << "Age is: " << age << endl;
    cout << "Sex is: " << sex << endl;
    cout << "Weight is: " << weight << endl;
  }
};

class Student : public Person
{
private:
  int year;
  static int Count;
public:
  Student(){Count++;}
  static void printCount(){cout << '\n' << "Quantity of students: " << Count << endl;}

  void changeYear()
  {
    cout << "Input year: \n";
    cin >> year;
  }
  void inceaseYear()
  {
    year = ++year;
    cout << "Increased year is: " << year << endl;
  }
  void printYear() { cout << "Year is: " << year << endl; }
};

/* Задание №2. Создать классы Apple (яблоко) и Banana (банан), которые наследуют класс Fruit (фрукт).
У Fruit есть две переменные-члена: name (имя) и color (цвет). Добавить новый класс GrannySmith, который наследует класс Apple.*/

class Fruit
{
private:
    string name;
    string color;
public:
    Fruit(string _name, string _color) : name(_name), color(_color) {}
    string getName() {return name;}
    string getColor() {return color;}
};

class Apple: public Fruit
{
protected:
	Apple(string name, string color) : Fruit(name, color) {}

public:
	Apple(string color="red") : Fruit("apple", color) {}
};

class Banana : public Fruit
{
public:
	Banana() : Fruit("banana", "yellow") {}
};

class GrannySmith : public Apple
{
public:
	GrannySmith() : Apple("Granny Smith apple", "green") {}
};

int Student::Count=0;
int main()
{
    // Задание №1.

    Student S1;
    S1.set("Svyatogor", 34, "male", 76);
    S1.print();
    S1.changeYear();
    S1.inceaseYear();
    Student S2;
    S2.set("Valera", 23, "male", 98);
    S2.print();
    Student S3;
    S3.set("Galya", 26, "female", 123);
    S3.print();
    Student::printCount();
    return 0;

    // Задание №2.

    Apple a("red");
	Banana b;
	GrannySmith c;

	cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
}

