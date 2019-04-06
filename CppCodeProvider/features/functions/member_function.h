#ifndef MEMBER_FUNCTION_HEADER
#define MEMBER_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "callable.h"
#include "../types/access_levels.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::functions
{
	using namespace internals;

	enum class ref_qualifier
	{
		none,
		lvalue,
		rvalue
	};

	class member_function
	{
		callable impl;
		std::shared_ptr<types::user_defined_type> container;
		types::access_levels access;
		ref_qualifier qualifier = ref_qualifier::none;
	public:
		member_function(const std::string&, std::shared_ptr<types::type>, std::shared_ptr<types::user_defined_type>);

		parameter_list &parameters();
		const parameter_list &parameters() const;
		template_parameter_list &template_parameters();
		const template_parameter_list &template_parameters() const;
		catch_list &catch_blocks();
		const catch_list &catch_blocks() const;
		ACCESSOR_DECLARATION(member_function, is_inline, bool)
		ACCESSOR_DECLARATION(member_function, is_constexpr, bool)
		ACCESSOR_DECLARATION(member_function, is_virtual, bool)
		ACCESSOR_DECLARATION(member_function, is_abstract, bool)
		ACCESSOR_DECLARATION(member_function, is_override, bool)
		ACCESSOR_DECLARATION(member_function, is_static, bool)
		ACCESSOR_DECLARATION(member_function, is_constant, bool)
		ACCESSOR_DECLARATION(member_function, is_volatile, bool)
		ACCESSOR_DECLARATION(member_function, has_try_block, bool)
		ACCESSOR_DECLARATION(member_function, reference_qualifier, ref_qualifier)
		ACCESSOR_DECLARATION(member_function, accessibility, types::access_levels)
		ACCESSOR_DECLARATION(member_function, return_type, std::shared_ptr<types::type>)
		statements::block_statement& body();
		const statements::block_statement& body() const;
		std::ostream &write_declaration(std::ostream &) const;
		std::ostream &write_definition(std::ostream &) const;
	};
}

#endif // !MEMBER_FUNCTION_HEADER
