#ifndef FOR_LOOP_HEADER
#define FOR_LOOP_HEADER

#pragma once

#include "common.h"
#include "block_statement.h"
#include "../forward_declarations.h"
#include "../../utils/copyable_ptr.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::statements
{
	class for_loop : public statement
	{
		block_statement body;
		utils::copyable_ptr<expressions::expression> init, loop_exp, condition_exp;
	public:
		ACCESSOR_DECLARATION_2(for_loop, initializer, const expressions::expression &, std::unique_ptr<expressions::expression>)
		ACCESSOR_DECLARATION_2(for_loop, condition, const expressions::expression &, std::unique_ptr<expressions::expression>)
		ACCESSOR_DECLARATION_2(for_loop, loop, const expressions::expression &, std::unique_ptr<expressions::expression>)
		statement_list &statements();
		const statement_list &statements() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}
#endif // !FOR_LOOP_HEADER
