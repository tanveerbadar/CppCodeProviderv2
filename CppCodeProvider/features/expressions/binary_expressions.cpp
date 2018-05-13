#include "binary_expressions.h"
#include "..\..\exceptions.h"

namespace cpp::codeprovider::primitives
{
	using namespace std;

	namespace
	{
		bool is_valid_expression(expression_type type)
		{
			switch (type)
			{
			case expression_type::addition:
			case expression_type::subtraction:
			case expression_type::multiplication:
			case expression_type::division:
			case expression_type::modulus:
			case expression_type::assignment:
			case expression_type::subscript:
			case expression_type::and_exp:
			case expression_type::or_exp:
			case expression_type::member_access:
			case expression_type::comma:
			case expression_type::left_shift:
			case expression_type::right_shift:
			case expression_type::less:
			case expression_type::greater:
			case expression_type::less_equal:
			case expression_type::greater_equal:
			case expression_type::equal:
			case expression_type::not_equal:
			case expression_type::bit_and:
			case expression_type::bit_or:
			case expression_type::xor_exp:
			case expression_type::add_assign:
			case expression_type::subtract_assign:
			case expression_type::multiply_assign:
			case expression_type::divide_assign:
			case expression_type::modulus_assign:
			case expression_type::left_shift_assign:
			case expression_type::right_shift_assign:
			case expression_type::bit_and_assign:
			case expression_type::bit_or_assign:
			case expression_type::xor_assign:
				return true;
			default:
				return false;
			}
		}
	}

	binary_expression::binary_expression(expression_type t, unique_ptr<expression> l, unique_ptr<expression> r)
		: e_type(is_valid_expression(t) ? t : throw exceptions::invalid_expression_type("binary expression does not expect type.")), e1(move(l)), e2(move(r))
	{
	}

	binary_expression::binary_expression(const binary_expression& other)
		: binary_expression(other.e_type, other.e1->clone(), other.e2->clone())
	{
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