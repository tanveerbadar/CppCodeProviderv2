#include "function.h"
#include "../../formatters/formatter_settings.h"
#include "../../utils/write_helpers.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/template_parameters.h"
#include "callable.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::functions::internals;
using namespace cpp::codeprovider::namespaces;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::utils;
using namespace cpp::codeprovider::formatting;

function::function(const string &n, shared_ptr<type> returns)
	: impl(n, returns)
{
}

function::~function()
{
}

unique_ptr<namespace_scope_entity> function::clone() const
{
	return make_unique<function>(*this);
}

parameter_list &function::parameters()
{
	return impl.parameters;
}

const parameter_list &function::parameters() const
{
	return impl.parameters;
}

template_parameter_list &function::template_parameters()
{
	return impl.template_parameters;
}

const template_parameter_list &function::template_parameters() const
{
	return impl.template_parameters;
}

catch_list &function::catch_blocks()
{
	return impl.catch_blocks;
}

const catch_list &function::catch_blocks() const
{
	return impl.catch_blocks;
}

ACCESSOR_IMPL_2(function, is_inline, bool, impl.is_inline)
ACCESSOR_IMPL_2(function, has_try_block, bool, impl.has_function_try_block)
ACCESSOR_IMPL_2(function, is_constexpr, bool, impl.is_const_expr)
ACCESSOR_IMPL_2(function, is_static, bool, impl.is_static)
ACCESSOR_IMPL_2(function, return_type, shared_ptr<type>, impl.return_type)
ACCESSOR_IMPL_2(function, has_trailing_return_type, bool, impl.has_trailing_return_type)
ACCESSOR_IMPL_2(function, is_var_arg, bool, impl.is_var_arg)
ACCESSOR_IMPL_2(function, is_no_except, bool, impl.is_no_except)
ACCESSOR_IMPL_2(function, no_except_expr, copyable_ptr<expression>, impl.no_except_expr)
ACCESSOR_IMPL_3(function, name, string, impl.name, const string&)

block_statement &function::body()
{
	return impl.statements;
}

const block_statement &function::body() const
{
	return impl.statements;
}

ostream &function::write_declaration(ostream &os) const
{
	write_template_parameters(os, impl.template_parameters);

	if (impl.is_const_expr)
		os << "constexpr ";
	if (impl.is_inline)
		os << "inline ";
	if (impl.is_static)
		os << "static ";

	if (impl.has_trailing_return_type)
		os << "auto";
	else
		os << impl.return_type->get_name();

	os << " " << impl.name << "(";

	write_vector(os, impl.parameters);

	if (impl.is_var_arg)
	{
		if (impl.parameters.empty())
			os << "...";
		else
		{
			os << ", ...";
		}
	}

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

	if (impl.has_trailing_return_type)
		os << " -> " << impl.return_type->get_name();

	os << ";" << endl;

	return os;
}

ostream &function::write_definition(ostream &os) const
{
	write_template_parameters(os, impl.template_parameters);

	if (impl.is_const_expr)
		os << "constexpr ";
	if (impl.is_inline)
		os << "inline ";
	if (impl.is_static)
		os << "static ";

	if (impl.has_trailing_return_type)
		os << "auto";
	else
		os << impl.return_type->get_name();

	os << " " << impl.name << "(";

	write_vector(os, impl.parameters);

	if (impl.is_var_arg)
	{
		if (impl.parameters.empty())
			os << "...";
		else
		{
			os << ", ...";
		}
	}

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

	if (impl.has_trailing_return_type)
		os << " -> " << impl.return_type->get_name() << endl;
	else
		os << endl;

	auto indent = formatter_settings::settings.get_indent_string();

	if (impl.has_function_try_block)
		os << indent << "try" << endl;

	os << impl.statements;

	if (impl.has_function_try_block)
		write_vector(os, impl.catch_blocks);

	return os;
}