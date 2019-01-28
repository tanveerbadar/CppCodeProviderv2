#include "callable.h"
#include "function.h"
#include "../declarations/declarator_specifier.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../types/common.h"
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

	callable::callable(const callable& other)
		: statements(other.statements), return_type(other.return_type->clone()), name(other.name), is_inline(other.is_inline)
	{
		for (auto& param : other.parameter_list)
			parameter_list.emplace_back(make_unique<variable_declaration>(*param));

		for (auto& param : other.template_parameter_list)
			template_parameter_list.emplace_back(make_unique<template_parameter>(*param));
	}
}
