#ifndef COMMON_FUNCTION_HEADER
#define COMMON_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "callable.h"
#include "../namespaces/namespace_scope_entity.h"
#include "../../utils/dirty_macros.h"

namespace cpp
{
namespace codeprovider
{
namespace functions
{
class function : public namespaces::namespace_scope_entity
{
	internals::callable impl;

public:
	function(const std::string &, std::shared_ptr<types::type>);
	~function() override;
	std::unique_ptr<namespaces::namespace_scope_entity> clone() const override;

	internals::parameter_list &parameters();
	const internals::parameter_list &parameters() const;
	internals::template_parameter_list &template_parameters();
	const internals::template_parameter_list &template_parameters() const;
	internals::catch_list &catch_blocks();
	const internals::catch_list &catch_blocks() const;
	ACCESSOR_DECLARATION(function, is_inline, bool);
	ACCESSOR_DECLARATION(function, is_static, bool);
	ACCESSOR_DECLARATION(function, is_constexpr, bool);
	ACCESSOR_DECLARATION(function, has_try_block, bool);
	ACCESSOR_DECLARATION(function, has_trailing_return_type, bool);
	ACCESSOR_DECLARATION(function, return_type, std::shared_ptr<types::type>);
	ACCESSOR_DECLARATION(function, is_var_arg, bool);
	ACCESSOR_DECLARATION(function, is_no_except, bool);
	ACCESSOR_DECLARATION(function, no_except_expr, utils::copyable_ptr<expressions::expression>);
	ACCESSOR_DECLARATION_2(function, name, std::string, const std::string&);
	statements::block_statement &body();
	const statements::block_statement &body() const;
	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
};
} // namespace functions
} // namespace codeprovider
} // namespace cpp

#endif // !COMMON_FUNCTION_HEADER