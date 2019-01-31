#ifndef COMMON_FUNCTION_HEADER
#define COMMON_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp::codeprovider::functions
{
	class function : public namespaces::namespace_scope_entity
	{
		std::unique_ptr<internals::callable> impl;
	public:
		function(const std::string&, std::unique_ptr<types::type>);
		function(const function&);
		function& operator=(const function&);
		~function() override;

		std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters();
		const std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters() const;
		std::vector<std::unique_ptr<types::templates::template_parameter>>& template_parameters();
		const std::vector<std::unique_ptr<types::templates::template_parameter>>& template_parameters() const;
		std::vector<statements::catch_clause> &catch_blocks();
		const std::vector<statements::catch_clause> &catch_blocks() const;
		bool is_inline() const;
		function& is_inline(bool);
		bool is_static() const;
		function& is_static(bool);
		bool is_constexpr() const;
		function& is_constexpr(bool);
		bool has_try_block() const;
		function &has_try_block(bool);
		types::type &return_type() const;
		function& return_type(std::unique_ptr<types::type>);
		statements::block_statement& body();
		const statements::block_statement& body() const;
		std::ostream &write_declaration(std::ostream &) const override;
		std::ostream &write_definition(std::ostream &) const override;
	};
}

#endif // !COMMON_FUNCTION_HEADER