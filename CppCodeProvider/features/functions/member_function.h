#ifndef MEMBER_FUNCTION_HEADER
#define MEMBER_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace cpp::codeprovider
{
	namespace types
	{
		class type;
		class user_defined_type;
		enum class access_level : int;

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

		class member_function
		{
			std::unique_ptr<internals::callable> impl;
			const types::user_defined_type* container;
			types::access_level access;
		public:
			member_function(const std::string&, std::unique_ptr<types::type>, const types::user_defined_type&);

			std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters();
			std::vector<std::unique_ptr<types::templates::template_parameter>>& template_parameters();
			bool is_inline() const;
			member_function& is_inline(bool);
			bool is_virtual() const;
			member_function& is_virtual(bool);
			bool is_static() const;
			member_function& is_static(bool);
			bool is_constant() const;
			member_function& is_constant(bool);
			bool is_volatile() const;
			member_function& is_volatile(bool);
			types::access_level accessibility() const;
			member_function& accessibility(types::access_level);
			types::type& return_type();
			member_function& return_type(types::type&);
			statements::block_statement& body();

			friend std::ostream& operator<<(std::ostream&, const member_function&);
			friend std::tuple<std::ostream&, std::ostream&> operator<<(std::tuple<std::ostream&, std::ostream&>, const member_function&);
		};
	}
}

#endif // !MEMBER_FUNCTION_HEADER
