#include "binary_expressions.h"

using namespace std;
using namespace cpp::codeprovider::expressions;

binary_expression::binary_expression(expression_type t, unique_ptr<expression> l, unique_ptr<expression> r)
	: e_type(t), e1(move(l)), e2(move(r))
{
}

const expression &binary_expression::left() const
{
	return *e1;
}

const expression &binary_expression::right() const
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

void binary_expression::write(ostream &os) const
{
	switch (e_type)
	{
	case expression_type::subscript:
		os << *e1 << "[" << *e2 << "]";
		break;
	default:
		os << *e1 << ' ' << e_type << ' ' << *e2;
		break;
	}
}
