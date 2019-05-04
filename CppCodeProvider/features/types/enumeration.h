#ifndef ENUMERATION_HEADER
#define ENUMERATION_HEADER

#include <string>
#include "common.h"
#include "custom_type.h"
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::types
{
	using namespace internal;

    class enumeration : public type, public namespaces::namespace_scope_entity
    {
        custom_type impl;
    public:
        explicit enumeration(const std::string&);
 
        member_field_list &enumerators();
        const member_field_list &enumerators() const;
        ACCESSOR_DECLARATION(enumeration, is_scoped_enum, bool)
        ACCESSOR_DECLARATION(enumeration, container, std::shared_ptr<nested_type>)

        std::unique_ptr<type> clone() const override;
        std::ostream &write_declaration(std::ostream &) const override;
        std::ostream &write_definition(std::ostream &) const override;
    };
} // namespace cpp::codeprovider::types
#endif