#ifndef USER_DEFINED_TYPE_HEADER
#define USER_DEFINED_TYPE_HEADER

#pragma once

#include "base_type.h"
#include "common.h"
#include "custom_type.h"
#include "nested_type.h"
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::types
{
	using namespace internal;

	class user_defined_type : public type, public namespaces::namespace_scope_entity, public nested_type
	{
		custom_type impl;
	public:
		user_defined_type(const std::string&);

		std::ostream &write_declaration(std::ostream &) const override;
		std::ostream &write_definition(std::ostream &) const override;
		std::ostream &write_forward_declaration(std::ostream &) const override;
		std::unique_ptr<type> clone() const override;

		member_function_list& member_functions();
		member_field_list &member_fields();
		base_list& bases();
		template_parameter_list& template_parameters();
		ACCESSOR_DECLARATION(user_defined_type, container, std::shared_ptr<nested_type>)
	};
}

#endif // !USER_DEFINED_TYPE_HEADER