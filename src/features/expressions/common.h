#ifndef COMMON_EXPRESSION_HEADER
#define COMMON_EXPRESSION_HEADER
#pragma once

#include <iostream>
#include <memory>

namespace cpp
{
namespace codeprovider
{
namespace expressions
{
class expression
{
public:
	virtual void write(std::ostream &) const = 0;
	virtual std::unique_ptr<expression> clone() const = 0;
	virtual ~expression() = 0;
};

std::ostream &operator<<(std::ostream &os, const expression &expr);
} // namespace expressions
} // namespace codeprovider
} // namespace cpp

#endif // !COMMON_EXPRESSION_HEADER
