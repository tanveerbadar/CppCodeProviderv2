#include "declarator_specifier.h"
#include "../types/common.h"

using namespace std;

namespace cpp::codeprovider::declarations
{
	using namespace types;

	declarator_specifier::declarator_specifier(shared_ptr<types::type> t)
		:type(t)
	{
	}

	std::shared_ptr<types::type> declarator_specifier::get_type() const
	{
		return type;
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
		os << ds.get_type()->get_name() << " ";

		return os;
	}
}