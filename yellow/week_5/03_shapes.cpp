#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>
#include <cmath>

const double PI = 3.14;

class Figure
{
public:
	Figure(std::string name_) : name(std::move(name_)) {};
	virtual std::string Name() = 0;
	virtual double Perimeter() = 0;
	virtual double Area() = 0;
protected:
	std::string name;
	double P;
	double S;
};

class Triangle : public Figure
{
public:
	Triangle(int a_, int b_, int c_) : Figure("TRIANGLE"), a(a_), b(b_), c(c_)
	{
		P = a + b + c;
		const double p2 = 0.5 * (a + b + c);
		S = std::sqrt(p2 * (p2 - a) * (p2 - b) * (p2 - c));
	}
	std::string Name() override { return name; }
	double Perimeter() override { return P;}
	double Area() override { return S; }
private:
	const double a, b, c;
};

class Rect : public Figure
{
public:
	Rect(int a_, int b_) : Figure("RECT"), a(a_), b(b_)
	{
		P = 2.0 * (a + b);
		S = a * b;
	}
	std::string Name() override {return name;}
	double Perimeter() override {return P;}
	double Area() override {return S;}
private:
	const int a, b;
};

class Circle : public Figure
{
public:
	Circle(int r_) : Figure("CIRCLE"), r(r_)
	{
		P = 2.0 * PI * r;
		S = PI * r * r;
	}
	std::string Name() override {return name;}
	double Perimeter() override {return P;}
	double Area() override {return S;}
private:
	const int r;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream &is)
{
	std::string fig;
	is >> fig;
	if (fig == "RECT")
	{
		int a, b;
		is >> a >> b;
		return std::make_shared<Rect>(a, b);
	}
	if (fig == "TRIANGLE")
	{
		int a, b, c;
		is >> a >> b >> c;
		return std::make_shared<Triangle>(a, b, c);
	}
	if (fig == "CIRCLE")
	{
		int r;
		is >> r;
		return std::make_shared<Circle>(r);
	}
}

int main() {
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; getline(std::cin, line); ) {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> std::ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                std::cout << std::fixed << std::setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << std::endl;
            }
        }
    }
    return 0;
}
