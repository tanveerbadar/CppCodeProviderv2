#ifndef COMMON_STATEMENT_HEADER
#define COMMON_STATEMENT_HEADER

#pragma once

#include <iostream>
#include <vector>
#include <memory>

namespace cpp::codeprovider::statements
{
	struct statement
	{
	public:
		std::string comment;

		virtual void write(std::ostream&) const = 0;
		virtual std::unique_ptr<statement> clone() const = 0;
		virtual ~statement() = 0;
	};

	std::ostream& operator <<(std::ostream& os, const statement& expr);
}

#endif // !COMMON_STATEMENT_HEADER
