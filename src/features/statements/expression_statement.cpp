#include "expression_statement.h"
#include "../expressions/common.h"
#include "../../formatters/formatter_settings.h"

using namespace std;
using e = cpp::codeprovider::expressions::expression;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::statements;

expression_statement::expression_statement(unique_ptr<e> e, const string &l)
	: e1(move(e)), label(l)
{
}

const e &expression_statement::expression() const
{
	return *e1;
}

void expression_statement::write(ostream &os) const
{
	auto indent = formatter_settings::settings.get_indent_string();
	if (comment.size() > 0)
		os << indent << "//" << comment << endl;
	if (label.size() > 0)
		os << label << ":" << endl;
	os << indent << *e1 << ";" << endl;
}

unique_ptr<statement> expression_statement::clone() const
{
	return make_unique<expression_statement>(*this);
}