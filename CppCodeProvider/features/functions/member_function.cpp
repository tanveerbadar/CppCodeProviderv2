#include "callable.h"
#include "member_function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/user_defined_type.h"
#include "../types/template_parameters.h"
#include "../../utils/write_helpers.h"

using namespace std;

namespace cpp::codeprovider::functions
{
using namespace declarations;
using namespace internals;
using namespace statements;
using namespace types;
using namespace templates;
using namespace utils;

member_function::member_function(const string &n, shared_ptr<type> returns, shared_ptr<user_defined_type> udt)
	: impl(n, returns), container(udt)
{
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

ACCESSOR_IMPL_2(member_function, is_inline, bool, impl.is_inline)
ACCESSOR_IMPL_2(member_function, has_try_block, bool, impl.has_function_try_block)
ACCESSOR_IMPL_2(member_function, is_constexpr, bool, impl.is_const_expr)
ACCESSOR_IMPL_2(member_function, is_virtual, bool, impl.is_virtual)
ACCESSOR_IMPL_2(member_function, is_abstract, bool, impl.is_abstract)
ACCESSOR_IMPL_2(member_function, is_static, bool, impl.is_static)
ACCESSOR_IMPL_2(member_function, is_constant, bool, impl.is_constant)
ACCESSOR_IMPL_2(member_function, is_volatile, bool, impl.is_volatile)
ACCESSOR_IMPL_2(member_function, is_override, bool, impl.is_override)
ACCESSOR_IMPL_2(member_function, reference_qualifier, ref_qualifier, qualifier)
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
	if (impl.is_abstract)
		os << " = 0";
	if (impl.is_override)
		os << " override";

	switch (qualifier)
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
} // namespace cpp::codeprovider::functions