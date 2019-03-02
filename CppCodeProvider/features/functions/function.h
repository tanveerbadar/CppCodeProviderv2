#ifndef COMMON_FUNCTION_HEADER
#define COMMON_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "callable.h"
#include "../namespaces/namespace_scope_entity.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::functions
{
	using namespace internals;

	class function : public namespaces::namespace_scope_entity
	{
		callable impl;
	public:
		function(const std::string&, std::unique_ptr<types::type>);
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