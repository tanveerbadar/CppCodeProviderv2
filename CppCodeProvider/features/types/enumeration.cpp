#include "base_type.h"
#include "enumeration.h"
#include "template_parameters.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../functions/callable.h"
#include "../functions/member_function.h"
#include "../statements/try_statement.h"

using namespace std;

namespace cpp::codeprovider::types
{
    using namespace declarations;
    using namespace expressions;

    enumeration::enumeration(const string &e)
        : type(e), impl(type_key::enum_type)
    {
    }

    member_field_list &enumeration::enumerators()
    {
        return impl.fields;
    }

    const member_field_list &enumeration::enumerators() const
    {
        return impl.fields;
    }

    ACCESSOR_IMPL_2(enumeration, is_scoped_enum, bool, impl.is_scoped_enum)

    unique_ptr<type> enumeration::clone() const
    {
        return make_unique<enumeration>(*this);
    }

    ostream& enumeration::write_declaration(ostream& os) const
    {
        os << (impl.is_scoped_enum ? "enum class " : "enum ");
        os << get_name();
        os << ";" << endl;

        return os;
    }

    ostream &enumeration::write_definition(ostream &os) const
    {
        os << (impl.is_scoped_enum ? "enum class " : "enum ");
        os << get_name();
        os << "{" << endl;

        for(auto& e : impl.fields)
        {
            auto member = dynamic_cast<const variable_declaration&>(*e.second);
            os << member.var_declarator().name;
            if(member.var_declarator().initializer_exp)
                os << " = " << *member.var_declarator().initializer_exp;
            os << ", " << endl;
        }

        os << "};" << endl;

        return os;
    }
} // namespace cpp::codeprovider::types