#include "callable.h"
#include "member_function.h"
#include "..\declarations\variable_declaration.h"

namespace cpp::codeprovider::types
{
	namespace templates
	{
		class template_parameter
		{

		};
	}
}

namespace cpp::codeprovider::functions
{
	using namespace std;
	using namespace internals;
	using namespace statements;
	using namespace types;

	member_function::member_function(const string& n, unique_ptr<type> returns, const user_defined_type& udt)
		:impl(make_unique<callable>(n, move(returns))), container(&udt)
	{
	}

	block_statement& member_function::body()
	{
		return impl->statements;
	}

	ostream& operator<<(ostream& os, const member_function& func)
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