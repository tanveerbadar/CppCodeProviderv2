#ifndef COMMON_STATEMENT_HEADER
#define COMMON_STATEMENT_HEADER

#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace cpp::codeprovider::statements
{
	class statement
	{
	public:
		std::string comment;

		virtual void write(std::ostream&) const = 0;
		virtual std::unique_ptr<statement> clone() const = 0;
		virtual ~statement() = 0;
	};

	typedef std::vector<std::unique_ptr<statement>> statement_list;

	std::ostream& operator <<(std::ostream&, const statement&);
}

#endif // !COMMON_STATEMENT_HEADER
