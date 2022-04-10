#include <iostream>
#include <string>

void SendSms(const std::string& number, const std::string& message) {
	std::cout << "Send '" << message << "' to number " << number << std::endl;
}

void SendEmail(const std::string& email, const std::string& message) {
	std::cout << "Send '" << message << "' to e-mail " << email << std::endl;
}

class INotifier {
public:
	virtual void Notify(const std::string &message) = 0;
protected:
private:
};

class SmsNotifier : public INotifier {
public:
	explicit SmsNotifier(const std::string &number_) : number(number_) {}
	void Notify(const std::string& message) override {
		SendSms(number, message);
	}
protected:
private:
	const std::string number;
};

class EmailNotifier : public INotifier {
public:
	explicit EmailNotifier(const std::string &address_) : address(address_) {}
	void Notify(const std::string& message) override {
		SendEmail(address, message);
	}
protected:
private:
	const std::string address;
};

void Notify(INotifier& notifier, const std::string& message) {
	notifier.Notify(message);
}

int main() {
	SmsNotifier sms{ "+7-495-777-77-77" };
	EmailNotifier email{ "na-derevnyu@dedushke.ru" };

	Notify(sms, "I have White belt in C++");
	Notify(email, "And want a Yellow one");
	return 0;
}
