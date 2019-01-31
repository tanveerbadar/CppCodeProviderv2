#ifndef COMMON_DECLARATION_HEADER
#define COMMON_DECLARATION_HEADER

#pragma once

#include <iostream>
#include <memory>
#include "../namespaces/namespace_scope_entity.h"

namespace cpp::codeprovider::declarations
{
	class declaration : public namespaces::namespace_scope_entity
	{
	public:
		virtual std::unique_ptr<declaration> clone() const = 0;
	};
}

#endif // !COMMON_DECLARATION_HEADER