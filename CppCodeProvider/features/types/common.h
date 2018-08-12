#ifndef  TYPES_COMMON_HEADER
#define TYPES_COMMON_HEADER

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace cpp::codeprovider::types
{
	class type
	{
		std::string name;
	protected:
		type(const std::string&);
	public:
		std::string get_name() const;
		virtual void write(std::ostream&) const = 0;
		virtual std::unique_ptr<type> clone() const = 0;
		virtual ~type() = 0;
	};
}

#endif // ! TYPES_COMMON_HEADER
