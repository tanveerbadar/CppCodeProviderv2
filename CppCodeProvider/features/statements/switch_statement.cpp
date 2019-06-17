#include "switch_statement.h"
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

case_statement::case_statement(bool)
	: block()
{
}

case_statement::case_statement(unique_ptr<expression> l)
	: e(move(l)), block()
{
}

const statement_list &case_statement::statements() const
{
	return block.statements();
}

statement_list &case_statement::statements()
{
	return block.statements();
}

const expression &case_statement::label() const
{
	return *e;
}

bool case_statement::has_label() const
{
	auto ptr = dynamic_cast<const primitive_expression *>(e.operator->());
	return ptr && ptr->expr().size() > 0;
}

ostream &cpp::codeprovider::statements::operator<<(ostream &os, const case_statement &c)
{
	os << formatter_settings::settings.get_indent_string();
	if (c.has_label())
		os << "case " << c.label() << ":" << endl;
	else
		os << "default"
		   << ":" << endl;

	os << c.block;

	return os;
}

switch_statement::switch_statement(unique_ptr<expression> c)
	: condition_exp(move(c))
{
}

unique_ptr<statement> switch_statement::clone() const
{
	return make_unique<switch_statement>(*this);
}

void switch_statement::write(ostream &os) const
{
	auto indent = formatter_settings::settings.get_indent_string();

	if (comment.size() > 0)
		os << indent << "//" << comment << endl;

	os << indent << "switch(" << *condition_exp << ")" << endl;
	os << indent << "{" << endl;
	for (auto &c : collection)
	{
		os << c;
	}
	os << indent << "}" << endl;
}

const expression &switch_statement::condition() const
{
	return *condition_exp;
}

switch_statement &switch_statement::condition(unique_ptr<cpp::codeprovider::expressions::expression> c)
{
	condition_exp = move(c);
	return *this;
}

case_list &switch_statement::cases()
{
	return collection;
}

const case_list &switch_statement::cases() const
{
	return collection;
}
