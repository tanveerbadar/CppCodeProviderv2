#include "lambda_expression.h"
#include "unary_expressions.h"
#include "../declarations/variable_declaration.h"
#include "../functions/callable.h"
#include "../types/common.h"
#include "../types/template_parameter.h"
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

lambda_expression::lambda_expression()
    : impl(make_unique<callable>())
{
}

lambda_expression::lambda_expression(const lambda_expression &other)
    : impl(make_unique<callable>(*other.impl))
{
}

lambda_expression& lambda_expression::operator=(const lambda_expression& other)
{
    if(this != &other)
    {
        impl = make_unique<callable>(*other.impl);
    }

    return *this;
}

vector<unique_ptr<variable_declaration>>& lambda_expression::parameters()
{
    return impl->parameter_list;
}

const vector<unique_ptr<variable_declaration>>& lambda_expression::parameters() const
{
    return impl->parameter_list;
}

vector<pair<capture_mode, unique_ptr<unary_expression>>>& lambda_expression::captured_variables()
{
    return captures;
}

const vector<pair<capture_mode, unique_ptr<unary_expression>>>& lambda_expression::captured_variables() const
{
    return captures;
}

block_statement& lambda_expression::body()
{
    return impl->statements;
}

const block_statement& lambda_expression::body() const
{
    return impl->statements;
}

unique_ptr<type>& lambda_expression::return_type() const
{
    return impl->return_type;
}

lambda_expression& lambda_expression::return_type(unique_ptr<type> t)
{
    impl->return_type = move(t);
    return *this;
}

capture_mode lambda_expression::default_capture_mode() const
{
    return default_capture;
}

lambda_expression& lambda_expression::default_capture_mode(capture_mode mode)
{
    default_capture = mode;
    return *this;
}

bool lambda_expression::is_mutable() const
{
    return impl->is_mutable;
}

lambda_expression& lambda_expression::is_mutable(bool flag)
{
    impl->is_mutable = flag;
    return *this;
}

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

    write_vector(os, impl->parameter_list);

    os << ")" << endl;

    if(impl->return_type)
        os << " -> " << impl->return_type->get_name() << endl;

    if(impl->is_mutable)
        os << " mutable";

    os << impl->statements;
}
