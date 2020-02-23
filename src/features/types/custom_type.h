#ifndef CUSTOM_TYPE_HEADER
#define CUSTOM_TYPE_HEADER

#pragma once

#include <memory>
#include <vector>
#include "../forward_declarations.h"
#include "../../utils/copyable_ptr.h"

namespace cpp
{
namespace codeprovider
{
namespace types
{
namespace internals
{
enum class type_key
{
    enum_type,
    struct_type,
    class_type,
    union_type
};

std::ostream &operator<<(std::ostream &, type_key);

typedef std::vector<base_type> base_list;
typedef std::vector<std::pair<access_levels, utils::copyable_ptr<declarations::declaration>>> member_field_list;
typedef std::vector<utils::copyable_ptr<templates::template_parameter>> template_parameter_list;
typedef std::vector<functions::member_function> member_function_list;
typedef std::vector<std::shared_ptr<type>> friend_types_list;
typedef std::vector<std::shared_ptr<functions::function>> friend_functions_list;
typedef std::vector<functions::constructor> constructor_list;

struct custom_type
{
    type_key key;
    member_function_list functions;
    member_field_list fields;
    base_list base_types;
    template_parameter_list template_params;
    bool is_scoped_enum = false;
    friend_functions_list friend_functions;
    friend_types_list friend_types;
    constructor_list constructors;

    custom_type(type_key);

    bool is_class() const;
};
} // namespace internal
} // namespace types
} // namespace codeprovider
} // namespace cpp

#endif