#include "ranged_for_loop.h"
#include "../expressions/unary_expressions.h"
#include "../../formatters/formatter_settings.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace formatting;

	namespace
	{
		primitive_expression placeholder("");
	}

	ranged_for_loop::ranged_for_loop(const ranged_for_loop& other)
		: init((other.init ? *other.init : placeholder).clone()), body(other.body)
	{
	}

	ranged_for_loop& ranged_for_loop::operator=(const ranged_for_loop& other)
	{
		if (this != &other)
		{
			auto temp = other.initializer().clone();
			body = other.body;
			init = move(temp);
		}
		return *this;
	}

	unique_ptr<statement> ranged_for_loop::clone() const
	{
		return make_unique<ranged_for_loop>(*this);
	}

	void ranged_for_loop::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();

		if (comment.size() > 0)
			os << indent << "//" << comment << endl;
		os << indent << "for( ";
		if (init)
			os << *init;
		os << " )" << endl;
		os << body;
	}

	const expression& ranged_for_loop::initializer() const
	{
		return init ? *init : placeholder;
	}

	ranged_for_loop& ranged_for_loop::initializer(unique_ptr<expression> i)
	{
		init = move(i);
		return *this;
	}

	vector<unique_ptr<statement>>& ranged_for_loop::statements()
	{
		return body.statements();
	}

	const vector<unique_ptr<statement>>& ranged_for_loop::statements() const
	{
		return body.statements();
	}
}