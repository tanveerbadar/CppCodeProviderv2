#ifndef INCLUDE_DIRECTIVE_HEADER
#define INCLUDE_DIRECTIVE_HEADER

#pragma once

#include "common.h"
#include <string>

namespace cpp
{
namespace codeprovider
{
namespace preprocessor
{
class include_directive : public preprocessor_directive
{
    std::string header;
    bool is_system;

public:
    include_directive(const std::string &, bool);

    std::ostream &write_declaration(std::ostream &) const override;
    std::ostream &write_definition(std::ostream &) const override;
};
} // namespace preprocessor
} // namespace codeprovider
} // namespace cpp

#endif