#pragma once

// user includes
#include "node.h"
// system includes
#include <iostream>

std::shared_ptr<Node> ParseCondition(std::istream& is);

void TestParseCondition();
