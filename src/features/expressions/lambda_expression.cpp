#include "lambda_expression.h"
#include "../../utils/write_helpers.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../functions/callable.h"
#include "../statements/try_statement.h"
#include "../types/template_parameters.h"
#include "unary_expressions.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::functions::internals;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::utils;

ostream &cpp::codeprovider::expressions::operator<<(ostream &os, capture_mode capture)
{
    switch (capture)
    {
    case capture_mode::by_ref:
        os << "&";
        break;
    case capture_mode::by_val:
        os << "=";
        break;
    }
    return os;
}

namespace
{
template <typename T>
void write_vector(std::ostream &os, const std::vector<std::pair<capture_mode, copyable_ptr<T>>> &parameters)
{
    if (parameters.size() > 0)
    {
        if (parameters.size() > 1)
            for (auto i = 0; i < parameters.size() - 1; ++i)
                os << (parameters[i].first == capture_mode::by_ref ? "&" : "") << *parameters[i].second << ", ";
        os << (parameters[parameters.size() - 1].first == capture_mode::by_ref ? "&" : "") << *parameters[parameters.size() - 1].second;
    }
}
} // namespace

parameter_list &lambda_expression::parameters()
{
    return impl.parameters;
}

const parameter_list &lambda_expression::parameters() const
{
    return impl.parameters;
}

capture_list &lambda_expression::captured_variables()
{
    return captures;
}

const capture_list &lambda_expression::captured_variables() const
{
    return captures;
}

block_statement &lambda_expression::body()
{
    return impl.statements;
}

const block_statement &lambda_expression::body() const
{
    return impl.statements;
}

ACCESSOR_IMPL_2(lambda_expression, return_type, shared_ptr<type>, impl.return_type)
ACCESSOR_IMPL_2(lambda_expression, default_capture_mode, capture_mode, default_capture)
ACCESSOR_IMPL_2(lambda_expression, is_mutable, bool, impl.is_mutable)
ACCESSOR_IMPL_2(lambda_expression, is_no_except, bool, impl.is_no_except)
ACCESSOR_IMPL_2(lambda_expression, no_except_expr, copyable_ptr<expression>, impl.no_except_expr)

unique_ptr<expression> lambda_expression::clone() const
{
    return make_unique<lambda_expression>(*this);
}

void lambda_expression::write(ostream &os) const
{
    os << "[";

    if (default_capture != capture_mode::none)
    {
        os << default_capture;
        if (captures.size() > 0)
            os << ", ";
    }
    write_vector(os, captures);
    os << "](";

    write_vector(os, impl.parameters);

    os << ")";

    if(impl.is_no_except)
    {
        if(impl.no_except_expr)
        {
            os << " noexcept(" << *impl.no_except_expr << ")";
        }
        else
            os << " noexcept";
    }

    if (impl.return_type)
        os << " -> " << impl.return_type->get_name();

    if (impl.is_mutable)
        os << " mutable";

    if (impl.statements.statements().empty())
    {
        if (impl.return_type || impl.is_mutable)
            os << endl;
        os << "{}";
    }
    else
        os << endl
           << impl.statements;
}
