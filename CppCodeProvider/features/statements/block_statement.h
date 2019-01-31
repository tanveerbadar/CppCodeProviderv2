#ifndef BLOCK_STATEMENT_HEADER
#define BLOCK_STATEMENT_HEADER

#pragma once

#include "common.h"

namespace cpp::codeprovider::statements
{
	class block_statement
	{
		std::vector<std::unique_ptr<statement>> collection;
	public:
		block_statement() = default;
		block_statement(const block_statement&);

		block_statement& operator=(const block_statement&);

		std::vector<std::unique_ptr<statement>>& statements();
		const std::vector<std::unique_ptr<statement>>& statements() const;
	};

	std::ostream& operator<<(std::ostream&, const block_statement&);
}

#endif // !BLOCK_STATEMENT_HEADER