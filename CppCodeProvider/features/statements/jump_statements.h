#ifndef JUMP_STATEMENT_HEADER
#define JUMP_STATEMENT_HEADER

#pragma once

#include "common.h"
#include "..\..\forward_declarations.h"

namespace cpp::codeprovider::statements
{
	enum class jump_type
	{
		goto_jump,
		break_jump,
		continue_jump,
		return_jump
	};

	std::ostream& operator<<(std::ostream&, jump_type);

	class jump_statement : public statement
	{
		jump_type j_type;
		std::unique_ptr<expressions::expression>  e1;
	public:
		jump_statement(jump_type);
		jump_statement(const jump_statement&);

		jump_type type() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !JUMP_STATEMENT_HEADER