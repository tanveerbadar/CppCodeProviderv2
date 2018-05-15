#ifndef WHILE_LOOP_HEADER
#define WHILE_LOOP_HEADER

#pragma once

#include "common.h"
#include "block_statement.h"

namespace cpp::codeprovider::expressions
{
	class expression;
}

namespace cpp::codeprovider::statements
{
	enum class while_loop_style
	{
		while_loop,
		do_while_loop,
	};

	class while_loop : public statement
	{
		std::unique_ptr<block_statement> body;
		std::unique_ptr<expressions::expression> condition_exp;
		while_loop_style loop_style;
	public:
		while_loop();
		while_loop(const while_loop&);

		const expressions::expression& condition() const;
		while_loop& condition(std::unique_ptr<expressions::expression>);
		while_loop_style style() const;
		while_loop& style(while_loop_style);
		block_statement& loop_body() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}
#endif // !FOR_LOOP_HEADER
