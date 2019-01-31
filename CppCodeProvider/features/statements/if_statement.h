#ifndef IF_STATEMENT_HEADER
#define IF_STATEMENT_HEADER

#pragma once

#include "block_statement.h"
#include "../forward_declarations.h"

namespace cpp::codeprovider::statements
{
	class if_statement : public statement
	{
		block_statement if_collection, else_collection;
		std::unique_ptr<expressions::expression> condition_exp;
	public:
		if_statement(std::unique_ptr<expressions::expression>);
		if_statement(const if_statement&);
		if_statement& operator=(const if_statement&);

		std::vector<std::unique_ptr<statement>>& if_block();
		const std::vector<std::unique_ptr<statement>>& if_block() const;
		std::vector<std::unique_ptr<statement>>& else_block();
		const std::vector<std::unique_ptr<statement>>& else_block() const;
		const expressions::expression& condition() const;
		if_statement& condition(std::unique_ptr<expressions::expression>);

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !IF_STATEMENT_HEADER