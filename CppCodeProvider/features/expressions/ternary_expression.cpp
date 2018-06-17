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

	ternary_expression& ternary_expression::operator=(const ternary_expression& other)
	{
		if (this != &other)
		{
			auto temp1 = other.e1->clone();
			auto temp2 = other.e2->clone();
			auto temp3 = other.e3->clone();
			e1 = move(temp1);
			e2 = move(temp2);
			e3 = move(temp3);
		}
		return *this;
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
