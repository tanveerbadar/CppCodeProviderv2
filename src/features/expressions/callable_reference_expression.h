#ifndef CALLABLE_REFERENCE_EXPRESSION_HEADER
#define CALLABLE_REFERENCE_EXPRESSION_HEADER

#include "../forward_declarations.h"
#include "common.h"

namespace cpp
{
namespace codeprovider
{
namespace expressions
{
class callable_reference_expression : public expression
{
    std::shared_ptr<functions::function> f_ref;
    std::shared_ptr<functions::member_function> mf_ref;
    std::shared_ptr<lambda_expression> le_ref;

public:
    callable_reference_expression(std::shared_ptr<functions::function>);
    callable_reference_expression(std::shared_ptr<functions::member_function>);
    callable_reference_expression(std::shared_ptr<lambda_expression>);

    std::unique_ptr<expression> clone() const override;
    void write(std::ostream &) const override;
};
} // namespace expression
} // namespace codeprovider
} // namespace cpp
#endif