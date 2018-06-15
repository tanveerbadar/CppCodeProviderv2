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

	while_loop& while_loop::operator=(const while_loop& other)
	{
		if (this != &other)
		{
			auto temp1 = other.condition_exp->clone();
			body = other.body;
			condition_exp = move(temp1);
			loop_style = other.loop_style;
		}
		return *this;
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

	while_loop_style while_loop::style() const
	{
		return loop_style;
	}

	while_loop& while_loop::style(while_loop_style wls)
	{
		loop_style = wls;
		return *this;
	}

	vector<unique_ptr<statement>>& while_loop::statements()
	{
		return body.statements();
	}

	ostream& operator<<(ostream& os, while_loop_style wls)
	{
		os << (wls == while_loop_style::do_while_loop ? "do-while" : "while");
		return os;
	}
}