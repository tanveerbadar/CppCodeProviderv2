#ifndef VARIABLE_DECLARATION_HEADER
#define VARIABLE_DECLARATION_HEADER

#pragma once

#include "common.h"
#include "declarator.h"
#include "declarator_specifier.h"

namespace cpp
{
namespace codeprovider
{
namespace declarations
{
class variable_declaration : public declaration
{
	declarator var_decl;

public:
	variable_declaration(const declarator_specifier &);
	variable_declaration(const variable_declaration &) = default;

	const declarations::declarator &var_declarator() const;
	declarations::declarator &var_declarator();

	std::unique_ptr<namespaces::namespace_scope_entity> clone() const override;

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
};
} // namespace declarations
} // namespace codeprovider
} // namespace cpp

#endif // !VARIABLE_DECLARATION_HEADER