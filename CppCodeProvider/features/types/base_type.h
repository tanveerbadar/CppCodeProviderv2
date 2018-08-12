#ifndef BASE_TYPE_HEADER
#define BASE_TYPE_HEADER

#pragma once

#include "access_levels.h"
#include <memory>

namespace cpp::codeprovider::types
{
    class user_defined_type;

    namespace templates
    {
        class template_parameter;
    }

    class base_type
    {
        access_levels access;
        std::shared_ptr<user_defined_type> udt;
        std::shared_ptr<templates::template_parameter> parameter;
    public:
        base_type(access_levels, std::shared_ptr<user_defined_type>);
        base_type(access_levels, std::shared_ptr<templates::template_parameter>);
    
        friend std::ostream& operator<<(std::ostream&, const base_type&);
    };
}

#endif // !BASE_TYPE_HEADER