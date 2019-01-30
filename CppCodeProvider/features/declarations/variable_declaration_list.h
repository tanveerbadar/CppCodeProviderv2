#ifndef VARIABLE_DECLARATION_LIST_HEADER
#define VARIABLE_DECLARATION_LIST_HEADER

#pragma once

#include "common.h"
#include "declarator.h"
#include "declarator_specifier.h"

namespace cpp::codeprovider::declarations
{
	class variable_declaration_list : public declaration
	{
		declarator_specifier var_specifier;
		std::vector<declarator> var_decls;
	public:
		variable_declaration_list(const declarator_specifier&);

		const declarator_specifier & specifier() const;
		std::vector<declarator>& declarations();
		const std::vector<declarator>& declarations() const;

		std::unique_ptr<declaration> clone() const override;
		void write(std::ostream&) const override;

		friend std::ostream& operator<<(std::ostream&, const variable_declaration_list&);
	};
}

#endif // !VARIABLE_DECLARATION_LIST_HEADER