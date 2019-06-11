#include "declarator.h"
#include "../expressions/unary_expressions.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;

ostream &cpp::codeprovider::declarations::operator<<(ostream &os, const declarator &d)
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

	auto ptr = dynamic_cast<const primitive_expression *>(d.initializer_exp.operator->());
	auto has_initializer = ptr && ptr->expr().size() > 0;

	if (has_initializer)
		os << " = " << *d.initializer_exp;

	return os;
}
