#ifndef BLOCK_STATEMENT_HEADER
#define BLOCK_STATEMENT_HEADER

#pragma once
#include "common.h"
#include <vector>
#include <memory>

namespace cpp::codeprovider::statements
{
	class block_statement : public statement
	{
		std::vector<std::unique_ptr<statement>> collection;
	public:
		std::vector<std::unique_ptr<statement>>& statements();
		std::vector<std::unique_ptr<statement>>& statements() const;
		block_statement();
		block_statement(const block_statement&);

		std::unique_ptr<statement> clone() const override;
		void write(std::ostream&) const override;
	};
}

#endif // !BLOCK_STATEMENT_HEADER