#include "lambda_expression.h"
#include "unary_expressions.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../functions/callable.h"
#include "../statements/try_statement.h"
#include "../types/template_parameters.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::functions::internals;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::utils;

namespace cpp::codeprovider::expressions
{
    ostream& operator<<(ostream& os, capture_mode capture)
    {
        switch(capture)
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
}

namespace
{
    template<typename T> void write_vector(std::ostream& os, const std::vector<std::pair<capture_mode, std::unique_ptr<T>>>& parameters)
    {
		if(parameters.size() > 0)
		{
			if (parameters.size() > 1)
				for (auto i = 1; i < parameters.size() - 1; ++i)
					os << parameters[i].first << *parameters[i].second << ", ";
			os << parameters[parameters.size() - 1].first << *parameters[parameters.size() - 1].second << std::endl;
		}
   }
}

lambda_expression::lambda_expression(const lambda_expression &other)
    : impl(other.impl), default_capture(other.default_capture)
{
    for(auto& vars: other.captures)
        captures.push_back(make_pair(vars.first, vars.second->clone()));
}

lambda_expression& lambda_expression::operator=(const lambda_expression& other)
{
    if(this != &other)
    {
        capture_list vars;
        for (auto &var : other.captures)
            vars.push_back(make_pair(var.first, var.second->clone()));

        impl = other.impl;
        swap(captures, vars);
        default_capture = other.default_capture;
    }

    return *this;
}

parameter_list& lambda_expression::parameters()
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

block_statement& lambda_expression::body()
{
    return impl.statements;
}

const block_statement& lambda_expression::body() const
{
    return impl.statements;
}

const unique_ptr<type>& lambda_expression::return_type() const
{
    return impl.return_type;
}

lambda_expression& lambda_expression::return_type(unique_ptr<type> t)
{
    impl.return_type = move(t);
    return *this;
}

ACCESSOR_IMPL_2(lambda_expression, default_capture_mode, capture_mode, default_capture)
ACCESSOR_IMPL_2(lambda_expression, is_mutable, bool, impl.is_mutable)

unique_ptr<expression> lambda_expression::clone() const
{
    return make_unique<lambda_expression>(*this);
}

void lambda_expression::write(ostream& os) const
{
    os << "[ ";
    os << default_capture;
    if(captures.size() > 0)
        os << ", ";
    write_vector(os, captures);
    os << "] (";

    write_vector(os, impl.parameters);

    os << ")" << endl;

    if(impl.return_type)
        os << " . " << impl.return_type->get_name() << endl;

    if(impl.is_mutable)
        os << " mutable";

    os << impl.statements;
}
