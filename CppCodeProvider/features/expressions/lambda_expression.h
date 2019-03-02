#ifndef LAMBDA_EXPRESSION_HEADER
#define LAMBDA_EXPRESSION_HEADER

#pragma once

#include <vector>
#include "common.h"
#include "../functions/callable.h"
#include "../../utils/dirty_macros.h"

namespace cpp::codeprovider::expressions
{
    enum class capture_mode : char
    {
        none,
        by_val,
        by_ref,
    };

    std::ostream& operator<<(std::ostream&, capture_mode);

    typedef std::vector<std::pair<capture_mode, utils::copyable_ptr<expression>>> capture_list;

    class lambda_expression : public expression
    {
        functions::internals::callable impl;
        capture_mode default_capture = capture_mode::none;
        capture_list captures;
      public:
        lambda_expression() = default;

        functions::internals::parameter_list &parameters();
        const functions::internals::parameter_list &parameters() const;
        capture_list &captured_variables();
        const capture_list &captured_variables() const;
        statements::block_statement& body();
        const statements::block_statement& body() const;
        ACCESSOR_DECLARATION_2(lambda_expression, return_type, const utils::copyable_ptr<types::type>&, std::unique_ptr<types::type>)
        ACCESSOR_DECLARATION(lambda_expression, default_capture_mode, capture_mode)
        ACCESSOR_DECLARATION(lambda_expression, is_mutable, bool)

        std::unique_ptr<expression> clone() const override;
        void write(std::ostream &) const override;
    };
}

#endif