#include "expression_statement.h"
#include "..\expressions\common.h"
#include "..\..\formatters\formatter_settings.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace formatting;

	expression_statement::expression_statement(unique_ptr<expressions::expression> e)
		: e1(move(e))
	{
	}

	expression_statement::expression_statement(const expression_statement& other)
		: expression_statement(other.e1->clone())
	{
	}

	const expressions::expression & expression_statement::expression() const
	{
		return *e1;
	}

	void expression_statement::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();
		if (comment.size() > 0)
			os << indent << "//" << comment << endl;
		os << indent << *e1 << ";" << endl;
	}

	unique_ptr<statement> expression_statement::clone() const
	{
		return make_unique<expression_statement>(*this);
	}
}