#ifndef FORWARD_DECLARATIONS_HEADER
#define FORWARD_DECLARATIONS_HEADER

#pragma once

namespace cpp::codeprovider
{
	namespace expressions
	{
		class expression;
	}

	namespace types
	{
		class type;

		namespace templates
		{
			class template_parameter;
		}

		class user_defined_type;
	}

	namespace declarations
	{
		class variable_declaration;
	}

	namespace statements
	{
		class block_statement;
		class catch_clause;
	}

	namespace functions
	{
		class function;
	}
}

#endif // !FORWARD_DECLARATIONS_HEADER