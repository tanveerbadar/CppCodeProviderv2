#ifndef  CALLABLE_HEADER
#define CALLABLE_HEADER

#pragma once

#include <string>
#include "../forward_declarations.h"
#include "../statements/block_statement.h"
#include "../../utils/copyable_ptr.h"

namespace cpp::codeprovider::functions::internals
{
    typedef std::vector<utils::copyable_ptr<declarations::variable_declaration>> parameter_list;
	typedef std::vector<utils::copyable_ptr<types::templates::template_parameter>> template_parameter_list;
	typedef std::vector<statements::catch_clause> catch_list;

	struct callable
	{
		statements::block_statement statements;
		std::shared_ptr<types::type> return_type;
		parameter_list parameters;
		std::string name;
		template_parameter_list template_parameters;
		bool is_inline = false;
		bool is_abstract = false;
		bool is_override = false;
		bool is_virtual = false;
		bool is_constant = false;
		bool is_volatile = false;
		bool is_static = false;
		bool has_trailing_return_type = false;
		bool is_const_expr = false;
		bool is_mutable = false;
		bool has_function_try_block = false;
		catch_list catch_blocks;

		callable() = default;
		callable(const std::string&, std::shared_ptr<types::type>);
	};
}

#endif // ! CALLABLE_HEADER