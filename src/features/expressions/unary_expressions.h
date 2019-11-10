#ifndef UNARY_EXPRESSION_HEADER
#define UNARY_EXPRESSION_HEADER

#pragma once
#include <memory>
#include <string>
#include "common.h"
#include "expression_types.h"
#include "../../utils/copyable_ptr.h"

namespace cpp
{
namespace codeprovider
{
namespace expressions
{
class unary_expression : public expression
{
	utils::copyable_ptr<expression> e1;
	expression_type e_type;

public:
	unary_expression(expression_type, std::unique_ptr<expression>);

	const expression &expr() const;
	expression_type type() const;

	std::unique_ptr<expression> clone() const override;
	void write(std::ostream &) const override;
};
} // namespace expressions
} // namespace codeprovider
} // namespace cpp

#endif // !UNARY_EXPRESSION_HEADER
