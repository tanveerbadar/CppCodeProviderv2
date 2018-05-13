#include "for_loop.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace codeprovider::formatting;

	for_loop::for_loop()
		:body(make_unique<block_statement>())
	{
	}

	for_loop::for_loop(const for_loop& other)
		: body(make_unique<block_statement>(*other.body)), 
		init(other.init->clone()),
		condition_exp(other.condition_exp->clone()),
		loop_exp(other.loop_exp->clone())
	{
	}

	unique_ptr<statement> for_loop::clone() const
	{
		return make_unique<for_loop>(*this);
	}

	void for_loop::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();

		if (comment.size() > 0)
			os << indent << "//" << comment << endl;
		os << "for( ";
		if (init)
			os << *init;
		os << "; ";
		if (condition_exp)
			os << *condition_exp;
		os << "; ";
		if (loop_exp)
			os << *loop_exp;
		os << " )" << endl;
		if (body)
			os << *body;
		else
			os << ";";
	}

	const expression& for_loop::initializer() const
	{
		return *init;
	}

	for_loop& for_loop::initializer(unique_ptr<expression> i)
	{
		init = move(i);
		return *this;
	}

	const expression& for_loop::condition() const
	{
		return *condition_exp;
	}

	for_loop& for_loop::condition(unique_ptr<expression> c)
	{
		condition_exp = move(c);
		return *this;
	}

	const expression& for_loop::loop() const
	{
		return *loop_exp;
	}

	for_loop& for_loop::loop(unique_ptr<expression> l)
	{
		loop_exp = move(l);
		return *this;
	}

	block_statement& for_loop::loop_body() const
	{
		return *body;
	}
}