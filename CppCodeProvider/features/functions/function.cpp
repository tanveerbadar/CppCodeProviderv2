#include "function.h"
#include "callable.h"
#include "../declarations/declarator_specifier.h"
#include "../declarations/variable_declaration.h"
#include "../types/common.h"
#include "../types/template_parameter.h"
#include "../../utils/write_helpers.h"
#include "../expressions/common.h"

using namespace std;
using namespace cpp::codeprovider::utils;

namespace cpp::codeprovider::functions
{
	using namespace internals;
	using namespace declarations;
	using namespace statements;
	using namespace types;
	using namespace templates;

	function::function(const string& n, unique_ptr<type> returns)
		:impl(make_unique<callable>(n,move(returns)))
	{
	}

	function::function(const function& other)
		: impl(make_unique<callable>(*other.impl))
	{
	}

	function& function::operator=(const function& other)
	{
		if (this != &other)
		{
			impl = make_unique<callable>(*other.impl);
		}
		return *this;
	}

	vector<unique_ptr<variable_declaration>>& function::parameters()
	{
		return impl->parameter_list;
	}

	const vector<unique_ptr<variable_declaration>>& function::parameters() const
	{
		return impl->parameter_list;
	}

	vector<unique_ptr<template_parameter>>& function::template_parameters()
	{
		return impl->template_parameter_list;
	}

	const vector<unique_ptr<template_parameter>>& function::template_parameters() const
	{
		return impl->template_parameter_list;
	}

	bool function::is_inline() const
	{
		return impl->is_inline;
	}

	function& function::is_inline(bool flag)
	{
		impl->is_inline = flag;
		return *this;
	}

	bool function::is_constexpr() const
	{
		return impl->is_const_expr;
	}

	function& function::is_constexpr(bool flag)
	{
		impl->is_const_expr = flag;
		return *this;
	}

	block_statement& function::body()
	{
		return impl->statements;
	}
	
	const block_statement& function::body() const
	{
		return impl->statements;
	}

	type& function::return_type() const
	{
		return *impl->return_type;
	}

	function& function::return_type(unique_ptr<type> t)
	{
		impl->return_type = move(t);
		return *this;
	}

	ostream& operator<<(ostream& os, const function& func)
	{
		write_vector(os, func.impl->template_parameter_list);
		
		if(func.impl->is_const_expr)
			os << "constexpr ";
		if(func.impl->is_inline)
			os << "inline ";
		if(func.impl->is_static)
			os << "static ";

		if(func.impl->has_trailing_return_type)
			os << "auto ";
		else
			os << func.impl->return_type->get_name();
		
		os << " " << func.impl->name << "(";

		write_vector(os, func.impl->parameter_list);

		os << ")" << endl;

		if(func.impl->has_trailing_return_type)
			os << " -> " << func.impl->return_type->get_name() << endl;

		os << func.impl->statements;

		return os;
	}
}