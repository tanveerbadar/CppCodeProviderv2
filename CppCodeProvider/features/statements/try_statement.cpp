#include "try_statement.h"
#include "..\expressions\common.h"
#include "..\declarations\variable_declaration.h"

namespace cpp::codeprovider::types
{
	class type
	{
	public:
		std::string name;

		virtual std::unique_ptr<type> clone() const
		{
			return std::make_unique<type>(*this);
		}
	};
}

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace declarations;
	using namespace types;

	variable_declaration placeholder(declarator_specifier(type()));

	catch_clause::catch_clause(const catch_clause& other)
		:catch_var(make_unique<variable_declaration>(*other.catch_var)), catch_body(other.catch_body)
	{
	}

	const variable_declaration& catch_clause::variable() const
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