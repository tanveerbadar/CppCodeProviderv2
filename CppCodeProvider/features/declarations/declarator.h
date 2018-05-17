#ifndef DECLARATOR_HEADER
#define DECLARATOR_HEADER

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace cpp::codeprovider::expressions
{
	class expression;
}

namespace cpp::codeprovider::declarations
{
	class declarator
	{
		std::unique_ptr<expressions::expression> initializer_exp;
	public:
		declarator() = default;
		declarator(const declarator&);

		std::string name;
		bool	is_constant,
					is_volatile,
					is_lvalue_ref,
					is_rvalue_ref;
		int pointer_level;
		std::vector<int> array_dimensions;

		friend std::ostream& operator <<(std::ostream& os, const declarator&);
	};
}

#endif
