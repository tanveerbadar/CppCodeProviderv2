#include "unary_expressions.h"

namespace cpp::codeprovider::expressions
{
	using namespace std;

	unary_expression::unary_expression(expression_type t, unique_ptr<expression> expr)
		: e_type(t), e1(move(expr))
	{
	}

	unique_ptr<expression> unary_expression::clone() const
	{
		return make_unique<unary_expression>(*this);
	}

	const expression& unary_expression::expr() const
	{
		return *e1;
	}

	expression_type unary_expression::type() const
	{
		return e_type;
	}

	void unary_expression::write(ostream& os) const
	{
		switch(e_type)
		{
		case expression_type::parenthesis:
			os << "(" << *e1 << ")";
			break;
		case expression_type::size_of:
			os << "sizeof(" << *e1 << ")";
			break;
		case expression_type::decltype_exp:
			os << "decltype(" << *e1 << ")";
			break;
		case expression_type::typeid_op:
			os << "typeid(" << *e1 << ")";
			break;
		case expression_type::postfix_decrement:
			os << *e1 << "--";
			break;
		case expression_type::postfix_increment:
			os << *e1 << "++";
			break;
		default:
			os << e_type << *e1;
			break;
		}
	}

	primitive_expression::primitive_expression(const string& p)
		:e1(p)
	{
	}

	const string& primitive_expression::expr() const
	{
		return e1;
	}

	expression_type primitive_expression::type() const
	{
		return expression_type::primitive;
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