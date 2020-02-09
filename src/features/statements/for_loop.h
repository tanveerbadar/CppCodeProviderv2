#ifndef FOR_LOOP_HEADER
#define FOR_LOOP_HEADER

#pragma once

#include "common.h"
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
class for_loop : public statement
{
	block_statement body;
	utils::copyable_ptr<expressions::expression> loop_exp, condition_exp;
	utils::copyable_ptr<declarations::variable_declaration_list> init;

public:
	ACCESSOR_DECLARATION_2(for_loop, initializer, const declarations::variable_declaration_list &, std::unique_ptr<declarations::variable_declaration_list>)
	ACCESSOR_DECLARATION_2(for_loop, condition, const expressions::expression &, std::unique_ptr<expressions::expression>)
	ACCESSOR_DECLARATION_2(for_loop, loop, const expressions::expression &, std::unique_ptr<expressions::expression>)
	statement_list &statements();
	const statement_list &statements() const;

	std::unique_ptr<statement> clone() const override;
	void write(std::ostream &) const override;
};
} // namespace statements
} // namespace codeprovider
} // namespace cpp

#endif // !FOR_LOOP_HEADER
