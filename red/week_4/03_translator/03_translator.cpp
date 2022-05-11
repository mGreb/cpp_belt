#include "test_runner.h"
#include <string>
#include <map>

class Translator {
public:
  void Add(std::string_view source, std::string_view target) {
    std::string_view sw_source = *words.insert(std::string(source)).first;
    std::string_view sw_target = *words.insert(std::string(target)).first;
    to[sw_source] = sw_target;
    from[sw_target] = sw_source;
  }
  [[nodiscard]]
  std::string_view TranslateForward(std::string_view source) const {
    auto it = to.find(source);
    if (it == to.end())
      return "";
    return it->second;
  }
  [[nodiscard]]
  std::string_view TranslateBackward(std::string_view target) const {
    auto it = from.find(target);
    if (it == from.end())
      return "";
    return it->second;
  }

private:
  std::map<std::string_view, std::string_view> to;
  std::map<std::string_view, std::string_view> from;
  std::set<std::string> words;
};

void TestSimple() {
  Translator translator;
  translator.Add(std::string("okno"), std::string("window"));
  translator.Add(std::string("stol"), std::string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
