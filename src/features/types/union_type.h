#ifndef UNION_HEADER
#define UNION_HEADER

#pragma once

#include "access_levels.h"
#include "common.h"
#include "custom_type.h"
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp
{
namespace codeprovider
{
namespace types
{
class union_type : public type, public namespaces::namespace_scope_entity
{
    internals::custom_type impl;
    bool final = false;

public:
    explicit union_type(const std::string &);

    std::ostream &write_declaration(std::ostream &) const override;
    std::ostream &write_definition(std::ostream &) const override;
    std::ostream &write_forward_declaration(std::ostream &) const override;
    std::ostream &write_template_parameters(std::ostream &) const;
    std::ostream &write_elaborated_name(std::ostream &) const;
    std::unique_ptr<namespaces::namespace_scope_entity> clone() const override;

    internals::member_field_list &member_fields();
    const internals::member_field_list &member_fields() const;
    internals::template_parameter_list &template_parameters();
    internals::friend_functions_list &friend_functions();
    internals::friend_types_list &friend_types();
    ACCESSOR_DECLARATION(union_type, is_final, bool)
};
} // namespace types
} // namespace codeprovider
} // namespace cpp

#endif