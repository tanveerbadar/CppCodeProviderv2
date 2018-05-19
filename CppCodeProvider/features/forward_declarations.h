#ifndef FORWARD_DECLARATIONS_HEADER
#define FORWARD_DECLARATIONS_HEADER

#pragma once
#include <string>

namespace cpp::codeprovider
{
	namespace types
	{
		class type_declaration
		{
		public:
			std::string name;
		};
	}

	namespace expressions
	{
		class expression;
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
		class function;
	}
}

#endif // !FORWARD_DECLARATIONS_HEADER