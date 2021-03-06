#ifndef MEMBER_FUNCTION_HEADER
#define MEMBER_FUNCTION_HEADER

#pragma once

#include "../../utils/dirty_macros.h"
#include "../internals/write_backlog_entry.h"
#include "../types/access_levels.h"
#include "callable.h"
#include <memory>
#include <string>
#include <vector>

namespace cpp
{
namespace codeprovider
{
namespace functions
{
using namespace internals;

enum class ref_qualifier : short
{
	none = 0,
	lvalue = 1,
	rvalue = 2,
};

class member_function : public cpp::codeprovider::internals::write_backlog_entry
{
	callable impl;
	std::shared_ptr<types::user_defined_type> udt;
	types::access_levels access;
	short flags = 0;
	mutable bool inline_definition = false;

	class write_definition_helper;

	friend class write_definition_helper;

public:
	member_function(const std::string &, std::shared_ptr<types::type>, std::shared_ptr<types::user_defined_type>);
	member_function(const member_function &);
	member_function &operator=(const member_function &);

	parameter_list &parameters();
	const parameter_list &parameters() const;
	template_parameter_list &template_parameters();
	const template_parameter_list &template_parameters() const;
	catch_list &catch_blocks();
	const catch_list &catch_blocks() const;
	ACCESSOR_DECLARATION(member_function, is_inline, bool);
	ACCESSOR_DECLARATION(member_function, is_constexpr, bool);
	ACCESSOR_DECLARATION(member_function, is_virtual, bool);
	ACCESSOR_DECLARATION(member_function, is_abstract, bool);
	ACCESSOR_DECLARATION(member_function, is_override, bool);
	ACCESSOR_DECLARATION(member_function, is_static, bool);
	ACCESSOR_DECLARATION(member_function, is_constant, bool);
	ACCESSOR_DECLARATION(member_function, is_volatile, bool);
	ACCESSOR_DECLARATION(member_function, has_try_block, bool);
	ACCESSOR_DECLARATION(member_function, reference_qualifier, ref_qualifier);
	ACCESSOR_DECLARATION(member_function, accessibility, types::access_levels);
	ACCESSOR_DECLARATION(member_function, return_type, std::shared_ptr<types::type>);
	ACCESSOR_DECLARATION(member_function, is_final, bool);
	ACCESSOR_DECLARATION(member_function, has_trailing_return_type, bool);
	ACCESSOR_DECLARATION(member_function, is_var_arg, bool);
	ACCESSOR_DECLARATION(member_function, is_no_except, bool);
	ACCESSOR_DECLARATION(member_function, no_except_expr, utils::copyable_ptr<expressions::expression>);
	ACCESSOR_DECLARATION_2(member_function, name, std::string, const std::string &);
	statements::block_statement &body();
	const statements::block_statement &body() const;
	std::ostream &write_declaration(std::ostream &) const;
	std::ostream &write_definition(std::ostream &) const override;
	std::ostream &write_inline_definition(std::ostream &) const;
};
} // namespace functions
} // namespace codeprovider
} // namespace cpp

#endif // !MEMBER_FUNCTION_HEADER
