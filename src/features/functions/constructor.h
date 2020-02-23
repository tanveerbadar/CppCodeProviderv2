#ifndef CONSTRUCTOR_HEADER
#define CONSTRUCTOR_HEADER

#include "../../utils/dirty_macros.h"
#include "callable.h"
#include <memory>
#include <utility>

namespace cpp
{
namespace codeprovider
{
namespace functions
{
typedef std::vector<std::pair<std::string, utils::copyable_ptr<expressions::expression>>> initializer_list;

class constructor
{
	internals::callable impl;
	std::shared_ptr<types::user_defined_type> udt;
	types::access_levels access;
	functions::initializer_list init_list;
	mutable bool inline_definition = false;

	class write_definition_helper;

	friend class write_definition_helper;

public:
	constructor(std::shared_ptr<types::user_defined_type>);

	initializer_list &initializers();
	const initializer_list &initializers() const;
	statements::block_statement &body();
	const statements::block_statement &body() const;
	internals::parameter_list &parameters();
	const internals::parameter_list &parameters() const;
	internals::template_parameter_list &template_parameters();
	const internals::template_parameter_list &template_parameters() const;
	internals::catch_list &catch_blocks();
	const internals::catch_list &catch_blocks() const;
	ACCESSOR_DECLARATION(constructor, is_inline, bool);
	ACCESSOR_DECLARATION(constructor, is_constexpr, bool);
	ACCESSOR_DECLARATION(constructor, has_try_block, bool);
	ACCESSOR_DECLARATION(constructor, accessibility, types::access_levels);
	ACCESSOR_DECLARATION(constructor, is_no_except, bool);
	ACCESSOR_DECLARATION(constructor, no_except_expr, utils::copyable_ptr<expressions::expression>);

	std::ostream &write_declaration(std::ostream &) const;
	std::ostream &write_definition(std::ostream &) const;
	std::ostream &write_inline_definition(std::ostream &) const;
};
} // namespace functions
} // namespace codeprovider
} // namespace cpp

#endif