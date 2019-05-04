#include "primitive_type.h"

using namespace std;
using namespace cpp::codeprovider::types;

primitive_type::primitive_type(const string& name)
	:type(name)
{
}

ostream& primitive_type::write_forward_declaration(ostream& os) const
{
	return write_declaration(os);
}

ostream &primitive_type::write_declaration(ostream &os) const
{
	os << get_name();
	return os;
}

ostream &primitive_type::write_definition(ostream &os) const
{
	os << get_name();
	return os;
}

unique_ptr<type> primitive_type::clone() const
{
	return make_unique<primitive_type>(*this);
}
