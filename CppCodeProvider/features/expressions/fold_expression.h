#ifndef FOLD_EXPRESSION_HEADER
#define FOLD_EXPRESSION_HEADER

#pragma once

#include <memory>
#include "common.h"
#include "expression_types.h"
#include "../../utils/copyable_ptr.h"

namespace cpp::codeprovider::expressions
{
    class fold_expression : public expression
    {
        utils::copyable_ptr<expression> e1, e2;
        expression_type e_type, f_type;
    public:
        fold_expression(expression_type, expression_type, std::unique_ptr<expression>, std::unique_ptr<expression>);

        const expression &left() const;
        const expression &right() const;
        expression_type type() const;
        expression_type fold_type() const;

        std::unique_ptr<expression> clone() const override;
        void write(std::ostream &) const override;
    };
}

#endif