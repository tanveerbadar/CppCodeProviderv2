#include "try_statement.h"
#include "..\expressions\common.h"
#include "..\declarations\variable_declaration.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace declarations;
	using namespace types;

	catch_clause::catch_clause(const catch_clause& other)
		:catch_var(other.catch_var ? make_unique<variable_declaration>(*other.catch_var) : make_unique<variable_declaration>(declarator_specifier(type()))), catch_body(other.catch_body)
	{
	}

	const declarations::variable_declaration& catch_clause::variable() const
	{
		return *catch_var;
	}

	block_statement& catch_clause::body()
	{
		return catch_body;
	}

	const block_statement& catch_clause::body() const
	{
		return catch_body;
	}

	std::ostream& operator<<(std::ostream& os, const catch_clause& c)
	{
		os << "catch(";
		if (c.variable().declarator().name.size() > 0)
			os << c.variable();
		else
			os << "...";
		os << ")" << endl;
		os << c.body();
		return os;
	}

	block_statement& try_statement::try_statements()
	{
		return try_block;
	}

	vector<catch_clause>& try_statement::catch_clauses()
	{
		return catch_blocks;
	}

	unique_ptr<statement> try_statement::clone() const
	{
		return make_unique<try_statement>(*this);
	}

	void try_statement::write(ostream& os) const
	{
		os << "try" << endl;
		os << try_block;

		for (auto& c : catch_blocks)
			os << c;
	}
}