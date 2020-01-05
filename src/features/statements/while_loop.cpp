#include "while_loop.h"
#include "../expressions/common.h"
#include "../../formatters/formatter_settings.h"

using namespace std;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::formatting;

while_loop::while_loop(unique_ptr<expression> expr)
	: body(), condition_exp(move(expr))
{
}

unique_ptr<statement> while_loop::clone() const
{
	return make_unique<while_loop>(*this);
}

void while_loop::write(ostream &os) const
{
	auto indent = formatter_settings::settings.get_indent_string();
	if (comment.size() > 0)
		os << indent << "//" << comment << endl;

	os << indent;
	if (loop_style == while_loop_style::while_loop)
		os << "while( " << *condition_exp << " )" << endl;
	else
		os << "do" << endl;
	os << body;
	if (loop_style == while_loop_style::do_while_loop)
		os << indent << "while( " << *condition_exp << " );" << endl;
}

const expression &while_loop::condition() const
{
	return *condition_exp;
}

while_loop &while_loop::condition(unique_ptr<expression> c)
{
	condition_exp = move(c);
	return *this;
}

while_loop_style while_loop::style() const
{
	return loop_style;
}

while_loop &while_loop::style(while_loop_style wls)
{
	loop_style = wls;
	return *this;
}

statement_list &while_loop::statements()
{
	return body.statements();
}

const statement_list &while_loop::statements() const
{
	return body.statements();
}

ostream &cpp::codeprovider::statements::operator<<(ostream &os, while_loop_style wls)
{
	os << (wls == while_loop_style::do_while_loop ? "do-while" : "while");
	return os;
}