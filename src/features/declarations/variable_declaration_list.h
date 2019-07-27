#ifndef VARIABLE_DECLARATION_LIST_HEADER
#define VARIABLE_DECLARATION_LIST_HEADER

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
class variable_declaration_list : public declaration
{
	std::vector<declarator> var_decls;

public:
	variable_declaration_list(const declarator_specifier &);

	std::vector<declarator> &declarations();
	const std::vector<declarator> &declarations() const;

	std::unique_ptr<namespaces::namespace_scope_entity> clone() const override;
	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
};
} // namespace declarations
} // namespace codeprovider
} // namespace cpp

#endif // !VARIABLE_DECLARATION_LIST_HEADER