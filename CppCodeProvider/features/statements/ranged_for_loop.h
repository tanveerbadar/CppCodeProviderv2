#ifndef RANGED_FOR_LOOP_HEADER
#define RANGED_FOR_LOOP_HEADER

#pragma once

#include "block_statement.h"
#include "../forward_declarations.h"
#include "../../utils/copyable_ptr.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::statements
{
	class ranged_for_loop : public statement
	{
		block_statement body;
		utils::copyable_ptr<expressions::expression> init;
	public:
		ranged_for_loop() = default;

		ACCESSOR_DECLARATION_2(ranged_for_loop, initializer, const expressions::expression &, std::unique_ptr<expressions::expression>)
		statement_list &statements();
		const statement_list &statements() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}
#endif // !RANGED_FOR_LOOP_HEADER
