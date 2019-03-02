#ifndef NAMESPACE_SCOPE_HEADER
#define NAMESPACE_SCOPE_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "namespace_scope_entity.h"
#include "../../utils/copyable_ptr.h"

namespace cpp::codeprovider::namespaces
{
    typedef std::vector<utils::copyable_ptr<namespace_scope_entity>> entity_list;
    
    class namespace_scope : public namespace_scope_entity
    {
        entity_list contained_entities;
        std::string name;
    public:
        namespace_scope(const std::string& = "");

        entity_list &entities();
        const entity_list &entities() const;

        std::ostream &write_declaration(std::ostream &) const override;
        std::ostream &write_definition(std::ostream &) const override;
    };

    std::ostream& operator<<(std::ostream&, const namespace_scope&);
} // cpp::codeprovider::namespaces

#endif