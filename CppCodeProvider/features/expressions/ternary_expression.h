#ifndef TERNARY_EXPRESSION_HEADER
#define TERNARY_EXPRESSION_HEADER

#pragma once

#include "common.h"
#include "expression_types.h"
#include <memory>

namespace cpp::codeprovider::expressions
{
	class ternary_expression : public expression
	{
		std::unique_ptr<expression> e1, e2, e3;
	public:
		ternary_expression(std::unique_ptr<expression>, std::unique_ptr<expression>, std::unique_ptr<expression>);
		ternary_expression(const ternary_expression&);
		ternary_expression& operator=(const ternary_expression&);

		const expression& left() const;
		const expression& right() const;
		const expression& condition() const;
		expression_type type() const;

		std::unique_ptr<expression> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !
