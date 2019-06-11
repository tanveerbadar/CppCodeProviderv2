#ifndef BLOCK_STATEMENT_HEADER
#define BLOCK_STATEMENT_HEADER

#pragma once

#include "common.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp
{
namespace codeprovider
{
namespace statements
{
class block_statement : public namespaces::namespace_scope_entity
{
	statement_list collection;

public:
	block_statement() = default;
	block_statement(const block_statement &);

	block_statement &operator=(const block_statement &);

	statement_list &statements();
	const statement_list &statements() const;

	std::ostream &write_declaration(std::ostream &) const override;
	std::ostream &write_definition(std::ostream &) const override;
};

std::ostream &operator<<(std::ostream &, const block_statement &);
} // namespace statements
} // namespace codeprovider
} // namespace cpp

#endif // !BLOCK_STATEMENT_HEADER