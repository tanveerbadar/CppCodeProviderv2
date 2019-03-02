#ifndef CUSTOM_TYPE_HEADER
#define CUSTOM_TYPE_HEADER

#pragma once

#include <memory>
#include <vector>
#include "../forward_declarations.h"

namespace cpp::codeprovider::types::internal
{
    enum class type_key
    {
        enum_type,
        struct_type,
        class_type,
        union_type
    };

    std::ostream& operator<<(std::ostream&, type_key);

    typedef std::vector<base_type> base_list;
    typedef std::vector<std::pair<access_levels, std::unique_ptr<declarations::declaration>>> member_field_list;
    typedef std::vector<std::unique_ptr<templates::template_parameter>> template_parameter_list;
    typedef std::vector<functions::member_function> member_function_list;

    struct custom_type
    {
        type_key key;
        member_function_list functions;
        member_field_list fields;
        base_list base_types;
        template_parameter_list template_params;
        bool is_scoped_enum = false;

        custom_type(type_key);
        custom_type(const custom_type&);
        custom_type& operator=(const custom_type&);

        bool is_class() const;
    };
}

#endif