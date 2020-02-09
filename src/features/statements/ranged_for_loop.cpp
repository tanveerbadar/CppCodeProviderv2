#include "ranged_for_loop.h"
#include "../../formatters/formatter_settings.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/primitive_expression.h"
#include "../types/primitive_type.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;

ranged_for_loop::ranged_for_loop(unique_ptr<variable_declaration> d)
	: init(move(d))
{
}

unique_ptr<statement> ranged_for_loop::clone() const
{
	return make_unique<ranged_for_loop>(*this);
}

void ranged_for_loop::write(ostream &os) const
{
	auto indent = formatter_settings::settings.get_indent_string();

	if (comment.size() > 0)
		os << indent << "//" << comment << endl;
	os << indent << "for(";
	os << init->specifier() << init->var_declarator().name << " : " << *init->var_declarator().initializer_exp;
	os << ")" << endl;
	os << body;
}

const variable_declaration &ranged_for_loop::initializer() const
{
	return *init;
}

ranged_for_loop &ranged_for_loop::initializer(unique_ptr<variable_declaration> i)
{
	init = move(i);
	return *this;
}

statement_list &ranged_for_loop::statements()
{
	return body.statements();
}

const statement_list &ranged_for_loop::statements() const
{
	return body.statements();
}