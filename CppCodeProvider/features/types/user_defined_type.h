#ifndef USER_DEFINED_TYPE_HEADER
#define USER_DEFINED_TYPE_HEADER

#pragma once

#include <vector>
#include "base_type.h"
#include "common.h"
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp::codeprovider::types
{
	typedef std::vector<base_type> base_list;
	typedef std::vector<std::pair<access_levels, std::unique_ptr<declarations::declaration>>> member_field_list;
	typedef std::vector<std::unique_ptr<templates::template_parameter>> template_parameter_list;
	typedef std::vector<functions::member_function> member_function_list;

	class user_defined_type : public type, public namespaces::namespace_scope_entity
	{
		bool is_class = true;
		member_function_list functions;
		member_field_list fields;
		base_list base_types;
		template_parameter_list template_params;
	public:
		user_defined_type(const std::string&);
		user_defined_type(const user_defined_type&);
		user_defined_type& operator=(const user_defined_type&);

		std::ostream &write_declaration(std::ostream &) const override;
		std::ostream &write_definition(std::ostream &) const override;
		std::unique_ptr<type> clone() const override;

		member_function_list& member_functions();
		member_field_list &member_fields();
		base_list& bases();
		template_parameter_list& template_parameters();
	};
}

#endif // !USER_DEFINED_TYPE_HEADER