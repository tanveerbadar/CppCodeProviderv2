#ifndef  CALLABLE_HEADER
#define CALLABLE_HEADER

#pragma once

#include <string>
#include "..\statements\block_statement.h"

namespace cpp::codeprovider
{
	namespace types
	{
		class type_declaration;

		namespace templates
		{
			class template_parameter;
		}
	}

	namespace declarations
	{
		class variable_declaration;
	}

	namespace statements
	{
		class block_statement;
	}

	namespace functions::internals
	{
		struct callable
		{
			statements::block_statement statements;
			std::unique_ptr<types::type_declaration> return_type;
			std::vector<std::unique_ptr<declarations::variable_declaration>> parameter_list;
			std::string name;
			std::vector<std::unique_ptr<types::templates::template_parameter>> template_parameter_list;
			bool is_inline = false;

			callable(const std::string&, std::unique_ptr<types::type_declaration>);
		};
	}
}

#endif // ! CALLABLE_HEADER