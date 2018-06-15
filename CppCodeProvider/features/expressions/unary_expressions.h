#ifndef PRIMITIVE_EXPRESSION_HEADER
#define PRIMITIVE_EXPRESSION_HEADER

#pragma once
#include <memory>
#include <string>
#include "expression_types.h"
#include "common.h"

namespace cpp::codeprovider::expressions
{
	class unary_expression : public expression
	{
		std::unique_ptr<expression> e1;
		expression_type e_type;
	public:
		unary_expression(expression_type, std::unique_ptr<expression>);
		unary_expression(const unary_expression&);
		unary_expression& operator=(const unary_expression&);

		const expression& expr() const;
		expression_type type() const;

		std::unique_ptr<expression> clone() const override;
		void write(std::ostream&) const override;
	};

	class primitive_expression : public expression
	{
		std::string e1;
	public:
		primitive_expression(const std::string&);

		const std::string& expr() const;
		expression_type type() const;

		std::unique_ptr<expression> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !PRIMITIVE_EXPRESSION_HEADER
