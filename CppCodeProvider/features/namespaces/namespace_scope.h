#ifndef NAMESPACE_SCOPE_HEADER
#define NAMESPACE_SCOPE_HEADER

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "namespace_scope_entity.h"

namespace cpp::codeprovider::namespaces
{
    class namespace_scope : public namespace_scope_entity
    {
        std::vector<std::unique_ptr<namespace_scope_entity>> contained_entities;
        std::string name;
    public:
        namespace_scope(const std::string& = "");
        namespace_scope(const namespace_scope&);
        namespace_scope& operator=(const namespace_scope&);

        std::vector<std::unique_ptr<namespace_scope_entity>> &entities();
        const std::vector<std::unique_ptr<namespace_scope_entity>> &entities() const;

        std::ostream &write_declaration(std::ostream &) const override;
        std::ostream &write_definition(std::ostream &) const override;
    };

    std::ostream& operator<<(std::ostream&, const namespace_scope&);
} // cpp::codeprovider::namespaces

#endif