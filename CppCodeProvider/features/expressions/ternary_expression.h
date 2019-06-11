#ifndef TERNARY_EXPRESSION_HEADER
#define TERNARY_EXPRESSION_HEADER

#pragma once

#include <memory>
#include "common.h"
#include "expression_types.h"
#include "../../utils/copyable_ptr.h"

namespace cpp
{
namespace codeprovider
{
namespace expressions
{
class ternary_expression : public expression
{
	utils::copyable_ptr<expression> e1, e2, e3;

public:
	ternary_expression(std::unique_ptr<expression>, std::unique_ptr<expression>, std::unique_ptr<expression>);

	const expression &left() const;
	const expression &right() const;
	const expression &condition() const;
	expression_type type() const;

	std::unique_ptr<expression> clone() const override;
	void write(std::ostream &) const override;
};
} // namespace expressions
} // namespace codeprovider
} // namespace cpp

#endif // !
