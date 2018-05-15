#ifndef TRY_STATEMENT_BLOCK
#define TRY_STATEMENT_BLOCK

#pragma once

#include "common.h"
#include "block_statement.h"
#include <string>

namespace cpp::codeprovider::declarations
{
	class variable_declaration
	{
	public:
		std::string name;
	};

	std::ostream& operator<<(std::ostream&, const variable_declaration&);
}

namespace cpp::codeprovider::statements
{
	class catch_clause
	{
		std::unique_ptr<declarations::variable_declaration> catch_var;
		block_statement catch_body;
	public:
		catch_clause() = default;
		catch_clause(const catch_clause&);

		const declarations::variable_declaration& variable() const;
		block_statement& body();
		const block_statement& body() const;
	};

	std::ostream& operator<<(std::ostream&, const catch_clause&);

	class try_statement : public statement
	{
		block_statement try_block;
		std::vector<catch_clause> catch_blocks;
	public:
		block_statement& try_statements();
		std::vector<catch_clause>& catch_clauses();

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}
#endif // !TRY_STATEMENT_BLOCK