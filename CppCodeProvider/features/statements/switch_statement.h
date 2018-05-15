#ifndef SWITCH_STATEMENT_HEADER
#define SWITCH_STATEMENT_HEADER

#pragma once

#include "common.h"
#include "block_statement.h"

namespace cpp::codeprovider::expressions
{
	class expression;
}

namespace cpp::codeprovider::statements
{
	class case_statement
	{
		std::unique_ptr<expressions::expression> e;
		std::unique_ptr<block_statement> statements;
	public:
		case_statement(bool);
		case_statement(std::unique_ptr<expressions::expression>);
		case_statement(const case_statement&);

		expressions::expression& label() const;
		block_statement& body() const;
		bool has_label() const;
	};

	std::ostream& operator <<(std::ostream&, const case_statement&);

	class switch_statement : public statement
	{
		std::unique_ptr<expressions::expression> condition_exp;
		std::vector<case_statement> collection;
	public:
		switch_statement(std::unique_ptr<expressions::expression>);
		switch_statement(const switch_statement&);

		const expressions::expression& condition() const;
		switch_statement& condition(std::unique_ptr<expressions::expression>);
		std::vector<case_statement>& cases();

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !SWITCH_STATEMENT_HEADER