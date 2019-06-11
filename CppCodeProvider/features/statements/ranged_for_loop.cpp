#include "ranged_for_loop.h"
#include "../expressions/unary_expressions.h"
#include "../../formatters/formatter_settings.h"

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::statements;

namespace
{
primitive_expression placeholder("");
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
	os << indent << "for( ";
	if (init)
		os << *init;
	os << " )" << endl;
	os << body;
}

const expression &ranged_for_loop::initializer() const
{
	return init ? *init : placeholder;
}

ranged_for_loop &ranged_for_loop::initializer(unique_ptr<expression> i)
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