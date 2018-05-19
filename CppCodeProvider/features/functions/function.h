#ifndef COMMON_FUNCTION_HEADER
#define COMMON_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "..\forward_declarations.h"

namespace cpp::codeprovider
{
	namespace types
	{
		class type_declaration;
	}

	namespace declarations
	{
		class variable_declaration;
	}

	namespace templates
	{
		class template_parameter;
	}

	namespace statements
	{
		class block_statement;
	}

	namespace functions
	{
		namespace internals
		{
			struct callable;
		}

		class function
		{
			std::unique_ptr<internals::callable> impl;
		public:
			function(std::string);

			std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters();
			std::vector<std::unique_ptr<templates::template_parameter>>& template_parameters();
			bool is_inline() const;
			function& is_inline(bool);
			types::type_declaration& return_type();
			statements::block_statement& body();
		};
	}
}

#endif // !COMMON_FUNCTION_HEADER