#include "user_defined_type.h"
#include "..\functions\callable.h"
#include "template_parameter.h"

using namespace std;
using namespace cpp::codeprovider::types;

user_defined_type::user_defined_type(const string& name)
	:type(name)
{
}

user_defined_type::user_defined_type(const user_defined_type& other)
	: type(other)
{
}

void user_defined_type::write(ostream& os) const
{
	os << "class " << get_name() << endl;
	os << "{" << endl;
	os << "};" << endl << endl;
}

unique_ptr<type> user_defined_type::clone() const
{
	return make_unique<user_defined_type>(*this);
}
