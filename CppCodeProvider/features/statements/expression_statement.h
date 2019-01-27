#ifndef EXPRESSION_STATEMENT_HEADER
#define EXPRESSION_STATEMENT_HEADER

#pragma once
#include "common.h"
#include "../forward_declarations.h"

namespace cpp::codeprovider::statements
{
	class expression_statement : public statement
	{
		std::unique_ptr<expressions::expression> e1;
		std::string label;
	public:
		expression_statement(std::unique_ptr<expressions::expression>, const std::string& = "");
		expression_statement(const expression_statement&);
		expression_statement& operator=(const expression_statement&);

		const expressions::expression& expression() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !EXPRESSION_STATEMENT_HEADER
