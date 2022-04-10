#include <iostream>

class Animal {
public:
    explicit Animal(const std::string &Name_) : Name(Name_) {}

    const std::string Name;
};

class Dog : public Animal {
public:
    explicit Dog(const std::string &Name_) : Animal(Name_) {}

    void Bark() {
        std::cout << Name << " barks: woof!" << std::endl;
    }
};

int main()
{
    Dog d("Barsik");
	d.Bark();
	
	return 0;
}
