#include "binary_expressions.h"

namespace cpp::codeprovider::expressions
{
	using namespace std;

	binary_expression::binary_expression(expression_type t, unique_ptr<expression> l, unique_ptr<expression> r)
		: e_type(t), e1(move(l)), e2(move(r))
	{
	}

	binary_expression::binary_expression(const binary_expression& other)
		: binary_expression(other.e_type, other.e1->clone(), other.e2->clone())
	{
	}

	binary_expression& binary_expression::operator=(const binary_expression& other)
	{
		if (this != &other)
		{
			auto temp1 = other.e1->clone();
			auto temp2 = other.e2->clone();
			e_type = other.e_type;
			e1 = move(temp1);
			e2 = move(temp2);
		}
		return *this;
	}

	const expression& binary_expression::left() const
	{
		return *e1;
	}

	const expression& binary_expression::right() const
	{
		return *e2;
	}

	expression_type binary_expression::type() const
	{
		return e_type;
	}

	unique_ptr<expression> binary_expression::clone() const
	{
		return make_unique<binary_expression>(*this);
	}

	void binary_expression::write(ostream& os) const
	{
		if (e_type == expression_type::subscript)
			os << *e1 << "[" << *e2 << "]";
		else
			os << *e1 << e_type << *e2;
	}
}