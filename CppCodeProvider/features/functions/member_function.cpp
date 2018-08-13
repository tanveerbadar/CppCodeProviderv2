#include "callable.h"
#include "member_function.h"
#include "..\declarations\variable_declaration.h"
#include "..\types\user_defined_type.h"
#include "..\types\template_parameter.h"
#include "..\..\utils\write_helpers.h"

using namespace std;

namespace cpp::codeprovider::functions
{
	using namespace internals;
	using namespace statements;
	using namespace types;
	using namespace utils;

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
		write_vector(os, func.impl->template_parameter_list);

		os << func.impl->return_type->get_name() << " " << func.impl->name << "(";

		write_vector(os, func.impl->parameter_list);

		os << ")" << endl;
		os << func.impl->statements;

		return os;
	}
}