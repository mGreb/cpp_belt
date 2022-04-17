#include "test_runner.h"
// user includes
// system includes
#include <sstream>
#include <string>


class Logger
{
public:
	explicit Logger(std::ostream& output_stream) : os(output_stream) {}
	
	void SetLogLine(bool value) { log_line = value; }
	void SetLogFile(bool value) { log_file = value; }
	
	bool GetLogLine() { return log_line; }
	bool GetLogFile() { return log_file; }
	
	void Log(const std::string& message)
	{
		os << message << "\n";
	}
	
	std::ostream& GetStream() { return os; }
	
private:
	std::ostream& os;
	bool log_line = false;
	bool log_file = false;
};

#define LOG(logger, message) {                    \
    const bool line = logger.GetLogLine();        \
    const bool file = logger.GetLogFile();        \
    std::ostream &s = logger.GetStream();         \
    if (file && !line)                            \
        s << __FILE__ << " ";                     \
    if (file && line)                             \
        s << __FILE__ << ":" << __LINE__ << " ";  \
    if (!file && line)                            \
        s << "Line " << __LINE__ << " ";          \
    logger.Log(message);                          \
}

void TestLog()
{
/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
 * и наш тест начинает падать. Это неудобно.
 *
 * Чтобы этого избежать, мы используем специальный макрос #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
 * переопределить номер строки, а также имя файла. Благодаря ему, номера
 * строк внутри функции TestLog будут фиксированы независимо от того, какой
 * код мы добавляем перед ней*/
#line 1 "logger.cpp"
	
	std::ostringstream logs;
	Logger l(logs);
	LOG(l, "hello");
	
	l.SetLogFile(true);
	LOG(l, "hello");
	
	l.SetLogLine(true);
	LOG(l, "hello");
	
	l.SetLogFile(false);
	LOG(l, "hello");
	
	std::string expected = "hello\n";
	expected += "logger.cpp hello\n";
	expected += "logger.cpp:10 hello\n";
	expected += "Line 13 hello\n";
	std::string actual = logs.str();
	ASSERT_EQUAL(actual, expected);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestLog);
}
