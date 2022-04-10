#include <iostream>
#include <string>
#include <deque>

void add_brackets(std::deque<std::string> &d)
{
	d.push_front("(");
	d.emplace_back(")");
}

void no_extra_brackets()
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

	char prev_command = ' ';
	
	for (int i = 0; i < ops; ++i)
	{
		char command;
		std::cin >> command;
		int value = 0;
		std::cin >> value;
		if (command == '+')
		{
			expression.push_back(" + " + std::to_string(value));
			prev_command = '+';
		}
		if (command == '-')
		{
			expression.push_back(" - " + std::to_string(value));
			prev_command = '-';
		}
		if (command == '*')
		{
			if (prev_command == '-' || prev_command == '+')
			{
				add_brackets(expression);
			}
			expression.push_back(" * " + std::to_string(value));
			prev_command = '*';
		}
		if (command == '/')
		{
			if (prev_command == '-' || prev_command == '+')
			{
				add_brackets(expression);
			}
			expression.push_back(" / " + std::to_string(value));
			prev_command = '/';
		}
	}

	for (const auto& i : expression)
		std::cout << i;
}

int main()
{
	no_extra_brackets();
	
	return 0;
}