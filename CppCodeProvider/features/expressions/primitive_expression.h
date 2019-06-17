#ifndef PRIMITIVE_EXPRESSION_HEADER
#define PRIMITIVE_EXPRESSION_HEADER

#pragma once

#include "common.h"
#include "expression_types.h"

namespace cpp
{
namespace codeprovider
{
namespace expressions
{
class primitive_expression : public expression
{
    std::string e1;

public:
    primitive_expression(const std::string &);

    const std::string &expr() const;
    expression_type type() const;

    std::unique_ptr<expression> clone() const override;
    void write(std::ostream &) const override;
};

} // namespace expressions

} // namespace codeprovider

} // namespace cpp

#endif