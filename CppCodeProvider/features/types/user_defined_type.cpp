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

namespace
{
	void write_declarations(const vector<member_function> &functions, ostringstream &default_stream, ostringstream &private_stream, ostringstream &protected_stream, ostringstream &public_streams)
	{
		for (const auto &mf : functions)
		{
			switch (mf.accessibility())
			{
			case access_levels::private_access:
				mf.write_declaration(private_stream);
				private_stream << endl;
				break;
			case access_levels::protected_access:
				mf.write_declaration(protected_stream);
				protected_stream << endl;
				break;
			case access_levels::public_access:
				mf.write_declaration(public_streams);
				public_streams << endl;
				break;
			default:
				mf.write_declaration(default_stream);
				default_stream << endl;
				break;
			}
		}
	}
}

user_defined_type::user_defined_type(const string &name)
	: type(name)
{
}

user_defined_type::user_defined_type(const user_defined_type &other)
	: type(other)
{
	for(auto& f: other.functions)
		functions.emplace_back(f);

	for(auto& f:other.fields)
		fields.push_back(make_pair(f.first, f.second->clone()));
}

user_defined_type& user_defined_type::operator=(const user_defined_type& other)
{
	if(this!=&other)
	{
		type::operator=(other);
	}
	return *this;
}

member_function_list &user_defined_type::member_functions()
{
	return functions;
}

member_field_list &user_defined_type::member_fields()
{
	return fields;
}

base_list &user_defined_type::bases()
{
	return base_types;
}

template_parameter_list &user_defined_type::template_parameters()
{
	return template_params;
}

ostream& user_defined_type::write_declaration(ostream &os) const
{
	if (template_params.size() > 0)
	{
		os << "template<";
		write_vector(os, template_params);
		os << ">";
	}

	os << (this->is_class ? "class " : "struct ") << get_name() << endl;
	write_vector(os, base_types);
	os << "{" << endl;
	ostringstream private_stream, protected_stream, public_stream;
	write_members(fields, this->is_class ? private_stream : public_stream, private_stream, protected_stream, public_stream);
	write_declarations(functions, this->is_class ? private_stream : public_stream, private_stream, protected_stream, public_stream);
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
	write_definitions(os, functions);

	return os;
}

unique_ptr<type> user_defined_type::clone() const
{
	return make_unique<user_defined_type>(*this);
}
