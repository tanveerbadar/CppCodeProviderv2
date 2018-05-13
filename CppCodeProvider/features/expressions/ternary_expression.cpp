#include "ternary_expression.h"

namespace cpp::codeprovider::expressions
{
	using namespace std;

	ternary_expression::ternary_expression(unique_ptr<expression> a, unique_ptr<expression> b, unique_ptr<expression> c)
		:e1(move(a)), e2(move(b)), e3(move(c))
	{
	}

	ternary_expression::ternary_expression(const ternary_expression& other)
		: e1(other.e1->clone()), e2(other.e2->clone()), e3(other.e3->clone())
	{
	}

	unique_ptr<expression> ternary_expression::clone() const
	{
		return make_unique<ternary_expression>(*this);
	}

	void ternary_expression::write(ostream& os)const
	{
		os << *e1 << " ? " << *e2 << " : " << *e3;
	}
}
