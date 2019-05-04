#include <sstream>
#include "base_type.h"
#include "template_parameters.h"
#include "union_type.h"
#include "../../features/declarations/variable_declaration.h"
#include "../../features/expressions/common.h"
#include "../../features/statements/try_statement.h"
#include "../../features/functions/callable.h"
#include "../../features/functions/member_function.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::utils;

union_type::union_type(const string &str)
    : type(str), impl(type_key::union_type)
{
}

member_function_list &union_type::member_functions()
{
    return impl.functions;
}

const member_field_list &union_type::member_fields() const
{
    return impl.fields;
}

member_field_list &union_type::member_fields()
{
    return impl.fields;
}

template_parameter_list &union_type::template_parameters()
{
    return impl.template_params;
}

unique_ptr<type> union_type::clone() const
{
    return make_unique<union_type>(*this);
}

ostream &union_type::write_declaration(ostream &os) const
{
    if (impl.template_params.size() > 0)
    {
        os << "template<";
        write_vector(os, impl.template_params);
        os << ">";
    }
    os << "union " << get_name() << endl;
    os << "{" << endl;
    ostringstream private_stream, protected_stream, public_stream;
    write_members(impl.fields, public_stream, private_stream, protected_stream, public_stream);

    vector<cpp::codeprovider::internals::write_backlog_entry> write_backlog;

    if (impl.template_params.size() > 0)
        write_definitions(impl.functions, public_stream, private_stream, protected_stream, public_stream, write_backlog);
    else
        write_declarations(impl.functions, public_stream, private_stream, protected_stream, public_stream);

    os << "private:" << endl;
    os << private_stream.str() << endl;
    os << "protected:" << endl;
    os << protected_stream.str() << endl;
    os << "public: " << endl;
    os << public_stream.str() << endl;
    os << "};" << endl;
    return os;
}

ostream &union_type::write_definition(ostream &os) const
{
    write_definitions(os, impl.functions);
    
    return os;
}