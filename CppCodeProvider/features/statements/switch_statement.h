#ifndef SWITCH_STATEMENT_HEADER
#define SWITCH_STATEMENT_HEADER

#pragma once

#include "block_statement.h"
#include "../forward_declarations.h"
#include "../../utils/copyable_ptr.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::statements
{
	class case_statement
	{
		utils::copyable_ptr<expressions::expression> e;
		block_statement block;
	public:
		case_statement(bool);
		case_statement(std::unique_ptr<expressions::expression>);

		const expressions::expression& label() const;
		statement_list &statements();
		const statement_list &statements() const;
		bool has_label() const;

		friend std::ostream& operator <<(std::ostream&, const case_statement&);
	};

	typedef std::vector<case_statement> case_list;

	class switch_statement : public statement
	{
		utils::copyable_ptr<expressions::expression> condition_exp;
		std::vector<case_statement> collection;
	public:
		switch_statement(std::unique_ptr<expressions::expression>);

		ACCESSOR_DECLARATION_2(switch_statement, condition, const expressions::expression &, std::unique_ptr<expressions::expression>)
		case_list &cases();
		const case_list &cases() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !SWITCH_STATEMENT_HEADER