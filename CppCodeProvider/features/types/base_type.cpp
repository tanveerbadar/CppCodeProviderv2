#include "base_type.h"
#include "template_parameter.h"
#include <iostream>
#include <string>
#include <memory>
#include "user_defined_type.h"

using namespace std;

namespace cpp::codeprovider::types
{
    bool base_type::is_virtual() const
    {
        return is_virtual_base;
    }

    base_type& base_type::is_virtual(bool flag)
    {
        is_virtual_base = flag;
        return *this;
    }

    ostream& operator<<(ostream& os, const base_type& b)
    {
        if(b.is_virtual_base)
            os << "virtual ";
        switch(b.access)
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
        
        if(b.udt)
            os << b.udt->get_name();
        else
            os << b.parameter->get_name();

        return os;
    }
}
