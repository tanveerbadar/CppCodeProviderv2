#ifndef VARIABLE_DECLARATION_HEADER
#define VARIABLE_DECLARATION_HEADER

#pragma once

#include "common.h"
#include "declarator_specifier.h"
#include "declarator.h"

namespace cpp::codeprovider::declarations
{
	class variable_declaration : public declaration
	{
		declarator_specifier var_specifier;
		declarator var_decl;
	public:
		variable_declaration(const declarator_specifier&);
		variable_declaration(const variable_declaration&) = default;

		const declarator_specifier & specifier() const;
		const declarations::declarator& var_declarator() const;
		declarations::declarator& var_declarator();

		std::unique_ptr<declaration> clone() const override;
		void write(std::ostream&) override;

		friend std::ostream& operator<<(std::ostream&, const variable_declaration&);
	};
}

#endif // !VARIABLE_DECLARATION_HEADER