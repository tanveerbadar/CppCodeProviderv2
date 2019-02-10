#ifndef IF_STATEMENT_HEADER
#define IF_STATEMENT_HEADER

#pragma once

#include "block_statement.h"
#include "../forward_declarations.h"
#include "../../utils/dirty_macros.h"

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

		statement_list &if_block();
		const statement_list &if_block() const;
		statement_list &else_block();
		const statement_list &else_block() const;
		ACCESSOR_DECLARATION_2(if_statement, condition, const expressions::expression &, std::unique_ptr<expressions::expression>)

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !IF_STATEMENT_HEADER