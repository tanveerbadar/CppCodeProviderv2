#ifndef EXPRESSION_STATEMENT_HEADER
#define EXPRESSION_STATEMENT_HEADER

#pragma once
#include "common.h"
#include "..\forward_declarations.h"

namespace cpp::codeprovider::statements
{
	class expression_statement : public statement
	{
		std::unique_ptr<expressions::expression> e1;
	public:
		expression_statement(std::unique_ptr<expressions::expression>);
		expression_statement(const expression_statement&);

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !EXPRESSION_STATEMENT_HEADER
