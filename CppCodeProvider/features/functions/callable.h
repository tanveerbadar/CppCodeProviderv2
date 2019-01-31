#ifndef  CALLABLE_HEADER
#define CALLABLE_HEADER

#pragma once

#include <string>
#include "../forward_declarations.h"
#include "../statements/block_statement.h"
#include "../statements/try_statement.h"

namespace cpp::codeprovider
{
	namespace functions::internals
	{
		struct callable
		{
			statements::block_statement statements;
			std::unique_ptr<types::type> return_type;
			std::vector<std::unique_ptr<declarations::variable_declaration>> parameter_list;
			std::string name;
			std::vector<std::unique_ptr<types::templates::template_parameter>> template_parameter_list;
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
			std::vector<statements::catch_clause> catch_blocks;

			callable() = default;
			callable(const std::string&, std::unique_ptr<types::type>);
			callable(const callable&);
		};
	}
}

#endif // ! CALLABLE_HEADER