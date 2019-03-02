#ifndef PRIMITIVE_TYPE_HEADER
#define PRIMITIVE_TYPE_HEADER

#pragma once

#include "common.h"

namespace cpp::codeprovider::types
{
	class primitive_type : public type
	{
	public:
		primitive_type(const std::string&);
		primitive_type(const primitive_type&) = default;
		
		std::ostream &write_declaration(std::ostream &) const override;
		std::ostream &write_definition(std::ostream &) const override;
		std::unique_ptr<type> clone() const override;
	};
}
#endif // !PRIMITIVE_TYPE_HEADER