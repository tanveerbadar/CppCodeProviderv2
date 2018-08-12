#include "callable.h"
#include "member_function.h"
#include "..\declarations\variable_declaration.h"
#include "..\types\user_defined_type.h"
#include "..\types\template_parameter.h"

using namespace std;

namespace cpp::codeprovider::functions
{
	using namespace internals;
	using namespace statements;
	using namespace types;

	member_function::member_function(const string& n, unique_ptr<type> returns, shared_ptr<user_defined_type> udt)
		:impl(make_unique<callable>(n, move(returns))), container(udt)
	{
	}

	member_function::member_function(const member_function& other)
		:impl(make_unique<callable>(*other.impl)), container(other.container), access(other.access)
	{
	}

	block_statement& member_function::body()
	{
		return impl->statements;
	}

	access_levels member_function::accessibility() const
	{
		return access;
	}

	ostream& operator<<(ostream& os, const member_function& func)
	{
		if (func.impl->is_inline)
			os << "inline ";

		os << func.impl->return_type->get_name() << " " << func.impl->name << "(";

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