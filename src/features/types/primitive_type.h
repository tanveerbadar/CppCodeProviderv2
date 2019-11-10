#ifndef PRIMITIVE_TYPE_HEADER
#define PRIMITIVE_TYPE_HEADER

#pragma once

#include "common.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp
{
namespace codeprovider
{
namespace types
{
class primitive_type : public type, namespaces::namespace_scope_entity
{
public:
	primitive_type(const std::string &);

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
	std::ostream &write_forward_declaration(std::ostream &) const override;
	std::unique_ptr<namespaces::namespace_scope_entity> clone() const override;
};
} // namespace types
} // namespace codeprovider
} // namespace cpp

#endif // !PRIMITIVE_TYPE_HEADER