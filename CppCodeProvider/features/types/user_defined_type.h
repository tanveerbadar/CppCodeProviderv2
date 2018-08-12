#ifndef USER_DEFINED_TYPE_HEADER
#define USER_DEFINED_TYPE_HEADER

#pragma once

#include <vector>
#include "common.h"
#include "..\functions\member_function.h"
#include "..\declarations\variable_declaration.h"

namespace cpp::codeprovider::types
{
	class user_defined_type : public type
	{
		std::vector<std::unique_ptr<functions::member_function>> functions;
		std::vector<std::unique_ptr<declarations::variable_declaration>> fields;
	public:
		user_defined_type(const std::string&);
		user_defined_type(const user_defined_type&);
		void write(std::ostream&) const override;
		std::unique_ptr<type> clone() const override;
	};
}

#endif // !USER_DEFINED_TYPE_HEADER