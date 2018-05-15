#ifndef BINARY_EXPRESSION_HEADER
#define BINARY_EXPRESSION_HEADER
#pragma once

#include <memory>
#include "expression_types.h"
#include "common.h"

namespace cpp::codeprovider::expressions
{
	class binary_expression : public expression
	{
		std::unique_ptr<expression> e1, e2;
		expression_type e_type;
	public:
		binary_expression(expression_type, std::unique_ptr<expression>, std::unique_ptr<expression>);
		binary_expression(const binary_expression&);

		const expression& left() const;
		const expression& right() const;
		expression_type type() const;

		std::unique_ptr<expression> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif
