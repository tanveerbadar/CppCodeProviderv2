#include "declarator.h"
#include "..\expressions\unary_expressions.h"

namespace cpp::codeprovider::declarations
{
	using namespace std;
	using namespace expressions;

	declarator::declarator(const declarator& other)
		:initializer_exp(other.initializer_exp ? other.initializer_exp->clone() : make_unique<primitive_expression>("")), name(other.name), is_rvalue_ref(other.is_rvalue_ref), is_lvalue_ref(other.is_lvalue_ref), is_constant(other.is_constant), is_volatile(other.is_volatile), pointer_level(other.pointer_level), array_dimensions(other.array_dimensions)
	{
	}

	ostream& operator<<(ostream & os, const declarator& d)
	{
		if (d.is_lvalue_ref)
			os << "& ";
		if (d.is_rvalue_ref)
			os << "&& ";
		if (d.is_constant)
			os << "const ";
		if (d.is_volatile)
			os << "volatile ";
		if (d.pointer_level > 0)
			os << string(d.pointer_level, '*');
		os << d.name;
		for (auto dim : d.array_dimensions)
			os << "[" << dim << "]";

		auto ptr = dynamic_cast<primitive_expression*>(d.initializer_exp.get());
		auto has_initializer = ptr && ptr->expr().size() > 0;

		if (has_initializer)
			os << " = " << *d.initializer_exp;

		return os;
	}
}
