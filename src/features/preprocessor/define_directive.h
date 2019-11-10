#ifndef DEFINE_DIRECTIVE_HEADER
#define DEFINE_DIRECTIVE_HEADER

#pragma once

#include "common.h"
#include <string>
#include <vector>

namespace cpp
{
namespace codeprovider
{
namespace preprocessor
{
class define_directive : public preprocessor_directive
{
    std::vector<std::string> parameters;
    std::string body, name;

public:
    define_directive(const std::string &);
    define_directive(const std::string &, const std::string &);
    define_directive(const std::string &, const std::vector<std::string> &, const std::string &);

    std::ostream &write_declaration(std::ostream &) const override;
    std::ostream &write_definition(std::ostream &) const override;
};
} // namespace preprocessor
} // namespace codeprovider
} // namespace cpp

#endif