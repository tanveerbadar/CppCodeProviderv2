#ifndef DECLARATOR_SPECIFIER_HEADER
#define DECLARATOR_SPECIFIER_HEADER
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include "../forward_declarations.h"

namespace cpp
{
namespace codeprovider
{
namespace declarations
{

class declarator_specifier
{
	std::shared_ptr<types::type> type;

public:
	declarator_specifier(std::shared_ptr<types::type>);

	bool is_static = false,
		 is_constant = false,
		 is_volatile = false,
		 is_auto = false,
		 is_extern = false;

	std::shared_ptr<types::type> get_type() const;
};

std::ostream &operator<<(std::ostream &, const declarator_specifier &);
} // namespace declarations
} // namespace codeprovider
} // namespace cpp

#endif
