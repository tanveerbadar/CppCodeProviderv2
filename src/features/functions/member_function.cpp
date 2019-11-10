#include "callable.h"
#include "member_function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/user_defined_type.h"
#include "../types/template_parameters.h"
#include "../../utils/write_helpers.h"

namespace
{
const short qualifier_mask = 0x03;
const short final_mask = 0x04;
const short container_mask = 0x08;
} // namespace

using namespace std;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::functions::internals;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::utils;

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

ostream &member_function::write_declaration(ostream &os) const
{
	if (impl.template_parameters.size() > 0)
	{
		os << "template<";
		write_vector(os, impl.template_parameters);
		os << ">";
	}

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
		os << impl.return_type->get_name();

	os << " " << impl.name << "(";

	write_vector(os, impl.parameters);

	os << ")";

	if (impl.is_constant)
		os << " const";
	if (impl.is_volatile)
		os << " volatile";
	if (impl.is_override)
		os << " override";
	if (is_final())
		os << " final";
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
	os << endl;

	if (impl.has_trailing_return_type)
		os << " -> " << impl.return_type->get_name();

	os << ";" << endl;
	return os;
}

ostream &member_function::write_definition(ostream &os) const
{
	vector<user_defined_type*> containers;

	containers.push_back(udt.get());
	auto ptr = udt->container().get();
	while(ptr)
	{
		containers.push_back(ptr);
		ptr = ptr->container().get();
	}

	for(auto iter = containers.rbegin(); iter != containers.rend(); ++iter)
	{
		(*iter)->write_template_parameters(os);
		os << ' ';
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

	for(auto iter = containers.rbegin(); iter != containers.rend(); ++iter)
	{
		(*iter)->write_elaborated_name(os);
		os << "::";
	}

	os << impl.name << "(";

	write_vector(os, impl.parameters);

	os << ")";

	if (impl.is_constant)
		os << " const";
	if (impl.is_volatile)
		os << " volatile";
	if (impl.is_abstract)
		os << " = 0";
	if (impl.is_override)
		os << " override";
	os << endl;

	if (impl.has_trailing_return_type)
		os << " -> " << impl.return_type->get_name() << endl;

	if (impl.has_function_try_block)
		os << "try" << endl;

	os << impl.statements;

	if (impl.has_function_try_block)
		write_vector(os, impl.catch_blocks);

	return os;
}
