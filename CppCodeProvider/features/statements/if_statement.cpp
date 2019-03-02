#include "if_statement.h"
#include "../expressions/common.h"
#include "../../formatters/formatter_settings.h"
#include "../../utils/write_helpers.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace formatting;

	if_statement::if_statement(unique_ptr<expression> c)
		:condition_exp(move(c))
	{
	}

	statement_list &if_statement::if_block()
	{
		return if_collection.statements();
	}

	const statement_list &if_statement::if_block() const
	{
		return if_collection.statements();
	}

	statement_list &if_statement::else_block()
	{
		return else_collection.statements();
	}

	const statement_list &if_statement::else_block() const
	{
		return else_collection.statements();
	}

	ACCESSOR_IMPL_2(if_statement, is_constexpr, bool, is_const_expr)

	const expression& if_statement::condition() const
	{
		return *condition_exp;
	}

	if_statement& if_statement::condition(unique_ptr<expression> e)
	{
		condition_exp = move(e);
		return *this;
	}

	unique_ptr<statement> if_statement::clone() const
	{
		return make_unique<if_statement>(condition_exp->clone());
	}

	void if_statement::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();
		os << indent << "if " ;
		if(is_const_expr)
			os << "constexpr ";
		os << "( " << *condition_exp << " )" << endl;
		os << if_collection;
		if (else_collection.statements().size() > 0)
		{
			os << indent << "else" << endl;
			os << else_collection;
		}
	}
}