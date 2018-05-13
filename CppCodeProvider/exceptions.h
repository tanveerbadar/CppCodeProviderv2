#ifndef EXCEPTION_HEADER
#define EXCEPTION_HEADER

#pragma once
#include <exception>

namespace cpp::codeprovider::exceptions
{
	class invalid_expression_type : std::invalid_argument
	{
	public:
		invalid_expression_type(const char* error)
			:invalid_argument(error)
		{
		}
	};
}

#endif // !EXCEPTION_HEADER
