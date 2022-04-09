#include <vector>
#include <algorithm>
#include <iostream>

//#define HOME

#ifdef HOME
enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;  // возраст
	Gender gender;  // пол
	bool is_employed;  // имеет ли работу
};

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
	}
	std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(
			begin(range_copy), middle, end(range_copy),
			[](const Person& lhs, const Person& rhs) {
				return lhs.age < rhs.age;
			}
	);
	return middle->age;
}
#endif //HOME

template<typename F>
int ComputeMedianAgeOnPred(std::vector<Person> &persons, F lambda) {
	return ComputeMedianAge(begin(persons), std::partition(begin(persons), end(persons), lambda));
}

void PrintStats1 (std::vector<Person> persons) {
	auto males_end = std::partition(begin(persons), end(persons), [](const Person &p){return p.gender == Gender::MALE;});
	auto males_emp_end = std::partition(begin(persons), males_end, [](const Person &p){return p.is_employed;});
	auto females_emp_end = std::partition(males_end, end(persons), [](const Person &p){return p.is_employed;});

	std::cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << std::endl;
	std::cout << "Median age for females = " << ComputeMedianAge(males_end, end(persons)) << std::endl;
	std::cout << "Median age for males = " << ComputeMedianAge(begin(persons), males_end) << std::endl;
	std::cout << "Median age for employed females = " << ComputeMedianAge(males_end, females_emp_end) << std::endl;
	std::cout << "Median age for unemployed females = " << ComputeMedianAge(females_emp_end, end(persons)) << std::endl;
	std::cout << "Median age for employed males = " << ComputeMedianAge(begin(persons), males_emp_end) << std::endl;
	std::cout << "Median age for unemployed males = " << ComputeMedianAge(males_emp_end, males_end) << std::endl;
}

void PrintStats(std::vector<Person> persons) {
	
	const int med_age = ComputeMedianAgeOnPred(persons, [](const Person &p){return true;});
	std::cout << "Median age = " << med_age << std::endl;
	
	const int med_age_fem = ComputeMedianAgeOnPred(persons,
											[](const Person &p)
											{return p.gender == Gender::FEMALE;});
	std::cout << "Median age for females = " << med_age_fem << std::endl;
	
	const int med_age_male = ComputeMedianAgeOnPred(persons,
											[](const Person &p)
											{return p.gender == Gender::MALE;});
	std::cout << "Median age for males = " << med_age_male << std::endl;
	
	const int med_age_fem_emp = ComputeMedianAgeOnPred(persons,
													   [](const Person &p)
													   {return p.gender == Gender::FEMALE && p.is_employed;});
	std::cout << "Median age for employed females = " << med_age_fem_emp << std::endl;

	const int med_age_fem_unemp = ComputeMedianAgeOnPred(persons,
													   [](const Person &p)
													   {return p.gender == Gender::FEMALE && !p.is_employed;});
	std::cout << "Median age for unemployed females = " << med_age_fem_unemp << std::endl;

	const int med_age_male_emp = ComputeMedianAgeOnPred(persons,
														 [](const Person &p)
														 {return p.gender == Gender::MALE && p.is_employed;});
	std::cout << "Median age for employed males = " << med_age_male_emp << std::endl;

	const int med_age_male_unemp = ComputeMedianAgeOnPred(persons,
														[](const Person &p)
														{return p.gender == Gender::MALE && !p.is_employed;});
	std::cout << "Median age for unemployed males = " << med_age_male_unemp << std::endl;
}

int main() {
	std::vector<Person> persons = {
			{31, Gender::MALE, false},
			{40, Gender::FEMALE, true},
			{24, Gender::MALE, true},
			{20, Gender::FEMALE, true},
			{80, Gender::FEMALE, false},
			{78, Gender::MALE, false},
			{10, Gender::FEMALE, false},
			{55, Gender::MALE, true},
	};
	PrintStats1(persons);
	return 0;
}
