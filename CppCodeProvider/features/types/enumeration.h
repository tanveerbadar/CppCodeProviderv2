#ifndef ENUMERATION_HEADER
#define ENUMERATION_HEADER

#include <memory>
#include <string>
#include <vector>
#include "common.h"
#include "../forward_declarations.h"
#include "../namespaces/namespace_scope_entity.h"

namespace cpp::codeprovider::types
{
    typedef std::vector<std::pair<std::string, std::unique_ptr<expressions::expression>>> enumerator_list;

    class enumeration : public type, public namespaces::namespace_scope_entity
    {
        enumerator_list members;
        bool is_scoped;
    public:
        explicit enumeration(const std::string&);
        enumeration(const enumeration&);
        enumeration& operator=(const enumeration&);
        enumerator_list &enumerators();
        const enumerator_list &enumerators() const;

        bool is_scoped_enum() const;
        enumeration& is_scoped_enum(bool);

        std::unique_ptr<type> clone() const override;
        std::ostream &write_declaration(std::ostream &) const override;
        std::ostream &write_definition(std::ostream &) const override;
    };
} // namespace cpp::codeprovider::types
#endif