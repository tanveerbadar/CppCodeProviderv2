#include "while_loop.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace codeprovider::formatting;

	while_loop::while_loop()
		:body(make_unique<block_statement>())
	{
	}

	while_loop::while_loop(const while_loop& other)
		: //body(other.body->clone()), 
		condition_exp(other.condition_exp->clone())
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
		if (body)
			os << *body;
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

	block_statement& while_loop::loop_body() const
	{
		return *body;
	}
}