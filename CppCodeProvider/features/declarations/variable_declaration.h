#ifndef VARIABLE_DECLARATION_HEADER
#define VARIABLE_DECLARATION_HEADER

#pragma once

#include "declarator_specific.h"
#include "declarator.h"

namespace cpp::codeprovider::declarations
{
	class variable_declaration
	{
		declarator_specifier var_specifier;
		declarator var_decl;
	public:
		variable_declaration(const declarator_specifier&);

		const declarator_specifier & specifier() const;
		const declarator& declarator() const;
		declarations::declarator& declarator();

		friend std::ostream& operator<<(std::ostream&, const variable_declaration&);
	};
}

#endif // !VARIABLE_DECLARATION_HEADER