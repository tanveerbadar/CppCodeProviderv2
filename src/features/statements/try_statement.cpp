#include "try_statement.h"
#include "../expressions/common.h"
#include "../declarations/variable_declaration.h"
#include "../types/primitive_type.h"
#include "../../formatters/formatter_settings.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::formatting;

namespace
{
auto placeholder = variable_declaration(declarator_specifier(make_unique<primitive_type>("")));
}

catch_clause::catch_clause(unique_ptr<variable_declaration> var)
	: catch_var(move(var))
{
}

const variable_declaration &catch_clause::variable() const
{
	return catch_var ? *catch_var : placeholder;
}

statement_list &catch_clause::statements()
{
	return catch_body.statements();
}

const statement_list &catch_clause::statements() const
{
	return catch_body.statements();
}

std::ostream &cpp::codeprovider::statements::operator<<(std::ostream &os, const catch_clause &c)
{
	auto indent = formatter_settings::settings.get_indent_string();
	os << indent << "catch(";
	if (c.variable().var_declarator().name.size() > 0)
		c.variable().write_declaration(os);
	else
		os << "...";
	os << ")" << endl;
	os << c.catch_body;
	return os;
}

statement_list &try_statement::statements()
{
	return try_block.statements();
}

const statement_list &try_statement::statements() const
{
	return try_block.statements();
}

catch_list &try_statement::catch_clauses()
{
	return catch_blocks;
}

const catch_list &try_statement::catch_clauses() const
{
	return catch_blocks;
}

unique_ptr<statement> try_statement::clone() const
{
	return make_unique<try_statement>(*this);
}

void try_statement::write(ostream &os) const
{
	os << "try" << endl;
	os << try_block;

	for (auto &c : catch_blocks)
		os << c;
}