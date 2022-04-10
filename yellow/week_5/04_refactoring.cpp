#include <iostream>
#include <string>
#include <vector>

class Person {
public:
	Person(const std::string& name, const std::string& occupation) : _name(name), _occupation(occupation) {}
	
	[[nodiscard]] std::string GetName() const {
		return _name;
	}
	[[nodiscard]] std::string GetOccupation() const {
		return _occupation;
	}
	virtual void Walk(const std::string& destination) const = 0;

private:
	const std::string _name;
	const std::string _occupation;
};


class Student : public Person {
public:
	Student(const std::string& name, const std::string& favouriteSong) : Person(name, "Student"), _favouriteSong(favouriteSong) {}
	
	void Learn() const {
		std::cout << "Student: " << GetName() << " learns" << std::endl;
	}
	
	void Walk(const std::string& destination) const override {
		std::cout << "Student: " << GetName() << " walks to: " << destination << std::endl;
		SingSong();
	}
	
	void SingSong() const {
		std::cout << "Student: " << GetName() << " sings a song: " << _favouriteSong << std::endl;
	}
	
private:
	const std::string _favouriteSong;
};


class Teacher : public Person {
public:
	Teacher(const std::string& name, const std::string& subject) : Person(name, "Teacher"), _subject(subject) {}
	
	void Teach() const {
		std::cout << "Teacher: " << GetName() << " teaches: " << _subject << std::endl;
	}
	
	void Walk(const std::string& destination) const override {
		std::cout << "Teacher: " << GetName() << " walks to: " << destination << std::endl;
	}
	
private:
	const std::string _subject;
};


class Policeman : public Person {
public:
	explicit Policeman(const std::string& name) : Person(name, "Policeman") {}
	
	void Check(const Person& person) const {
		std::cout << "Policeman: " << GetName() << " checks " << person.GetOccupation() << ". "
				  << person.GetOccupation() << "'s name is: " << person.GetName() << std::endl;
	}
	
	void Walk(const std::string& destination) const override {
		std::cout << "Policeman: " << GetName() << " walks to: " << destination << std::endl;
	}
};


void VisitPlaces(const Person& person, const std::vector<std::string> &places) {
	for (const auto& p : places) {
		person.Walk(p);
	}
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");
	
	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	
	return 0;
}