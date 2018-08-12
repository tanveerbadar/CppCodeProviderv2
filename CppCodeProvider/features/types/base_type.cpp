#include "base_type.h"
#include "template_parameter.h"
#include <iostream>
#include <string>
#include <memory>
#include "user_defined_type.h"

using namespace std;

namespace cpp::codeprovider::types
{
    ostream& operator<<(ostream& os, const base_type& b)
    {
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
