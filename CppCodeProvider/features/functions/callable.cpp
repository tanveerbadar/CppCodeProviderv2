#include "callable.h"
#include "function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/template_parameter.h"

using namespace std;

namespace cpp::codeprovider::functions::internals
{
	using namespace std;
	using namespace types;
	using namespace declarations;
	using namespace templates;

	callable::callable(const string& n, unique_ptr<type> returns)
		: name(n), return_type(move(returns))
	{
	}

	callable::callable(const callable &other)
		: statements(other.statements), return_type(other.return_type ? other.return_type->clone() : 0), name(other.name), is_inline(other.is_inline), is_const_expr(other.is_const_expr), is_static(other.is_static), is_abstract(other.is_abstract), is_constant(other.is_constant), is_volatile(other.is_volatile), is_virtual(other.is_virtual), is_override(other.is_override)
	{
		for (auto& param : other.parameter_list)
			parameter_list.emplace_back(make_unique<variable_declaration>(*param));

		for (auto& param : other.template_parameter_list)
			template_parameter_list.emplace_back(make_unique<template_parameter>(*param));
	}
}
