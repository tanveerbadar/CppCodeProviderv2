#ifndef NAMESPACE_SCOPE_ENTITY_HEADER
#define NAMESPACE_SCOPE_ENTITY_HEADER

#pragma once

#include <ostream>

namespace cpp
{
namespace codeprovider
{
namespace namespaces
{
class namespace_scope_entity
{
public:
  virtual std::ostream &write_declaration(std::ostream &) const = 0;
  virtual std::ostream &write_definition(std::ostream &) const = 0;
  virtual ~namespace_scope_entity() = 0;
};
} // namespace namespaces
} // namespace codeprovider
} // namespace cpp
#endif