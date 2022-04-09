#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
	/* Для тестирования повставляйте сюда код, реализующий различное поведение этой функии:
	   * нормальный возврат строкового значения
	   * выброс исключения system_error
	   * выброс другого исключения с сообщением.
	*/
//	throw std::exception();
//	throw std::string("pewpewpew");
//	throw std::domain_error("");
//	throw std::system_error();
	return "01:01:01";
}

class TimeServer {
public:
	string GetCurrentTime() {
		/* Реализуйте этот метод:
			* если AskTimeServer() вернула значение, запишите его в last_fetched_time и верните
			* если AskTimeServer() бросила исключение system_error, верните текущее значение
			поля last_fetched_time
			* если AskTimeServer() бросила другое исключение, пробросьте его дальше.
		*/
		try {
			last_fetched_time = AskTimeServer();
		} catch (const std::system_error &s) {
		}
		return last_fetched_time;
	}

private:
	string last_fetched_time = "00:00:00";
};

int main() {
	// Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
	TimeServer ts;
	try {
		cout << ts.GetCurrentTime() << endl;
	} catch (exception& e) {
		cout << "Exception got: " << e.what() << endl;
	}
	return 0;
}
