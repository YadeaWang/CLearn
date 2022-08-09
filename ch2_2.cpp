#include <string>
#include <iostream>

using namespace std;

class Animal
{
public:
    Animal(int age, double weight, string *name)
        : age_(age), weight_(weight), name_(name) // constructor with params
    {
        count++;
    }
    Animal(const Animal &animal)
        : age_(animal.age_), weight_(animal.weight_) // copy constructor
    {
        name_ = new string(*animal.name_); // deep copy
        count++;
    }
    Animal(Animal &&animal)
        : Animal(animal.age_, animal.weight_, move(animal.name_)) // move constructor
    {
    }
    ~Animal()
    {
        count--;
    }

    static int getInstance() {
        return count;
    }
    // just for test, no private variables
    int age_;
    double weight_;
    string *name_;
    static int count;
};

int Animal::count = 0;

class Cat : public Animal
{
public:
    Cat(int age, double weight, string *name) : Animal(age, weight, name) {}
};

class Dog : public Animal
{
public:
    Dog(int age, double weight, string *name) : Animal(age, weight, name) {}
};

int main()
{
    string* cutename = new string("cute animal");
    Animal animal(3, 11.11, cutename);
    Animal copyanimal(animal);
    Animal moveanimal(move(animal));

    *cutename = "cute cat";
    Animal *cat = new Cat(1, 12, cutename);

    *cutename = "cute dog";
    Animal *dog = new Dog(2, 11, cutename);

    cout << Animal::getInstance() << endl;

}