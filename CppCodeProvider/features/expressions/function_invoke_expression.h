#ifndef FUNCTION_INVOKE_EXPRESSION
#define FUNCTION_INVOKE_EXPRESSION

#pragma once

#include <vector>
#include "common.h"
#include "../forward_declarations.h"
#include "../../utils/copyable_ptr.h"

namespace cpp
{
namespace codeprovider
{
namespace expressions
{
class function_invoke_expression : public expression
{
    utils::copyable_ptr<expression> target;
    std::vector<utils::copyable_ptr<expression>> arguments;

public:
    std::unique_ptr<expression> clone() const override;
    void write(std::ostream &) const override;
};
} // namespace expressions

} // namespace codeprovider

} // namespace cpp

#endif