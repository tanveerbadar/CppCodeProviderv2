#include <sstream>
#include "union_type.h"
#include "../../features/declarations/variable_declaration.h"
#include "../../features/expressions/common.h"
#include "../../features/statements/try_statement.h"
#include "../../features/functions/callable.h"
#include "../../features/functions/member_function.h"
#include "../../features/types/template_parameters.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::utils;

union_type::union_type(const string& str)
    :type(str)
{

}

union_type::union_type(const union_type &other)
    : type(other)
{
    for (auto &f : other.fields)
        fields.push_back(make_pair(f.first, f.second->clone()));
}

union_type &union_type::operator=(const union_type &other)
{
    if (this != &other)
    {
        type::operator=(other);
    }
    return *this;
}

member_function_list &union_type::member_functions()
{
    return functions;
}

const member_field_list& union_type::member_fields() const
{
    return fields;
}

member_field_list &union_type::member_fields()
{
    return fields;
}

template_parameter_list &union_type::template_parameters()
{
    return template_params;
}

unique_ptr<type> union_type::clone() const
{
    return make_unique<union_type>(*this);
}

ostream &union_type::write_declaration(ostream &os) const
{
    if (template_params.size() > 0)
    {
        os << "template<";
        write_vector(os, template_params);
        os << ">";
    }
    os << "union " << get_name() << ";" << endl;
    return os;
}

ostream &union_type::write_definition(ostream & os) const
{
    if (template_params.size() > 0)
    {
        os << "template<";
        write_vector(os, template_params);
        os << ">";
    }
    os << "union " << get_name() << endl;
    os << "{" << endl;
    ostringstream private_stream, protected_stream, public_stream;
    write_members(fields, public_stream, private_stream, protected_stream, public_stream);
    write_declarations(functions, public_stream, private_stream, protected_stream, public_stream);
    os << "private:" << endl;
    os << private_stream.str() << endl;
    os << "protected:" << endl;
    os << protected_stream.str() << endl;
    os << "public: " << endl;
    os << public_stream.str() << endl;
    os << "};" << endl;
	return os;
}