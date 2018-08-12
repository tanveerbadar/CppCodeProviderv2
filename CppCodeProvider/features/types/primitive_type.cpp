#include "primitive_type.h"

using namespace std;
using namespace cpp::codeprovider::types;

primitive_type::primitive_type(const string& name)
	:type(name)
{
}

void primitive_type::write(ostream& os) const
{
	os << get_name();
}

unique_ptr<type> primitive_type::clone() const
{
	return make_unique<primitive_type>(*this);
}
