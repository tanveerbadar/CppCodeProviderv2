#ifndef BINARY_EXPRESSION_HEADER
#define BINARY_EXPRESSION_HEADER
#pragma once

#include <memory>
#include "common.h"
#include "expression_types.h"
#include "../../utils/copyable_ptr.h"

namespace cpp::codeprovider::expressions
{
	class binary_expression : public expression
	{
		utils::copyable_ptr<expression> e1, e2;
		expression_type e_type;
	public:
		binary_expression(expression_type, std::unique_ptr<expression>, std::unique_ptr<expression>);

		const expression& left() const;
		const expression& right() const;
		expression_type type() const;

		std::unique_ptr<expression> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif
