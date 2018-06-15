#include "function.h"
#include "callable.h"
#include "..\declarations\declarator_specific.h"
#include "..\declarations\variable_declaration.h"

namespace cpp::codeprovider::types::templates
{
	class template_parameter
	{

	};
}

namespace cpp::codeprovider::functions
{
	using namespace std;
	using namespace internals;
	using namespace statements;
	using namespace types;

	function::function(const string& n, unique_ptr<type_declaration> returns)
		:impl(make_unique<callable>(n,move(returns)))
	{
	}

	block_statement& function::body()
	{
		return impl->statements;
	}

	function& function::return_type(type_declaration& type)
	{
		impl->return_type.reset(new type_declaration(type));
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