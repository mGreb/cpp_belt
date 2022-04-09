#include <string>
#include <vector>

void MoveStrings(
	std::vector<std::string> &source,
	std::vector<std::string> &destination
) {
	for (const std::string &s: source)
		destination.push_back(s);
	source.clear();
}

int main()
{
	std::vector<std::string> source = {"a", "b", "c"};
	std::vector<std::string> destination = {"z"};
	MoveStrings(source, destination);
	
	return 0;
}
