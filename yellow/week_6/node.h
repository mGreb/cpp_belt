#pragma once

// user includes
#include "date.h"
#include "logical_operation.h"
#include "comparison.h"
// system includes
#include <memory>


class Node {
public:
	virtual bool Evaluate(const Date &date, const std::string &event) = 0;
private:
};


class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison _comp, const Date &_date);
	bool Evaluate(const Date &ev_date, const std::string &ev_event) override;
private:
	const Comparison comp;
	const Date date;
};


class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison _comp, const std::string &_event);
	bool Evaluate(const Date &ev_date, const std::string &ev_event) override;
private:
	const Comparison comp;
	const std::string event;
};


class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation _lop, std::shared_ptr<Node> _left, std::shared_ptr<Node> _right);
	bool Evaluate(const Date &date, const std::string &event) override;
private:
	const LogicalOperation lop;
	const std::shared_ptr<Node> left, right;
};


class EmptyNode : public Node {
public:
	EmptyNode() = default;
	bool Evaluate(const Date &date, const std::string &event) override;
private:
};


void TestEventComparisonNode();