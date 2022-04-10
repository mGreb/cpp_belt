#include <iostream>
#include <string>
#include <deque>

void with_extra_brackets()
{
	int num = 0;
	std::cin >> num;
	int ops = 0;
	std::cin >> ops;
	if (ops == 0)
	{
		std::cout << num;
		return;
	}

	std::deque<std::string> expression;
	expression.push_back(std::to_string(num));

	for (int i = 0; i < ops; ++i)
	{
		char command;
		std::cin >> command;
		int value = 0;
		std::cin >> value;
		if (command == '+')
		{
			expression.push_front("(");
			expression.push_back(") + " + std::to_string(value));
		}
		if (command == '-')
		{
			expression.push_front("(");
			expression.push_back(") - " + std::to_string(value));
		}
		if (command == '*')
		{
			expression.push_front("(");
			expression.push_back(") * " + std::to_string(value));
		}
		if (command == '/')
		{
			expression.push_front("(");
			expression.push_back(") / " + std::to_string(value));
		}
	}

	for (const auto &i : expression)
		std::cout << i;
}

int main()
{
	with_extra_brackets();
	
	return 0;
}