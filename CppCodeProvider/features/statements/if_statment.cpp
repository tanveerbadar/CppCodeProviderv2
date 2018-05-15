#include "if_statement.h"
#include "..\expressions\common.h"
#include "..\..\formatters\formatter_settings.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace formatting;

	if_statement::if_statement(unique_ptr<expression> c)
		:condition_exp(move(c))
	{
	}

	block_statement& if_statement::if_block()
	{
		return if_collection;
	}

	block_statement& if_statement::else_block()
	{
		return else_collection;
	}

	unique_ptr<statement> if_statement::clone() const
	{
		return make_unique<if_statement>(condition_exp->clone());
	}

	void if_statement::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();
		os << indent << "if( " << *condition_exp << " )" << endl;
		os << if_collection;
		if (else_collection.statements().size() > 0)
		{
			os << indent << "else" << endl;
			os << else_collection;
		}
	}
}