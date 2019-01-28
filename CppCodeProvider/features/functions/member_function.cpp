#include "callable.h"
#include "member_function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../types/user_defined_type.h"
#include "../types/template_parameter.h"
#include "../../utils/write_helpers.h"

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

	bool member_function::is_inline() const
	{
		return impl->is_inline;
	}
	
	member_function& member_function::is_inline(bool flag)
	{
		impl->is_inline = flag;
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

	ostream& operator<<(ostream& os, const member_function& func)
	{
		write_vector(os, func.impl->template_parameter_list);

		if(func.impl->is_const_expr)
			os << "constexpr ";
		if(func.impl->is_inline)
			os << "inline ";
		if(func.impl->is_static)
			os << "static ";
		if(func.impl->is_virtual || func.impl->is_abstract)
			os << "virtual ";

		if(func.impl->has_trailing_return_type)
			os << "auto ";
		else
			os << func.impl->return_type->get_name();

		os << " " << func.impl->name << "(";

		write_vector(os, func.impl->parameter_list);

		os << ")";

		if(func.impl->is_constant)
			os << " const";
		if(func.impl->is_volatile)
			os << " volatile";
		if(func.impl->is_abstract)
			os << " = 0";
		if(func.impl->is_override)
			os << " override";
		os << endl;
	
		if(func.impl->has_trailing_return_type)
			os << " -> " << func.impl->return_type->get_name() << endl;
	
		os << func.impl->statements;

		return os;
	}
}