#include "rectangle.h"
#include "test_runner.h"

void Test() {
	Rectangle rectangle(10, 1);
	Assert(rectangle.GetArea() == 10, "area");
	Assert(rectangle.GetHeight() == 1, "height");
	Assert(rectangle.GetPerimeter() == 22, "perimeter");
	Assert(rectangle.GetWidth() == 10, "width");
}

int main () {
	TestRunner runner;
	runner.RunTest(Test, "all tests");
	return 0;
}
