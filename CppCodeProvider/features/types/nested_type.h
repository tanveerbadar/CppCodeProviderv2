#ifndef NESTED_TYPE_HEADER
#define NESTED_TYPE_HEADER

#pragma once

#include <ostream>
#include <memory>
#include <vector>

namespace cpp::codeprovider::types
{
class nested_type
{
public:
    std::shared_ptr<nested_type> container;
    std::vector<const nested_type *> get_containers() const;
    virtual std::ostream& write_template_parameters(std::ostream&) const = 0;
    std::ostream& write_qualified_name(std::ostream&) const;
    virtual std::ostream &write_elaborated_name(std::ostream &) const = 0;
    virtual ~nested_type() = 0;
};
} // namespace cpp::codeprovider::types

#endif