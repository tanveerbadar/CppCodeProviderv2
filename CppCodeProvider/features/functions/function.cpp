#include "function.h"
#include "callable.h"
#include "..\declarations\declarator_specifier.h"
#include "..\declarations\variable_declaration.h"

using namespace std;

namespace cpp::codeprovider::types
{
	class type
	{
	public:
		string name;
	};

	namespace templates
	{
		class template_parameter
		{

		};
	}
}

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

	const vector<unique_ptr<variable_declaration>>& function::parameters() const
	{
		return impl->parameter_list;
	}

	const vector<unique_ptr<template_parameter>>& function::template_parameters() const
	{
		return impl->template_parameter_list;
	}

	bool function::is_inline() const
	{
		return impl->is_inline;
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
		if (func.impl->is_inline)
			os << "inline ";

		os << func.impl->return_type->name << " " << func.impl->name << "(";

		const auto& variables = func.impl->parameter_list;

		if (variables.size() > 1)
			for (auto i = 0; i < variables.size() - 1; ++i)
				os << *variables[i] << ", ";
		if (variables.size() > 0)
			os << *variables[variables.size() - 1] << endl;

		os << ")" << endl;
		os << func.impl->statements;

		return os;
	}
}