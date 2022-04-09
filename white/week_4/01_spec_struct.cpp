#include <string>

struct Specialization {
  std::string v;
  explicit Specialization(std::string v_) {v = v_;}
};

struct Course {
  std::string v;
  explicit Course(std::string v_) {v = v_;}
};

struct Week {
  std::string v;
  explicit Week(std::string v_) {v = v_;}
};

struct LectureTitle {
  std::string specialization;
  std::string course;
  std::string week;
  LectureTitle(Specialization s, Course c, Week w) {
    specialization = s.v;
    course = c.v;
    week = w.v;
  }
};

int main() {
	LectureTitle title(
			Specialization("C++"),
			Course("White belt"),
			Week("4th")
	);
	return 0;
}
