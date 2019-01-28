#include "unary_expressions.h"

namespace cpp::codeprovider::expressions
{
	using namespace std;

	namespace
	{
		bool is_postfix_operator(expression_type type)
		{
			return type == expression_type::postfix_decrement || type == expression_type::postfix_increment;
		}
	}

	unary_expression::unary_expression(expression_type t, unique_ptr<expression> expr)
		: e_type(t), e1(move(expr))
	{
	}

	unary_expression::unary_expression(const unary_expression& other)
		: unary_expression(other.e_type, other.e1->clone())
	{
	}

	unary_expression& unary_expression::operator=(const unary_expression& other)
	{
		if (this != &other)
		{
			e1 = other.e1->clone();
			e_type = other.e_type;
		}
		return *this;
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