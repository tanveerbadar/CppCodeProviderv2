#include "base_type.h"
#include "custom_type.h"
#include "template_parameters.h"
#include "../declarations/common.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../functions/callable.h"
#include "../functions/member_function.h"
#include "../statements/try_statement.h"

using namespace std;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::types::internals;

std::ostream &cpp::codeprovider::types::internals::operator<<(std::ostream &os, type_key key)
{
    switch (key)
    {
    case type_key::class_type:
        os << "class ";
        break;
    case type_key::enum_type:
        os << "enum ";
        break;
    case type_key::struct_type:
        os << "struct ";
        break;
    case type_key::union_type:
        os << "union ";
        break;
    }
    return os;
}

custom_type::custom_type(type_key k)
    : key(k)
{
}

bool custom_type::is_class() const
{
    return key == type_key::class_type;
}