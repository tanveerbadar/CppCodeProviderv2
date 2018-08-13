#ifndef TEMPLATE_PARAMETER_HEADER
#define TEMPLATE_PARAMETER_HEADER

#pragma once

#include "common.h"

namespace cpp::codeprovider::types::templates
{
	class template_parameter : public type
	{
	public:
		void write(std::ostream&) const override;
		std::unique_ptr<type> clone() const override;
	};
}

#endif // !TEMPLATE_PARAMETER_HEADER