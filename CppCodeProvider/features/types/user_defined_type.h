#ifndef USER_DEFINED_TYPE_HEADER
#define USER_DEFINED_TYPE_HEADER

#pragma once

#include <vector>
#include "base_type.h"
#include "common.h"
#include "template_parameter.h"
#include "../declarations/variable_declaration.h"
#include "../functions/member_function.h"

namespace cpp::codeprovider::types
{
	class user_defined_type : public type
	{
		bool is_class = true;
		std::vector<std::unique_ptr<functions::member_function>> functions;
		std::vector<std::unique_ptr<std::tuple<access_levels, declarations::variable_declaration>>> fields;
		std::vector<base_type> base_types;
		std::vector<std::unique_ptr<templates::template_parameter>> template_parameter_list;
	public:
		user_defined_type(const std::string&);
		user_defined_type(const user_defined_type&);
		user_defined_type& operator=(const user_defined_type&);

		void write(std::ostream&) const override;
		std::unique_ptr<type> clone() const override;

		std::vector<std::unique_ptr<functions::member_function>>& member_functions();
		std::vector<std::unique_ptr<declarations::variable_declaration>>& member_fields();
		std::vector<base_type>& bases();
		std::vector<std::unique_ptr<templates::template_parameter>>& template_parameters();
	};
}

#endif // !USER_DEFINED_TYPE_HEADER