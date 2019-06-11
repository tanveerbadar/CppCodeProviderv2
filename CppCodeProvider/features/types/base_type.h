#ifndef BASE_TYPE_HEADER
#define BASE_TYPE_HEADER

#pragma once

#include <memory>
#include "access_levels.h"
#include "../../utils/dirty_macros.h"

namespace cpp
{
namespace codeprovider
{
namespace types
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
    bool is_virtual_base = false;

public:
    base_type(access_levels, std::shared_ptr<user_defined_type>);
    base_type(access_levels, std::shared_ptr<templates::template_parameter>);

    ACCESSOR_DECLARATION(base_type, is_virtual, bool)

    friend std::ostream &operator<<(std::ostream &, const base_type &);
};
} // namespace types
} // namespace codeprovider
} // namespace cpp

#endif // !BASE_TYPE_HEADER