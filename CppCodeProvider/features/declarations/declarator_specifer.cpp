#include "declarator_specifier.h"

namespace cpp::codeprovider::types
{
	class type
	{
	public:
		std::string name;

		virtual std::unique_ptr<type> clone() const
		{
			return std::make_unique<type>(*this);
		}
	};
}

namespace cpp::codeprovider::declarations
{
	using namespace std;
	using namespace types;

	declarator_specifier::declarator_specifier(std::unique_ptr<types::type> t)
		:type(move(t))
	{
	}

	declarator_specifier::declarator_specifier(const declarator_specifier& other)
		: is_static(other.is_static), is_constant(other.is_constant), is_volatile(other.is_volatile), is_auto(other.is_auto), is_extern(other.is_extern), type(other.type->clone())
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