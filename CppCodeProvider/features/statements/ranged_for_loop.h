#ifndef RANGED_FOR_LOOP_HEADER
#define RANGED_FOR_LOOP_HEADER

#pragma once

#include "common.h"
#include "block_statement.h"
#include "../forward_declarations.h"

namespace cpp::codeprovider::statements
{
	class ranged_for_loop : public statement
	{
		block_statement body;
		std::unique_ptr<expressions::expression> init;
	public:
		ranged_for_loop() = default;
		ranged_for_loop(const ranged_for_loop&);
		ranged_for_loop& operator=(const ranged_for_loop&);

		const expressions::expression& initializer() const;
		ranged_for_loop& initializer(std::unique_ptr<expressions::expression>);
		std::vector<std::unique_ptr<statement>>& statements();
		const std::vector<std::unique_ptr<statement>>& statements() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}
#endif // !RANGED_FOR_LOOP_HEADER
