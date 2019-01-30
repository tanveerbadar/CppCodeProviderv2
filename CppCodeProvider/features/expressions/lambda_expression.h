#ifndef LAMBDA_EXPRESSION_HEADER
#define LAMBDA_EXPRESSION_HEADER

#pragma once

#include <vector>
#include "common.h"
#include "../forward_declarations.h"

namespace cpp::codeprovider::functions::internals
{
    struct callable;
}

namespace cpp::codeprovider::expressions
{
    class unary_expression;
    enum class capture_mode : char
    {
        none,
        by_val,
        by_ref,
    };

    std::ostream& operator<<(std::ostream&, capture_mode);

    class lambda_expression : public expression
    {
        std::unique_ptr<functions::internals::callable> impl;
        capture_mode default_capture = capture_mode::none;
        std::vector<std::pair<capture_mode, std::unique_ptr<unary_expression>>> captures;
    public:
        lambda_expression() = default;
        lambda_expression(const lambda_expression&);
        lambda_expression& operator=(const lambda_expression&);

        std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters();
        const std::vector<std::unique_ptr<declarations::variable_declaration>>& parameters() const;
        std::vector<std::pair<capture_mode, std::unique_ptr<unary_expression>>>& captured_variables();
        const std::vector<std::pair<capture_mode, std::unique_ptr<unary_expression>>>& captured_variables() const;
        std::unique_ptr<types::type>& return_type() const;
        lambda_expression& return_type(std::unique_ptr<types::type>);
        statements::block_statement& body();
        const statements::block_statement& body() const;
        capture_mode default_capture_mode() const;
        lambda_expression& default_capture_mode(capture_mode);
        bool is_mutable() const;
        lambda_expression& is_mutable(bool);

		std::unique_ptr<expression> clone() const override;
		void write(std::ostream&) const override;
    };
}

#endif