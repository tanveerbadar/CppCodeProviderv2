#include "declarator_specifier.h"
#include "../types/common.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using t = cpp::codeprovider::types::type;

declarator_specifier::declarator_specifier(shared_ptr<t> t)
	: type(t)
{
}

std::shared_ptr<t> declarator_specifier::get_type() const
{
	return type;
}

ostream &cpp::codeprovider::declarations::operator<<(ostream &os, const declarator_specifier &ds)
{
	if (ds.is_auto)
		os << "auto ";
	if (ds.is_extern)
		os << "extern ";
	if (ds.is_constant)
		os << "const ";
	if (ds.is_volatile)
		os << "volatile ";
	if (ds.is_static)
		os << "static ";
	os << ds.get_type()->get_name() << " ";

	return os;
}
