#include <vector>
#include <iostream>

class Operation {
public:
	Operation(char op_, double val_) {op = op_; val = val_;}
	void Invert() {
		if (op == '+') {op = '-'; return;}
		if (op == '-') {op = '+'; return;}
		if (op == '*') {op = '/'; return;}
		if (op == '/') {op = '*'; return;}
	}
	[[nodiscard]] double Apply(double x) const {
		if (op == '+') return x + val;
		if (op == '-') return x - val;
		if (op == '/') return x / val;
		if (op == '*') return x * val;
	}
private:
	char op;
	double val;
};

class Function {
public:
	void AddPart(char op, double val) {
		ops.emplace_back(Operation(op, val));
	}
	[[nodiscard]] double Apply(double x) const {
		for (const auto & op : ops)
			x = op.Apply(x);
		return x;
	}
	void Invert() {
		for (auto &op : ops)
			op.Invert();
		std::reverse(ops.begin(), ops.end());
	}
private:
	std::vector<Operation> ops = {};
};

struct Image {
	double quality;
	double freshness;
	double rating;
};

struct Params {
	double a;
	double b;
	double c;
};

Function MakeWeightFunction(const Params& params,
							const Image& image) {
	Function function;
	function.AddPart('*', params.a);
	function.AddPart('-', image.freshness * params.b);
	function.AddPart('+', image.rating * params.c);
	return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
	Function function = MakeWeightFunction(params, image);
	return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
							  const Image& image,
							  double weight) {
	Function function = MakeWeightFunction(params, image);
	function.Invert();
	return function.Apply(weight);
}

int main() {
	Image image = {10, 2, 6};
	Params params = {4, 2, 6};
	std::cout << ComputeImageWeight(params, image) << std::endl;
	std::cout << ComputeQualityByWeight(params, image, 52) << std::endl;
	return 0;
}

