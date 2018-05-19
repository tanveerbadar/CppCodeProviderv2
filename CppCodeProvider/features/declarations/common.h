#ifndef COMMON_DECLARATION_HEADER
#define COMMON_DECLARATION_HEADER

#pragma once

#include <iostream>

namespace cpp::codeprovider::declarations
{
	class declaration
	{
	public:
		virtual ~declaration() = 0;
		virtual void write(std::ostream&) = 0;
	};

	std::ostream& operator<<(std::ostream&, const declaration&);
}

#endif // !COMMON_DECLARATION_HEADER