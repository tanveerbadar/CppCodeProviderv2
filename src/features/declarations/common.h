#ifndef COMMON_DECLARATION_HEADER
#define COMMON_DECLARATION_HEADER

#pragma once

#include <iostream>
#include <memory>
#include "declarator_specifier.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp
{
namespace codeprovider
{
namespace declarations
{
class declaration : public namespaces::namespace_scope_entity
{
	declarator_specifier var_specifier;

protected:
	declaration(const declarator_specifier &);

public:
	declaration(const declaration &) = default;

	const declarator_specifier &specifier() const;
};
} // namespace declarations
} // namespace codeprovider
} // namespace cpp

#endif // !COMMON_DECLARATION_HEADER