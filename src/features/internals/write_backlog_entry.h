#ifndef WRITE_BACKLOG_ENTRY
#define WRITE_BACKLOG_ENTRY

#pragma once

#include <ostream>

namespace cpp
{
namespace codeprovider
{
namespace internals
{
class write_backlog_entry
{
public:
    virtual ~write_backlog_entry() = 0;
    virtual std::ostream &write_definition(std::ostream &) const = 0;
};
} // namespace internals
} // namespace codeprovider
} // namespace cpp

#endif