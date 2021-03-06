#ifndef WHILE_LOOP_HEADER
#define WHILE_LOOP_HEADER

#pragma once

#include "block_statement.h"
#include "../forward_declarations.h"
#include "../../utils/copyable_ptr.h"
#include "../../utils/dirty_macros.h"

namespace cpp
{
namespace codeprovider
{
namespace statements
{
enum class while_loop_style
{
	while_loop,
	do_while_loop,
};

std::ostream &operator<<(std::ostream &os, while_loop_style);

class while_loop : public statement
{
	block_statement body;
	utils::copyable_ptr<expressions::expression> condition_exp;
	while_loop_style loop_style = while_loop_style::while_loop;

public:
	while_loop(std::unique_ptr<expressions::expression>);

	ACCESSOR_DECLARATION_2(while_loop, condition, const expressions::expression &, std::unique_ptr<expressions::expression>)
	while_loop_style style() const;
	while_loop &style(while_loop_style);
	statement_list &statements();
	const statement_list &statements() const;

	std::unique_ptr<statement> clone() const override;
	void write(std::ostream &) const override;
};
} // namespace statements
} // namespace codeprovider
} // namespace cpp

#endif // !WHILE_LOOP_HEADER