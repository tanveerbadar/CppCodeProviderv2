#ifndef COMMON_STATEMENT_HEADER
#define COMMON_STATEMENT_HEADER

#pragma once

#include <iostream>
#include <mediaerr.h>

namespace cpp::codeprovider::statements
{
	struct statement
	{
		virtual void write(std::ostream&) const = 0;
		virtual std::unique_ptr<statement> clone() const = 0;
		virtual ~statement() = 0;
	};
}

#endif // !COMMON_STATEMENT_HEADER
