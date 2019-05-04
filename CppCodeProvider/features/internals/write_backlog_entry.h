#ifndef WRITE_BACKLOG_ENTRY
#define WRITE_BACKLOG_ENTRY

#pragma once

#include <ostream>

namespace cpp::codeprovider::internals
{
class write_backlog_entry
{
public:
    virtual ~write_backlog_entry() = 0;
    virtual std::ostream &write_definition(std::ostream &) const = 0;
};
} // namespace cpp::codeprovider::internals

#endif