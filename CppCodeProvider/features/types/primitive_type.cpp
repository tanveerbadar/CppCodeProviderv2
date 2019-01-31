#include "primitive_type.h"

using namespace std;
using namespace cpp::codeprovider::types;

primitive_type::primitive_type(const string& name)
	:type(name)
{
}

ostream &primitive_type::write_declaration(ostream &os) const
{
	os << get_name();
}

ostream &primitive_type::write_definition(ostream &os) const
{
	os << get_name();
}

unique_ptr<type> primitive_type::clone() const
{
	return make_unique<primitive_type>(*this);
}
