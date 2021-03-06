#include "union_type.h"
#include "../../utils/dirty_macros.h"
#include "../../utils/write_helpers.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../functions/constructor.h"
#include "../functions/function.h"
#include "../functions/member_function.h"
#include "../statements/try_statement.h"
#include "base_type.h"
#include "template_parameters.h"
#include <sstream>

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::namespaces;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::internals;
using namespace cpp::codeprovider::utils;

union_type::union_type(const string &str)
    : type(str), impl(type_key::union_type)
{
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

friend_functions_list &union_type::friend_functions()
{
    return impl.friend_functions;
}

friend_types_list &union_type::friend_types()
{
    return impl.friend_types;
}

//ACCESSOR_IMPL_2(union_type, is_final, bool, final)

unique_ptr<namespace_scope_entity> union_type::clone() const
{
    return make_unique<union_type>(*this);
}

ostream &union_type::write_forward_declaration(ostream &os) const
{
    utils::write_template_parameters(os, impl.template_params);
    os << "union " << get_name() << ";" << endl;

    return os;
}

ostream &union_type::write_template_parameters(ostream &os) const
{
    utils::write_template_parameters(os, impl.template_params);
    return os;
}

ostream &union_type::write_elaborated_name(ostream &os) const
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

ostream &union_type::write_declaration(ostream &os) const
{
    utils::write_template_parameters(os, impl.template_params);
    os << "union " << get_name();
    if (final)
        os << " final";
    os << endl;
    os << "{" << endl;
    ostringstream private_stream, protected_stream, public_stream;
    write_members(impl.fields, public_stream, private_stream, protected_stream, public_stream);

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

    os << "};" << endl;
    return os;
}

ostream &union_type::write_definition(ostream &os) const
{
    write_definitions(os, impl.functions);

    return os;
}