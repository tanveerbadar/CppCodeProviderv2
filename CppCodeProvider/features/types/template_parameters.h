#ifndef TEMPLATE_PARAMETER_HEADER
#define TEMPLATE_PARAMETER_HEADER

#pragma once

#include "common.h"

namespace cpp
{
namespace codeprovider
{
namespace types
{
namespace templates
{
class template_parameter : public type
{
public:
	template_parameter(const std::string &);

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
	std::ostream &write_forward_declaration(std::ostream &) const override final;
	std::unique_ptr<type> clone() const override;
};

class non_type_template_parameter : public template_parameter
{
	std::string p;

public:
	non_type_template_parameter(const std::string &, const std::string &);

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
	std::unique_ptr<type> clone() const override;
};

class template_template_parameter : public template_parameter
{
	int arguments;

public:
	template_template_parameter(const std::string &, int);

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
	std::unique_ptr<type> clone() const override;
};
} // namespace templates
} // namespace types
} // namespace codeprovider
} // namespace cpp

#endif // !TEMPLATE_PARAMETER_HEADER