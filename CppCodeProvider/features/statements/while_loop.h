#ifndef WHILE_LOOP_HEADER
#define WHILE_LOOP_HEADER

#pragma once

#include "common.h"
#include "block_statement.h"
#include "..\forward_declarations.h"

namespace cpp::codeprovider::statements
{
	enum class while_loop_style
	{
		while_loop,
		do_while_loop,
	};

	std::ostream& operator<<(std::ostream& os, while_loop_style);

	class while_loop : public statement
	{
		block_statement body;
		std::unique_ptr<expressions::expression> condition_exp;
		while_loop_style loop_style;
	public:
		while_loop(std::unique_ptr<expressions::expression>);
		while_loop(const while_loop&);
		while_loop& operator=(const while_loop&);

		const expressions::expression& condition() const;
		while_loop& condition(std::unique_ptr<expressions::expression>);
		while_loop_style style() const;
		while_loop& style(while_loop_style);
		std::vector<std::unique_ptr<statement>>& statements();

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}
#endif // !WHILE_LOOP_HEADER
