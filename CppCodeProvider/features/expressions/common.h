#ifndef COMMON_EXPRESSION_HEADER
#define COMMON_EXPRESSION_HEADER
#pragma once

#include <iostream>

namespace cpp::codeprovider::expressions
{
	class expression
	{
	public:
		virtual void write(std::ostream&) const = 0;
		virtual std::unique_ptr<expression> clone() const = 0;
		virtual ~expression() = 0;
	};

	std::ostream& operator<<(std::ostream& os, const expression& expr);
}

#endif // !COMMON_EXPRESSION_HEADER
