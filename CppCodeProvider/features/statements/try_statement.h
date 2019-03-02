#ifndef TRY_STATEMENT_BLOCK
#define TRY_STATEMENT_BLOCK

#pragma once

#include <string>
#include "block_statement.h"
#include "../forward_declarations.h"
#include "../../utils/copyable_ptr.h"

namespace cpp::codeprovider::statements
{
	class catch_clause
	{
		utils::copyable_ptr<declarations::variable_declaration> catch_var;
		block_statement catch_body;
	public:
		catch_clause() = default;
		catch_clause(std::unique_ptr<declarations::variable_declaration>);

		const declarations::variable_declaration& variable() const;
		statement_list& statements();
		const statement_list &statements() const;

		friend std::ostream& operator<<(std::ostream&, const catch_clause&);
	};

	typedef std::vector<catch_clause> catch_list;

	class try_statement : public statement
	{
		block_statement try_block;
		std::vector<catch_clause> catch_blocks;
	public:
	  statement_list &statements();
	  const statement_list &statements() const;
	  catch_list &catch_clauses();
	  const catch_list &catch_clauses() const;

	  std::unique_ptr<statement> clone() const override;
	  void write(std::ostream &) const override;
	};
}

#endif // !TRY_STATEMENT_BLOCK