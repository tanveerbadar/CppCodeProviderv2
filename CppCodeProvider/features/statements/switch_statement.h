#ifndef SWITCH_STATEMENT_HEADER
#define SWITCH_STATEMENT_HEADER

#pragma once

#include "block_statement.h"
#include "common.h"
#include "../forward_declarations.h"

namespace cpp::codeprovider::statements
{
	class case_statement
	{
		std::unique_ptr<expressions::expression> e;
		block_statement block;
	public:
		case_statement(bool);
		case_statement(std::unique_ptr<expressions::expression>);
		case_statement(const case_statement&);
		case_statement& operator=(const case_statement&);

		expressions::expression& label() const;
		std::vector<std::unique_ptr<statement>>& statements();
		const std::vector<std::unique_ptr<statement>>& statements() const;
		bool has_label() const;

		friend std::ostream& operator <<(std::ostream&, const case_statement&);
	};

	class switch_statement : public statement
	{
		std::unique_ptr<expressions::expression> condition_exp;
		std::vector<case_statement> collection;
	public:
		switch_statement(std::unique_ptr<expressions::expression>);
		switch_statement(const switch_statement&);
		switch_statement& operator=(const switch_statement&);

		const expressions::expression& condition() const;
		switch_statement& condition(std::unique_ptr<expressions::expression>);
		std::vector<case_statement>& cases();
		const std::vector<case_statement>& cases() const;

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !SWITCH_STATEMENT_HEADER