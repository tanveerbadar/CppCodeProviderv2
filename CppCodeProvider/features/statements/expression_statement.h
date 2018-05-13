#ifndef EXPRESSION_STATEMENT_HEADER
#define EXPRESSION_STATEMENT_HEADER

#pragma once
#include "common.h"
#include "..\expressions\common.h"

namespace cpp::codeprovider::statements
{
	class expression_statement : public statement
	{
		std::unique_ptr<primitives::expression> e1;
	public:
		expression_statement(std::unique_ptr<primitives::expression>);
		expression_statement(const expression_statement&);

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !EXPRESSION_STATEMENT_HEADER
