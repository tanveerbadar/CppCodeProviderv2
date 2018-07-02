#ifndef DECLARATOR_SPECIFIER_HEADER
#define DECLARATOR_SPECIFIER_HEADER
#pragma once

#include <iostream>
#include <string>

namespace cpp::codeprovider::types
{
	class type
	{
	public:
		std::string name;
	};
}

namespace cpp::codeprovider::declarations
{
	class declarator_specifier
	{
		const types::type* type;
	public:
		declarator_specifier(const types::type&);

		bool	is_static = false,
					is_constant = false,
					is_volatile = false,
					is_auto = false,
					is_extern = false;

		const types::type& get_type() const
		{
			return *type;
		}
	};

	std::ostream& operator<<(std::ostream&, const declarator_specifier&);
}

#endif
