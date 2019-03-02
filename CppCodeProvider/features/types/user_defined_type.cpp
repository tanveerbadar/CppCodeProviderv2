#include <sstream>
#include "template_parameters.h"
#include "user_defined_type.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../functions/callable.h"
#include "../functions/member_function.h"
#include "../statements/try_statement.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::utils;

user_defined_type::user_defined_type(const string &name)
	: type(name), impl(type_key::class_type)
{
}

member_function_list &user_defined_type::member_functions()
{
	return impl.functions;
}

member_field_list &user_defined_type::member_fields()
{
	return impl.fields;
}

base_list &user_defined_type::bases()
{
	return impl.base_types;
}

template_parameter_list &user_defined_type::template_parameters()
{
	return impl.template_params;
}

ostream& user_defined_type::write_declaration(ostream &os) const
{
	if (impl.template_params.size() > 0)
	{
		os << "template<";
		write_vector(os, impl.template_params);
		os << ">";
	}

	os << impl.key << get_name() << endl;
	write_vector(os, impl.base_types);
	os << "{" << endl;
	ostringstream private_stream, protected_stream, public_stream;
	write_members(impl.fields, impl.is_class() ? private_stream : public_stream, private_stream, protected_stream, public_stream);
	write_declarations(impl.functions, impl.is_class() ? private_stream : public_stream, private_stream, protected_stream, public_stream);
	os << "private:" << endl;
	os << private_stream.str() << endl;
	os << "protected:" << endl;
	os << protected_stream.str() << endl;
	os << "public: " << endl;
	os << public_stream.str() << endl;
	os << "};" << endl << endl;
	return os;
}

ostream& user_defined_type::write_definition(ostream& os) const
{
	write_definitions(os, impl.functions);

	return os;
}

unique_ptr<type> user_defined_type::clone() const
{
	return make_unique<user_defined_type>(*this);
}
