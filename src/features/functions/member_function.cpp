#include "member_function.h"
#include "../../formatters/formatter_settings.h"
#include "../../utils/write_helpers.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/template_parameters.h"
#include "../types/user_defined_type.h"
#include "callable.h"

namespace
{
const short qualifier_mask = 0x03;
const short final_mask = 0x04;
const short container_mask = 0x08;
} // namespace

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::functions::internals;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::utils;
using namespace cpp::codeprovider::formatting;

member_function::member_function(const string &n, shared_ptr<type> returns, shared_ptr<user_defined_type> t)
	: impl(n, returns), udt(t)
{
}

member_function::member_function(const member_function &other)
	: impl(other.impl), flags(other.flags), access(other.access)
{
	udt = other.udt;
}

member_function &member_function::operator=(const member_function &other)
{
	if (this != &other)
	{
		impl = other.impl;
		udt = other.udt;
		flags = other.flags;
		access = other.access;
	}
	return *this;
}

const block_statement &member_function::body() const
{
	return impl.statements;
}

block_statement &member_function::body()
{
	return impl.statements;
}

parameter_list &member_function::parameters()
{
	return impl.parameters;
}

const parameter_list &member_function::parameters() const
{
	return impl.parameters;
}

template_parameter_list &member_function::template_parameters()
{
	return impl.template_parameters;
}

const template_parameter_list &member_function::template_parameters() const
{
	return impl.template_parameters;
}

catch_list &member_function::catch_blocks()
{
	return impl.catch_blocks;
}

const catch_list &member_function::catch_blocks() const
{
	return impl.catch_blocks;
}

access_levels member_function::accessibility() const
{
	return access;
}

member_function &member_function::is_final(bool flag)
{
	flags = flag ? flags | final_mask : flags & ~final_mask;
	return *this;
}

bool member_function::is_final() const
{
	return flags & final_mask;
}

member_function &member_function::reference_qualifier(ref_qualifier flag)
{
	flags &= ~qualifier_mask;
	flags |= ((short)(flag) & ~qualifier_mask);
	return *this;
}

ref_qualifier member_function::reference_qualifier() const
{
	return (ref_qualifier)(flags & qualifier_mask);
}

ACCESSOR_IMPL_2(member_function, is_inline, bool, impl.is_inline)
ACCESSOR_IMPL_2(member_function, has_try_block, bool, impl.has_function_try_block)
ACCESSOR_IMPL_2(member_function, is_constexpr, bool, impl.is_const_expr)
ACCESSOR_IMPL_2(member_function, is_virtual, bool, impl.is_virtual)
ACCESSOR_IMPL_2(member_function, is_abstract, bool, impl.is_abstract)
ACCESSOR_IMPL_2(member_function, is_static, bool, impl.is_static)
ACCESSOR_IMPL_2(member_function, is_constant, bool, impl.is_constant)
ACCESSOR_IMPL_2(member_function, is_volatile, bool, impl.is_volatile)
ACCESSOR_IMPL_2(member_function, is_override, bool, impl.is_override)
ACCESSOR_IMPL_2(member_function, return_type, shared_ptr<type>, impl.return_type)
ACCESSOR_IMPL_2(member_function, has_trailing_return_type, bool, impl.has_trailing_return_type)
ACCESSOR_IMPL_2(member_function, is_var_arg, bool, impl.is_var_arg)
ACCESSOR_IMPL_2(member_function, is_no_except, bool, impl.is_no_except)
ACCESSOR_IMPL_2(member_function, no_except_expr, copyable_ptr<expression>, impl.no_except_expr)

ostream &member_function::write_declaration(ostream &os) const
{
	write_template_parameters(os, impl.template_parameters);

	if (impl.is_const_expr)
		os << "constexpr ";
	if (impl.is_inline)
		os << "inline ";
	if (impl.is_static)
		os << "static ";
	if (impl.is_virtual || impl.is_abstract)
		os << "virtual ";

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

	if (impl.is_constant)
		os << " const";
	if (impl.is_volatile)
		os << " volatile";
	if (impl.is_override)
		os << " override";
	if (is_final())
		os << " final";
    if(impl.is_no_except)
    {
        if(impl.no_except_expr)
        {
            os << " noexcept(" << *impl.no_except_expr << ")";
        }
        else
            os << " noexcept";
    }
	if (impl.is_abstract)
		os << " = 0";

	switch (reference_qualifier())
	{
	case ref_qualifier::lvalue:
		os << " &";
		break;
	case ref_qualifier::rvalue:
		os << " &&";
		break;
	}

	if (impl.has_trailing_return_type)
		os << " -> " << impl.return_type->get_name();

	os << ";" << endl;
	return os;
}

class member_function::write_definition_helper
{
	const member_function *fn;

public:
	write_definition_helper(const member_function *f)
		: fn(f)
	{
		fn->inline_definition = true;
	}

	~write_definition_helper()
	{
		fn->inline_definition = false;
	}
};

ostream &member_function::write_inline_definition(ostream &os) const
{
	write_definition_helper helper(this);

	write_definition(os);

	return os;
}

ostream &member_function::write_definition(ostream &os) const
{
	vector<user_defined_type *> containers;

	containers.push_back(udt.get());
	auto ptr = udt->container().get();
	while (ptr)
	{
		containers.push_back(ptr);
		ptr = ptr->container().get();
	}

	if (!inline_definition)
	{
		for (auto iter = containers.rbegin(); iter != containers.rend(); ++iter)
		{
			(*iter)->write_template_parameters(os);
		}
	}
	write_template_parameters(os, impl.template_parameters);

	if (impl.is_const_expr)
		os << "constexpr ";
	if (impl.is_inline)
		os << "inline ";
	if (impl.is_static)
		os << "static ";
	if (impl.is_virtual || impl.is_abstract)
		os << "virtual ";

	if (impl.has_trailing_return_type)
		os << "auto ";
	else
		os << impl.return_type->get_name() << " ";

	if (!inline_definition)
	{
		for (auto iter = containers.rbegin(); iter != containers.rend(); ++iter)
		{
			(*iter)->write_elaborated_name(os);
			os << "::";
		}
	}

	os << impl.name << "(";

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

	if (impl.is_constant)
		os << " const";
	if (impl.is_volatile)
		os << " volatile";
	if (impl.is_override)
		os << " override";

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
