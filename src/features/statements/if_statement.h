#ifndef IF_STATEMENT_HEADER
#define IF_STATEMENT_HEADER

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
class if_statement : public statement
{
	block_statement if_collection, else_collection;
	utils::copyable_ptr<expressions::expression> condition_exp;
	bool is_const_expr = false;

public:
	if_statement(std::unique_ptr<expressions::expression>);

	statement_list &if_block();
	const statement_list &if_block() const;
	statement_list &else_block();
	const statement_list &else_block() const;
	ACCESSOR_DECLARATION_2(if_statement, condition, const expressions::expression &, std::unique_ptr<expressions::expression>)
	ACCESSOR_DECLARATION(if_statement, is_constexpr, bool);

	std::unique_ptr<statement> clone() const override;
	void write(std::ostream &) const override;
};
} // namespace statements
} // namespace codeprovider
} // namespace cpp

#endif // !IF_STATEMENT_HEADER