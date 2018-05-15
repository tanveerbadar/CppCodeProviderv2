#include "unary_expressions.h"
#include "..\..\exceptions.h"

namespace cpp::codeprovider::expressions
{
	using namespace std;

	namespace
	{
		bool is_valid_expression(expression_type type)
		{
			switch (type)
			{
			case expression_type::address_of:
			case expression_type::complement:
			case expression_type::not_exp:
			case expression_type::negate:
			case expression_type::parenthesis:
			case expression_type::plus:
			case expression_type::postfix_decrement:
			case expression_type::postfix_increment:
			case expression_type::prefix_decrement:
			case expression_type::prefix_increment:
			case expression_type::throw_exp:
			case expression_type::size_of:
			case expression_type::decltype_exp:
				//case expression_type::static_cast_exp:
			//case expression_type::const_cast_exp:
			//case expression_type::reinterpret_cast_exp:
			//case expression_type::dynamic_cast_exp:
			//case expression_type::c_cast_exp:
				return true;
			default:
				return false;
			}
		}

		bool is_postfix_operator(expression_type type)
		{
			return type == expression_type::postfix_decrement || type == expression_type::postfix_increment;
		}
	}

	unary_expression::unary_expression(expression_type t, unique_ptr<expression> expr)
		: e_type(is_valid_expression(t) ? t : throw exceptions::invalid_expression_type("unary expression does not expect type.")), e1(move(expr))
	{
	}

	unary_expression::unary_expression(const unary_expression& other)
		: unary_expression(other.e_type, other.e1->clone())
	{
	}

	unique_ptr<expression> unary_expression::clone() const
	{
		return make_unique<unary_expression>(*this);
	}

	void unary_expression::write(ostream& os) const
	{
		if (is_postfix_operator(e_type))
			os << *e1 << e_type;
		else if (e_type == expression_type::parenthesis)
			os << "(" << *e1 << ")";
		else if (e_type == expression_type::size_of)
			os << "sizeof(" << *e1 << ")";
		else if (e_type == expression_type::decltype_exp)
			os << "decltype(" << *e1 << ")";
		else
			os << e_type << *e1;
	}

	primitive_expression::primitive_expression(const string& p)
		:e1(p)
	{
	}

	unique_ptr<expression> primitive_expression::clone() const
	{
		return make_unique<primitive_expression>(*this);
	}

	void primitive_expression::write(ostream& os) const
	{
		os << e1;
	}
}