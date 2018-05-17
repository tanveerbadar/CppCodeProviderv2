#include "declarator.h"
#include "..\expressions\unary_expressions.h"

namespace cpp::codeprovider::declarations
{
	using namespace std;
	using namespace expressions;

	declarator::declarator(const declarator& other)
		:initializer_exp(other.initializer_exp ? other.initializer_exp->clone() : make_unique<primitive_expression>(""))
	{
	}

	ostream& operator<<(ostream & os, const declarator& d)
	{
		if (d.pointer_level > 0)
			os << string(d.pointer_level, '*');
		if (d.is_lvalue_ref)
			os << "& ";
		if (d.is_rvalue_ref)
			os << "&& ";
		if (d.is_constant)
			os << "const ";
		if (d.is_volatile)
			os << "volatile ";

		os << d.name;

		for (auto dim : d.array_dimensions)
			os << "[" << dim << "]";

		if (d.initializer_exp)
			os << " = " << *d.initializer_exp;

		return os;
	}
}
