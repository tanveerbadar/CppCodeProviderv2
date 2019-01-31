#ifndef BLOCK_STATEMENT_HEADER
#define BLOCK_STATEMENT_HEADER

#pragma once

#include "common.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp::codeprovider::statements
{
	class block_statement : public namespaces::namespace_scope_entity
	{
		std::vector<std::unique_ptr<statement>> collection;
	public:
		block_statement() = default;
		block_statement(const block_statement&);

		block_statement& operator=(const block_statement&);

		std::vector<std::unique_ptr<statement>>& statements();
		const std::vector<std::unique_ptr<statement>>& statements() const;

		std::ostream &write_declaration(std::ostream &) const override;
		std::ostream &write_definition(std::ostream &) const override;
	};

	std::ostream& operator<<(std::ostream&, const block_statement&);
}

#endif // !BLOCK_STATEMENT_HEADER