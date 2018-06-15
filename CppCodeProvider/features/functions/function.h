#ifndef COMMON_FUNCTION_HEADER
#define COMMON_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>

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
			function(const std::string&, std::unique_ptr<types::type_declaration>);

			std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters();
			std::vector<std::unique_ptr<types::templates::template_parameter>>& template_parameters();
			bool is_inline() const;
			function& is_inline(bool);
			types::type_declaration& return_type();
			function& return_type(types::type_declaration&);
			statements::block_statement& body();

			friend std::ostream& operator<<(std::ostream&, const function&);
		};
	}
}

#endif // !COMMON_FUNCTION_HEADER