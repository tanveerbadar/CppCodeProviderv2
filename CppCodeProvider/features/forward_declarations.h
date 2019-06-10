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
		enum class access_levels;
		class type;

		namespace templates
		{
			class template_parameter;
		}

		class union_type;
		class user_defined_type;
		class base_type;
	}

	namespace declarations
	{
		class declaration;
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
		class member_function;

		namespace internals
		{
			struct callable;
		}
	}
}

#endif // !FORWARD_DECLARATIONS_HEADER