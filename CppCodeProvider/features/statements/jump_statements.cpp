#include "jump_statements.h"
#include "../expressions/unary_expressions.h"
#include "../../formatters/formatter_settings.h"

using namespace std;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;

namespace
{
primitive_expression placeholder("");
}

jump_statement::jump_statement(jump_type t)
	: j_type(t)
{
}

jump_type jump_statement::type() const
{
	return j_type;
}

unique_ptr<statement> jump_statement::clone() const
{
	return make_unique<jump_statement>(*this);
}

void jump_statement::write(ostream &os) const
{
	auto indent = formatter_settings::settings.get_indent_string();
	if (comment.size() > 0)
		os << indent << "//" << comment << endl;

	os << indent;
	switch (j_type)
	{
	case jump_type::continue_jump:
		os << "continue;" << endl;
		break;
	case jump_type::break_jump:
		os << "break;" << endl;
		break;
	case jump_type::goto_jump:
		os << "goto " << *e1 << endl;
		break;
	case jump_type::return_jump:
		os << "return ";
		if (e1)
			os << *e1;
		os << ";" << endl;
		break;
	}
}

ostream &cpp::codeprovider::statements::operator<<(ostream &os, jump_type t)
{
	switch (t)
	{
	case jump_type::break_jump:
		os << "break;";
		break;
	case jump_type::continue_jump:
		os << "continue;";
		break;
	case jump_type::goto_jump:
		os << "goto;";
		break;
	case jump_type::return_jump:
		os << "return;";
		break;
	}
	return os;
}