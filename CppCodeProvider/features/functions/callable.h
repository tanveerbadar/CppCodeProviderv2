#ifndef  CALLABLE_HEADER
#define CALLABLE_HEADER

#pragma once

#include <string>
#include "..\forward_declarations.h"
#include "..\statements\block_statement.h"

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

			callable(const std::string&, std::unique_ptr<types::type>);
			callable(const callable&);
		};
	}
}

#endif // ! CALLABLE_HEADER