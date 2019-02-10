#ifndef FOR_LOOP_HEADER
#define FOR_LOOP_HEADER

#pragma once

#include "common.h"
#include "block_statement.h"
#include "../forward_declarations.h"

namespace cpp::codeprovider::statements
{
	class for_loop : public statement
	{
		block_statement body;
		std::unique_ptr<expressions::expression> init, loop_exp, condition_exp;
	public:
		for_loop() = default;
		for_loop(const for_loop&);
		for_loop& operator=(const for_loop&);

		const expressions::expression& initializer() const;
		for_loop& initializer(std::unique_ptr<expressions::expression>);
		const expressions::expression& condition() const;
		for_loop& condition(std::unique_ptr<expressions::expression>);
		const expressions::expression& loop() const;
		for_loop& loop(std::unique_ptr<expressions::expression>);
		statement_list &statements();
		const statement_list &statements() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}
#endif // !FOR_LOOP_HEADER
