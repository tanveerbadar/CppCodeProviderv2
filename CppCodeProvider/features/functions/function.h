#ifndef COMMON_FUNCTION_HEADER
#define COMMON_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::functions
{
    typedef std::vector<std::unique_ptr<declarations::variable_declaration>> parameter_list;
	typedef std::vector<std::unique_ptr<types::templates::template_parameter>> template_parameter_list;
	typedef std::vector<statements::catch_clause> catch_list;

	class function : public namespaces::namespace_scope_entity
	{
		std::unique_ptr<internals::callable> impl;
	public:
		function(const std::string&, std::unique_ptr<types::type>);
		function(const function&);
		function& operator=(const function&);
		~function() override;

		parameter_list &parameters();
		const parameter_list &parameters() const;
		template_parameter_list &template_parameters();
		const template_parameter_list &template_parameters() const;
		catch_list &catch_blocks();
		const catch_list &catch_blocks() const;
		ACCESSOR_DECLARATION(function, is_inline, bool);
		ACCESSOR_DECLARATION(function, is_static, bool);
		ACCESSOR_DECLARATION(function, is_constexpr, bool);
		ACCESSOR_DECLARATION(function, has_try_block, bool);
		ACCESSOR_DECLARATION_2(function, return_type, const types::type&, std::unique_ptr<types::type>);
		statements::block_statement& body();
		const statements::block_statement& body() const;
		std::ostream &write_declaration(std::ostream &) const override;
		std::ostream &write_definition(std::ostream &) const override;
	};
}

#endif // !COMMON_FUNCTION_HEADER