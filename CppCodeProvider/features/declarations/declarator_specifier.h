#ifndef DECLARATOR_SPECIFIER_HEADER
#define DECLARATOR_SPECIFIER_HEADER
#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "../forward_declarations.h"

namespace cpp::codeprovider::declarations
{
	class declarator_specifier
	{
		std::unique_ptr<types::type> type;
	public:
		declarator_specifier(std::unique_ptr<types::type>);
		declarator_specifier(const declarator_specifier&);

		bool	is_static = false,
					is_constant = false,
					is_volatile = false,
					is_auto = false,
					is_extern = false;

		const types::type& get_type() const;
	};

	std::ostream& operator<<(std::ostream&, const declarator_specifier&);
}

#endif
