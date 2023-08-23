#include <string>
#include <iostream>

using namespace std;

class Animal
{
public:
    Animal() = default; // default constructor
    Animal(int age, double weight, string *name)
        : age_(age), weight_(weight), name_(name) // constructor with params
    {
    }
    Animal(const Animal &animal)
        : age_(animal.age_), weight_(animal.weight_) // copy constructor
    {
        name_ = new string(*animal.name_); // deep copy
    }
    Animal(Animal &&animal)
        : Animal(animal.age_, animal.weight_, move(animal.name_)) // move constructor
    {
        animal.name_ = nullptr;
    }
    ~Animal()
    {
        if (name_ != nullptr)
            delete name_;
    }

    virtual void print() const;

    // just for test, no private variables
    int age_;
    double weight_;
    string *name_;
};

void Animal::print() const
{
    cout << "I'm an animal:" << *name_ << endl;
}

class Cat : public Animal
{
public:
    Cat(int age, double weight, string *name) : Animal(age, weight, name) {}
    void print() const override
    {
        cout << "I'm a cat:" << *name_ << endl;
    }
};

class Dog : public Animal
{
public:
    Dog(int age, double weight, string *name) : Animal(age, weight, name) {}
    void print() const override
    {
        cout << "I'm a dog:" << *name_ << endl;
    }
};

int main()
{
    string* cutename = new string("cute animal");
    Animal animal(3, 11.11, cutename);
    animal.print();     // cute animal

    Animal copyanimal(animal);
    copyanimal.print(); // cute animal[deep copy]

    *cutename = "cute cat";
    Animal *cat = new Cat(1, 12, cutename);
    cat->print();       // cute cat
    animal.print();     // cute cat[changed]
    copyanimal.print(); // cute animal[unchanged]

    *cutename = "cute dog";
    Animal *dog = new Dog(2, 11, cutename);
    dog->print();       // cute dog
}