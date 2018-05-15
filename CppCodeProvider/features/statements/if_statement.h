#ifndef IF_STATEMENT_HEADER
#define IF_STATEMENT_HEADER

#pragma once

#include "common.h"
#include "block_statement.h"

namespace cpp::codeprovider::expressions
{
	class expression;
}

namespace cpp::codeprovider::statements
{
	class if_statement : public statement
	{
		block_statement if_collection, else_collection;
		std::unique_ptr<expressions::expression> condition_exp;
	public:
		if_statement(std::unique_ptr<expressions::expression>);

		block_statement & if_block();
		block_statement& else_block();
		const expressions::expression& condition() const;
		if_statement& condition(std::unique_ptr<expressions::expression>);

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !IF_STATEMENT_HEADER