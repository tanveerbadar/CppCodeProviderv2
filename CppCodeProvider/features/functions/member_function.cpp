#include "callable.h"
#include "member_function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/user_defined_type.h"
#include "../types/template_parameter.h"
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

	member_function::member_function(const string& n, unique_ptr<type> returns, const user_defined_type& udt)
		:impl(make_unique<callable>(n, move(returns))), container(&udt)
	{
	}

	member_function::member_function(const member_function& other)
		:impl(make_unique<callable>(*other.impl)), container(other.container), access(other.access)
	{
	}

	member_function& member_function::operator=(const member_function& other)
	{
		if (this != &other)
		{
			impl = make_unique<callable>(*other.impl);
			container = other.container;
			access = other.access;
		}
		return *this;
	}
	
	const block_statement& member_function::body() const
	{
		return impl->statements;
	}

	block_statement& member_function::body()
	{
		return impl->statements;
	}

	const type& member_function::return_type() const
	{
		return *impl->return_type;
	}

	type& member_function::return_type()
	{
		return *impl->return_type;
	}

	member_function& member_function::return_type(unique_ptr<type> t)
	{
		impl->return_type = move(t);
		return *this;
	}

	vector<unique_ptr<variable_declaration>>& member_function::parameters()
	{
		return impl->parameter_list;
	}

	const vector<unique_ptr<variable_declaration>>& member_function::parameters() const
	{
		return impl->parameter_list;
	}

	vector<unique_ptr<template_parameter>>& member_function::template_parameters()
	{
		return impl->template_parameter_list;
	}

	const vector<unique_ptr<template_parameter>>& member_function::template_parameters() const
	{
		return impl->template_parameter_list;
	}

	vector<catch_clause> &member_function::catch_blocks()
	{
		return impl->catch_blocks;
	}

	const vector<catch_clause> &member_function::catch_blocks() const
	{
		return impl->catch_blocks;
	}

	access_levels member_function::accessibility() const
	{
		return access;
	}

	bool member_function::is_inline() const
	{
		return impl->is_inline;
	}
	
	member_function& member_function::is_inline(bool flag)
	{
		impl->is_inline = flag;
		return *this;
	}

	bool member_function::has_try_block() const
	{
		return impl->has_function_try_block;
	}

	member_function &member_function::has_try_block(bool flag)
	{
		impl->has_function_try_block = flag;
		return *this;
	}

	bool member_function::is_constexpr() const
	{
		return impl->is_const_expr;
	}

	member_function& member_function::is_constexpr(bool flag)
	{
		impl->is_const_expr = flag;
		return *this;
	}

	bool member_function::is_virtual() const
	{
		return impl->is_virtual;
	}

	member_function& member_function::is_virtual(bool flag)
	{
		impl->is_virtual = flag;
		return *this;
	}

	bool member_function::is_abstract() const
	{
		return impl->is_abstract;
	}

	member_function& member_function::is_abstract(bool flag)
	{
		impl->is_abstract = flag;
		return *this;
	}

	bool member_function::is_static() const
	{
		return impl->is_static;
	}
	member_function& member_function::is_static(bool flag)
	{
		impl->is_static = flag;
		return *this;
	}

	bool member_function::is_constant() const
	{
		return impl->is_constant;
	}

	member_function& member_function::is_constant(bool flag)
	{
		impl->is_constant = flag;
		return *this;
	}

	bool member_function::is_volatile() const
	{
		return impl->is_volatile;
	}
	
	member_function& member_function::is_volatile(bool flag)
	{
		impl->is_volatile = flag;
		return *this;
	}

	bool member_function::is_override() const
	{
		return impl->is_override;
	}
	
	member_function& member_function::is_override(bool flag)
	{
		impl->is_override = flag;
		return *this;
	}

	ostream &member_function::write_declaration(ostream &os) const
	{
		if (impl->template_parameter_list.size() > 0)
		{
			os << "template<";
			write_vector(os, impl->template_parameter_list);
			os << ">";
		}

		if (impl->is_const_expr)
			os << "constexpr ";
		if (impl->is_inline)
			os << "inline ";
		if (impl->is_static)
			os << "static ";
		if (impl->is_virtual || impl->is_abstract)
			os << "virtual ";

		if (impl->has_trailing_return_type)
			os << "auto ";
		else
			os << impl->return_type->get_name();

		os << " " << impl->name << "(";

		write_vector(os, impl->parameter_list);

		os << ")";

		if (impl->is_constant)
			os << " const";
		if (impl->is_volatile)
			os << " volatile";
		if (impl->is_abstract)
			os << " = 0";
		if (impl->is_override)
			os << " override";
		os << endl;

		if (impl->has_trailing_return_type)
			os << " -> " << impl->return_type->get_name();

		os << ";" << endl;
		return os;
	}

	ostream &member_function::write_definition(ostream & os) const
	{
		if (impl->template_parameter_list.size() > 0)
		{
			os << "template<";
			write_vector(os, impl->template_parameter_list);
			os << ">";
		}

		if (impl->is_const_expr)
			os << "constexpr ";
		if (impl->is_inline)
			os << "inline ";
		if (impl->is_static)
			os << "static ";
		if (impl->is_virtual || impl->is_abstract)
			os << "virtual ";

		if (impl->has_trailing_return_type)
			os << "auto ";
		else
			os << impl->return_type->get_name();

		os << " " << impl->name << "(";

		write_vector(os, impl->parameter_list);

		os << ")";

		if (impl->is_constant)
			os << " const";
		if (impl->is_volatile)
			os << " volatile";
		if (impl->is_abstract)
			os << " = 0";
		if (impl->is_override)
			os << " override";
		os << endl;

		if (impl->has_trailing_return_type)
			os << " -> " << impl->return_type->get_name() << endl;

		if (impl->has_function_try_block)
			os << "try" << endl;

		os << impl->statements;

		if (impl->has_function_try_block)
			write_vector(os, impl->catch_blocks);

		return os;
	}
}