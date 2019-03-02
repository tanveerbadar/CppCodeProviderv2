#ifndef COMMON_DECLARATION_HEADER
#define COMMON_DECLARATION_HEADER

#pragma once

#include <iostream>
#include <memory>
#include "declarator_specifier.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp::codeprovider::declarations
{
	class declaration : public namespaces::namespace_scope_entity
	{
		declarator_specifier var_specifier;
	protected:
		declaration(const declarator_specifier &);
	public:
		declaration(const declaration&) = default;

		virtual std::unique_ptr<declaration> clone() const = 0;
		const declarator_specifier &specifier() const;
	};
} // namespace cpp::codeprovider::declarations

#endif // !COMMON_DECLARATION_HEADER