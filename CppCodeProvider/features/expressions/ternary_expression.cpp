#include "ternary_expression.h"

namespace cpp::codeprovider::expressions
{
	using namespace std;

	ternary_expression::ternary_expression(unique_ptr<expression> a, unique_ptr<expression> b, unique_ptr<expression> c)
		:e1(move(a)), e2(move(b)), e3(move(c))
	{
	}

	unique_ptr<expression> ternary_expression::clone() const
	{
		return make_unique<ternary_expression>(*this);
	}

	const expression& ternary_expression::condition() const
	{
		return *e1;
	}

	const expression& ternary_expression::left() const
	{
		return *e2;
	}

	const expression& ternary_expression::right() const
	{
		return *e3;
	}

	expression_type ternary_expression::type() const
	{
		return expression_type::conditional;
	}

	void ternary_expression::write(ostream& os)const
	{
		os << *e1 << " ? " << *e2 << " : " << *e3;
	}
}
