#include <iostream>
#include <string>
#include <memory>
#include "base_type.h"
#include "template_parameters.h"
#include "user_defined_type.h"

using namespace std;

using namespace cpp::codeprovider::types;
ACCESSOR_IMPL_2(base_type, is_virtual, bool, is_virtual_base)

ostream &cpp::codeprovider::types::operator<<(ostream &os, const base_type &b)
{
    if (b.is_virtual_base)
        os << "virtual ";
    switch (b.access)
    {
    case access_levels::default_access:
        break;
    case access_levels::private_access:
        os << "private ";
        break;
    case access_levels::protected_access:
        os << "protected ";
        break;
    case access_levels::public_access:
        os << "public ";
        break;
    }

    if (b.udt)
        os << b.udt->get_name();
    else
        os << b.parameter->get_name();

    return os;
}
