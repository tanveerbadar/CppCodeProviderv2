#include "declarator_specifier.h"

using namespace std;

namespace cpp::codeprovider::types
{
	class type
	{
	public:
		string name;
	};
}

namespace cpp::codeprovider::declarations
{
	using namespace types;

	declarator_specifier::declarator_specifier(const types::type& t)
		:type(&t)
	{
	}

	const type& declarator_specifier::get_type() const
	{
		return *type;
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