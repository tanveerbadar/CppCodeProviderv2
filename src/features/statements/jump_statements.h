#ifndef JUMP_STATEMENT_HEADER
#define JUMP_STATEMENT_HEADER

#pragma once

#include "common.h"
#include "../forward_declarations.h"
#include "../../utils/copyable_ptr.h"

namespace cpp
{
namespace codeprovider
{
namespace statements
{
enum class jump_type
{
	goto_jump,
	break_jump,
	continue_jump,
	return_jump
};

std::ostream &operator<<(std::ostream &, jump_type);

class jump_statement : public statement
{
	jump_type j_type;
	utils::copyable_ptr<expressions::expression> e1;

public:
	jump_statement(jump_type);
	jump_statement(jump_type, std::unique_ptr<expressions::expression>);

	jump_type type() const;

	std::unique_ptr<statement> clone() const override;
	void write(std::ostream &) const override;
};
} // namespace statements
} // namespace codeprovider
} // namespace cpp

#endif // !JUMP_STATEMENT_HEADER