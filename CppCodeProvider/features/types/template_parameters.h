#ifndef TEMPLATE_PARAMETER_HEADER
#define TEMPLATE_PARAMETER_HEADER

#pragma once

#include "common.h"
#include "../namespaces/namespace_scope_entity.h"
#include "../../utils/dirty_macros.h"

namespace cpp
{
namespace codeprovider
{
namespace types
{
namespace templates
{
class template_parameter : public type, protected namespaces::namespace_scope_entity
{
	bool pack;
public:
	template_parameter(const std::string &);

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
	std::ostream &write_forward_declaration(std::ostream &) const override final;
	std::unique_ptr<namespaces::namespace_scope_entity> clone() const override;

	ACCESSOR_DECLARATION(template_parameter, is_parameter_pack, bool)
};

class non_type_template_parameter : public template_parameter
{
	std::string p;

public:
	non_type_template_parameter(const std::string &, const std::string &);

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
	std::unique_ptr<namespaces::namespace_scope_entity> clone() const override;
};

class template_template_parameter : public template_parameter
{
	int arguments;

public:
	template_template_parameter(const std::string &, int);

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
	std::unique_ptr<namespaces::namespace_scope_entity> clone() const override;
};
} // namespace templates
} // namespace types
} // namespace codeprovider
} // namespace cpp

#endif // !TEMPLATE_PARAMETER_HEADER