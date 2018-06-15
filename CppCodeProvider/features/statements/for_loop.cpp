#include "for_loop.h"
#include "..\expressions\unary_expressions.h"
#include "..\..\formatters\formatter_settings.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace formatting;

	primitive_expression placeholder("");

	for_loop::for_loop(const for_loop& other)
		: init((other.init ? *other.init : placeholder).clone()), condition_exp((other.condition_exp ? *other.condition_exp : placeholder).clone()), loop_exp((other.loop_exp ? *other.loop_exp : placeholder).clone()), body(other.body)
	{
	}

	for_loop& for_loop::operator=(const for_loop& other)
	{
		if (this != &other)
		{
			auto temp1 = other.initializer().clone();
			auto temp2 = other.condition().clone();
			auto temp3 = other.loop().clone();
			body = other.body;
			init = move(temp1);
			condition_exp = move(temp2);
			loop_exp = move(temp3);
		}
		return *this;
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
		os << indent << "for( ";
		if (init)
			os << *init;
		os << "; ";
		if (condition_exp)
			os << *condition_exp;
		os << "; ";
		if (loop_exp)
			os << *loop_exp;
		os << " )" << endl;
		os << body;
	}

	const expression& for_loop::initializer() const
	{
		return init ? *init : placeholder;
	}

	for_loop& for_loop::initializer(unique_ptr<expression> i)
	{
		init = move(i);
		return *this;
	}

	const expression& for_loop::condition() const
	{
		return condition_exp ? *condition_exp : placeholder;
	}

	for_loop& for_loop::condition(unique_ptr<expression> c)
	{
		condition_exp = move(c);
		return *this;
	}

	const expression& for_loop::loop() const
	{
		return loop_exp ? *loop_exp : placeholder;
	}

	for_loop& for_loop::loop(unique_ptr<expression> l)
	{
		loop_exp = move(l);
		return *this;
	}

	vector<unique_ptr<statement>>& for_loop::statements()
	{
		return body.statements();
	}
}