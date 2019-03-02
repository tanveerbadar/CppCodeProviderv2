#ifndef DECLARATOR_HEADER
#define DECLARATOR_HEADER

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "../forward_declarations.h"

namespace cpp::codeprovider::declarations
{
	class declarator
	{
	public:
		declarator() = default;
		declarator(const declarator&);

		std::string name;
		bool	is_constant = false,
					is_volatile = false,
					is_lvalue_ref = false,
					is_rvalue_ref = false;
		int pointer_level = 0;
		std::vector<int> array_dimensions;
		std::unique_ptr<expressions::expression> initializer_exp;

		friend std::ostream& operator <<(std::ostream& os, const declarator&);
	};
}

#endif
