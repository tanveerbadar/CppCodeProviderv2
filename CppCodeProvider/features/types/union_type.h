#ifndef UNION_HEADER
#define UNION_HEADER

#pragma once

#include <vector>
#include "access_levels.h"
#include "common.h"
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp::codeprovider::types
{
	typedef std::vector<std::pair<access_levels, std::unique_ptr<declarations::declaration>>> member_field_list;
    typedef std::vector<functions::member_function> member_function_list;
    typedef std::vector<std::unique_ptr<templates::template_parameter>> template_parameter_list;

    class union_type : public type
    {
        member_function_list functions;
        member_field_list fields;
        template_parameter_list template_params;
      public:
        explicit union_type(const std::string&);
        union_type(const union_type&);
        union_type& operator=(const union_type&);
        
        std::ostream &write_declaration(std::ostream &) const override;
        std::ostream &write_definition(std::ostream &) const override;
        std::unique_ptr<type> clone() const override;

        member_function_list &member_functions();
        member_field_list &member_fields();
        const member_field_list &member_fields() const;
        template_parameter_list &template_parameters();
    };
}

#endif