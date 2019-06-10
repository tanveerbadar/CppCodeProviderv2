#include <sstream>
#include "template_parameters.h"
#include "user_defined_type.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../functions/callable.h"
#include "../functions/function.h"
#include "../functions/member_function.h"
#include "../statements/try_statement.h"
#include "../../utils/write_helpers.h"
#include "../internals/write_backlog_entry.h"

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

friend_functions_list &user_defined_type::friend_functions()
{
	return impl.friend_functions;
}

friend_types_list &user_defined_type::friend_types()
{
	return impl.friend_types;
}

base_list &user_defined_type::bases()
{
	return impl.base_types;
}

template_parameter_list &user_defined_type::template_parameters()
{
	return impl.template_params;
}

ACCESSOR_IMPL_2(user_defined_type, is_final, bool, final)

ostream &user_defined_type::write_forward_declaration(ostream &os) const
{
	utils::write_template_parameters(os, impl.template_params);
	os << impl.key << get_name() << ";" << endl;

	return os;
}

ostream &user_defined_type::write_template_parameters(ostream &os) const
{
	utils::write_template_parameters(os, impl.template_params);
	return os;
}

ostream &user_defined_type::write_elaborated_name(ostream &os) const
{
	os << get_name();
	if (impl.template_params.size() > 0)
	{
		os << "<";
		write_vector(os, impl.template_params);
		os << ">";
	}
	return os;
}

ostream &user_defined_type::write_declaration(ostream &os) const
{
	write_template_parameters(os);

	os << impl.key << get_name();
	if (final)
		os << " final";
	if (impl.base_types.size())
	{
		os << " : ";
		write_vector(os, impl.base_types);
	}
	os << endl
	   << "{" << endl;
	ostringstream private_stream, protected_stream, public_stream;
	write_members(impl.fields, impl.is_class() ? private_stream : public_stream, private_stream, protected_stream, public_stream);

	vector<const cpp::codeprovider::internals::write_backlog_entry *> write_backlog;

	if (impl.template_params.size() > 0)
		write_definitions(impl.functions, impl.is_class() ? private_stream : public_stream, private_stream, protected_stream, public_stream, write_backlog);
	else
		write_declarations(impl.functions, impl.is_class() ? private_stream : public_stream, private_stream, protected_stream, public_stream);

	os << "private:" << endl;
	os << private_stream.str() << endl;
	os << "protected:" << endl;
	os << protected_stream.str() << endl;
	os << "public: " << endl;
	os << public_stream.str() << endl;

	for (auto &ff : impl.friend_functions)
		ff->write_declaration(os);

	for (auto &ft : impl.friend_types)
		ft->write_forward_declaration(os);

	os << "};" << endl
	   << endl;

	for (auto &entry : write_backlog)
		entry->write_definition(os);

	return os;
}

ostream &user_defined_type::write_definition(ostream &os) const
{
	write_definitions(os, impl.functions);

	return os;
}

unique_ptr<type> user_defined_type::clone() const
{
	return make_unique<user_defined_type>(*this);
}
