#include <iostream>
#include <string>
#include <algorithm>

class ReversibleString {
public:
    ReversibleString() : s("") {};
    ReversibleString(const std::string &s_) : s(s_) {};
    void Reverse() {
        std::reverse(s.begin(), s.end());
    };
    std::string ToString() const {
        return s;
    }
private:
    std::string s;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  std::cout << s.ToString() << std::endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  std::string tmp = s_ref.ToString();
  std::cout << tmp << std::endl;
  
  ReversibleString empty;
  std::cout << '"' << empty.ToString() << '"' << std::endl;
  
  return 0;
}
