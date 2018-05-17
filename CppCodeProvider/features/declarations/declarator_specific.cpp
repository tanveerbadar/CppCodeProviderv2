#include "declarator_specific.h"

namespace cpp::codeprovider::declarations
{
	using namespace std;

	declarator_specifier::declarator_specifier(const types::type_declaration& t)
		:type(&t)
	{
	}

	ostream & operator<<(ostream& os, const declarator_specifier& ds)
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
		os << ds.get_type().name << " ";

		return os;
	}
}