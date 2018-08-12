#include "try_statement.h"
#include "..\expressions\common.h"
#include "..\declarations\variable_declaration.h"
#include "..\types\primitive_type.h"

using namespace std;

namespace cpp::codeprovider::statements
{
	using namespace declarations;
	using namespace types;

	namespace
	{
		auto placeholder = variable_declaration(declarator_specifier(make_unique<primitive_type>("")));
	}

	catch_clause::catch_clause(unique_ptr<variable_declaration> var)
		:catch_var(move(var))
	{
	}

	catch_clause::catch_clause(const catch_clause& other)
		: catch_var(make_unique<variable_declaration>(other.catch_var ? *other.catch_var : placeholder)), catch_body(other.catch_body)
	{
	}

	catch_clause& catch_clause::operator=(const catch_clause& other)
	{
		if (this != &other)
		{
			catch_body = other.catch_body;
			catch_var = make_unique<variable_declaration>(other.catch_var ? *other.catch_var : placeholder);
		}
		return *this;
	}

	const variable_declaration& catch_clause::variable() const
	{
		return catch_var ? *catch_var : placeholder;
	}

	vector<unique_ptr<statement>>& catch_clause::statements()
	{
		return catch_body.statements();
	}

	const vector<unique_ptr<statement>>& catch_clause::statements() const
	{
		return catch_body.statements();
	}

	std::ostream& operator<<(std::ostream& os, const catch_clause& c)
	{
		os << "catch(";
		if (c.variable().declarator().name.size() > 0)
			os << c.variable();
		else
			os << "...";
		os << ")" << endl;
		os << c.catch_body;
		return os;
	}

	vector<unique_ptr<statement>>& try_statement::statements()
	{
		return try_block.statements();
	}

	const vector<unique_ptr<statement>>& try_statement::statements() const
	{
		return try_block.statements();
	}

	vector<catch_clause>& try_statement::catch_clauses()
	{
		return catch_blocks;
	}

	const vector<catch_clause>& try_statement::catch_clauses() const
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