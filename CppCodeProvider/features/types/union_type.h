#ifndef UNION_HEADER
#define UNION_HEADER

#pragma once

#include "access_levels.h"
#include "common.h"
#include "custom_type.h"
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp::codeprovider::types
{
    using namespace internal;

    class union_type : public type, public namespaces::namespace_scope_entity
    {
        custom_type impl;
    public:
        explicit union_type(const std::string &);

        std::ostream &write_declaration(std::ostream &) const override;
        std::ostream &write_definition(std::ostream &) const override;
        std::ostream &write_forward_declaration(std::ostream &) const override;
        std::unique_ptr<type> clone() const override;

        member_function_list &member_functions();
        member_field_list &member_fields();
        const member_field_list &member_fields() const;
        template_parameter_list &template_parameters();
        friend_functions_list &friend_functions();
        friend_types_list &friend_types();
        ACCESSOR_DECLARATION(union_type, container, std::shared_ptr<nested_type>)
    };
}

#endif