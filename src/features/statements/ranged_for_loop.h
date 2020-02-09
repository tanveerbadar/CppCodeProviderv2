#ifndef RANGED_FOR_LOOP_HEADER
#define RANGED_FOR_LOOP_HEADER

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
class ranged_for_loop : public statement
{
	block_statement body;
	utils::copyable_ptr<declarations::variable_declaration> init;

public:
	ranged_for_loop(std::unique_ptr<declarations::variable_declaration>);

	ACCESSOR_DECLARATION_2(ranged_for_loop, initializer, const declarations::variable_declaration &, std::unique_ptr<declarations::variable_declaration>)
	statement_list &statements();
	const statement_list &statements() const;

	std::unique_ptr<statement> clone() const override;
	void write(std::ostream &) const override;
};
} // namespace statements
} // namespace codeprovider
} // namespace cpp

#endif // !RANGED_FOR_LOOP_HEADER
