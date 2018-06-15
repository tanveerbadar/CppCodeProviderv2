#include "try_statement.h"

namespace cpp::codeprovider::declarations
{
	using namespace std;

	ostream& operator<<(ostream& os, const variable_declaration& var)
	{
		os << var.name;
		return os;
	}
}

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace declarations;

	catch_clause::catch_clause(const catch_clause& other)
		:catch_var(other.catch_var ? make_unique<variable_declaration>(*other.catch_var) : make_unique<variable_declaration>()), catch_body(other.catch_body)
	{
	}

	const declarations::variable_declaration& catch_clause::variable() const
	{
		return *catch_var;
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
		if (c.variable().name.size() > 0)
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