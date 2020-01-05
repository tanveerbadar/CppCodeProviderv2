#include "for_loop.h"
#include "../expressions/primitive_expression.h"
#include "../../formatters/formatter_settings.h"

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::statements;

namespace
{
primitive_expression placeholder("");
}

unique_ptr<statement> for_loop::clone() const
{
	return make_unique<for_loop>(*this);
}

void for_loop::write(ostream &os) const
{
	auto indent = formatter_settings::settings.get_indent_string();

	if (comment.size() > 0)
		os << indent << "//" << comment << endl;
	os << indent << "for( ";
	if (init)
		os << *init;
	os << ";";
	if (condition_exp)
		os << ' ' << *condition_exp;
	os << ";";
	if (loop_exp)
		os << ' ' << *loop_exp;
	os << " )" << endl;
	os << body;
}

const expression &for_loop::initializer() const
{
	return init ? *init : placeholder;
}

for_loop &for_loop::initializer(unique_ptr<expression> i)
{
	init = move(i);
	return *this;
}

const expression &for_loop::condition() const
{
	return condition_exp ? *condition_exp : placeholder;
}

for_loop &for_loop::condition(unique_ptr<expression> c)
{
	condition_exp = move(c);
	return *this;
}

const expression &for_loop::loop() const
{
	return loop_exp ? *loop_exp : placeholder;
}

for_loop &for_loop::loop(unique_ptr<expression> l)
{
	loop_exp = move(l);
	return *this;
}

statement_list &for_loop::statements()
{
	return body.statements();
}

const statement_list &for_loop::statements() const
{
	return body.statements();
}