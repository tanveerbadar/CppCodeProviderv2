#ifndef MEMBER_FUNCTION_HEADER
#define MEMBER_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../forward_declarations.h"
#include "../types/access_levels.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::functions
{
    typedef std::vector<std::unique_ptr<declarations::variable_declaration>> parameter_list;
	typedef std::vector<std::unique_ptr<types::templates::template_parameter>> template_parameter_list;
	typedef std::vector<statements::catch_clause> catch_list;

	class member_function
	{
		std::unique_ptr<internals::callable> impl;
		const types::user_defined_type* container;
		types::access_levels access;
	public:
		member_function(const std::string&, std::unique_ptr<types::type>, const types::user_defined_type&);
		member_function(const member_function&);
		member_function& operator =(const member_function&);

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
		ACCESSOR_DECLARATION(member_function, accessibility, types::access_levels)
		ACCESSOR_DECLARATION_2(member_function, return_type, const types::type&, std::unique_ptr<types::type>)
		types::type& return_type();
		statements::block_statement& body();
		const statements::block_statement& body() const;
		std::ostream &write_declaration(std::ostream &) const;
		std::ostream &write_definition(std::ostream &) const;
	};
}

#endif // !MEMBER_FUNCTION_HEADER
