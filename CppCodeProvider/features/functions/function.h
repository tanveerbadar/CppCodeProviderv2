#ifndef COMMON_FUNCTION_HEADER
#define COMMON_FUNCTION_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../forward_declarations.h"

namespace cpp::codeprovider
{
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
			function(const std::string&, std::unique_ptr<types::type>);
			function(const function&);
			function& operator=(const function&);

			std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters();
			const std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters() const;
			std::vector<std::unique_ptr<types::templates::template_parameter>>& template_parameters();
			const std::vector<std::unique_ptr<types::templates::template_parameter>>& template_parameters() const;
			std::vector<statements::catch_clause> &catch_blocks();
			const std::vector<statements::catch_clause> &catch_blocks() const;
			bool is_inline() const;
			function& is_inline(bool);
			bool is_static() const;
			function& is_static(bool);
			bool is_constexpr() const;
			function& is_constexpr(bool);
			bool has_try_block() const;
			function &has_try_block(bool);
			types::type &return_type() const;
			function& return_type(std::unique_ptr<types::type>);
			statements::block_statement& body();
			const statements::block_statement& body() const;

			friend std::ostream& operator<<(std::ostream&, const function&);
		};
	}
}

#endif // !COMMON_FUNCTION_HEADER