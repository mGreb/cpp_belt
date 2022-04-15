#include "node.h"

// user includes
#include "comparison.h"
#include "test_runner.h"


DateComparisonNode::DateComparisonNode(Comparison _comp, const Date &_date) : comp(_comp), date(_date) {
}


bool DateComparisonNode::Evaluate(const Date &ev_date, const std::string &ev_event) {
	return Compare(comp, ev_date, date);
}


EventComparisonNode::EventComparisonNode(Comparison _comp, const std::string &_event) : comp(_comp), event(std::move(_event)) {
}


bool EventComparisonNode::Evaluate(const Date &ev_date, const std::string &ev_event) {
	return Compare(comp, ev_event, event);
}


LogicalOperationNode::LogicalOperationNode(LogicalOperation _lop, std::shared_ptr<Node> _left, std::shared_ptr<Node> _right)
: lop(_lop), left(std::move(_left)), right(std::move(_right)) {

}


bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) {
	if (lop == LogicalOperation::And)
		return left->Evaluate(date, event) && right->Evaluate(date, event);;
	if (lop == LogicalOperation::Or)
		return left->Evaluate(date, event) || right->Evaluate(date, event);
	
	return true;
}


bool EmptyNode::Evaluate(const Date &date, const std::string &event) {
	return true;
}


void TestEventComparisonNode() {
	const Date january_1{1970, 1, 1};
	
	EventComparisonNode less_eq(Comparison::LessOrEqual, "b");
	Assert(less_eq.Evaluate(january_1, "a"), "EventComparisonNode: less_eq 1");
	Assert(!less_eq.Evaluate(january_1, "c"), "EventComparisonNode: less_eq 2");
	Assert(less_eq.Evaluate(january_1, "b"), "EventComparisonNode: less_eq 3");
	
	EventComparisonNode equal(Comparison::Equal, "b");
	Assert(equal.Evaluate(january_1, "b"), "EventComparisonNode: equal 1");
	Assert(!equal.Evaluate(january_1, "a"), "EventComparisonNode: equal 2");
	Assert(!equal.Evaluate(january_1, "c"), "EventComparisonNode: equal 3");
	
	EventComparisonNode greater(Comparison::Greater, "b");
	Assert(greater.Evaluate(january_1, "c"), "EventComparisonNode: greater 1");
	Assert(!greater.Evaluate(january_1, "b"), "EventComparisonNode: greater 2");
	Assert(!greater.Evaluate(january_1, "a"), "EventComparisonNode: greater 3");
}
