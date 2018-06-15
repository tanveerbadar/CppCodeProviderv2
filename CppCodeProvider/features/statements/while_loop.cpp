#include "while_loop.h"
#include "..\expressions\common.h"
#include "..\..\formatters\formatter_settings.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace formatting;

	while_loop::while_loop()
		:body()
	{
	}

	while_loop::while_loop(const while_loop& other)
		: body(other.body), condition_exp(other.condition_exp->clone())
	{
	}

	unique_ptr<statement> while_loop::clone() const
	{
		return make_unique<while_loop>(*this);
	}

	void while_loop::write(ostream& os) const
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
			os << indent << "while(" << *condition_exp << ");" << endl;
	}

	const expression& while_loop::condition() const
	{
		return *condition_exp;
	}

	while_loop& while_loop::condition(unique_ptr<expression> c)
	{
		condition_exp = move(c);
		return *this;
	}

	vector<unique_ptr<statement>>& while_loop::statements()
	{
		return body.statements();
	}
}