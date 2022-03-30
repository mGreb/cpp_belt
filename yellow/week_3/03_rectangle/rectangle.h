#pragma once

class Rectangle {
public:
	Rectangle(int width, int height);

	[[nodiscard]] int GetArea() const;

	[[nodiscard]] int GetPerimeter() const;

	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;

private:
	int width_, height_;
};
