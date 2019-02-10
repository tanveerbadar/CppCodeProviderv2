#include "callable.h"
#include "function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/template_parameter.h"
#include "../../utils/write_helpers.h"

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

	function::~function()
	{		
	}

	parameter_list& function::parameters()
	{
		return impl->parameters;
	}

	const parameter_list &function::parameters() const
	{
		return impl->parameters;
	}

	template_parameter_list& function::template_parameters()
	{
		return impl->template_parameters;
	}

	const template_parameter_list &function::template_parameters() const
	{
		return impl->template_parameters;
	}

	catch_list &function::catch_blocks()
	{
		return impl->catch_blocks;
	}

	const catch_list &function::catch_blocks() const
	{
		return impl->catch_blocks;
	}

	ACCESSOR_IMPL(function, is_inline, bool, is_inline)
	ACCESSOR_IMPL(function, has_try_block, bool, has_function_try_block)
	ACCESSOR_IMPL(function, is_constexpr, bool, is_const_expr)
	ACCESSOR_IMPL(function, is_static, bool, is_static)

	block_statement& function::body()
	{
		return impl->statements;
	}
	
	const block_statement& function::body() const
	{
		return impl->statements;
	}

	const type& function::return_type() const
	{
		return *impl->return_type;
	}

	function& function::return_type(unique_ptr<type> t)
	{
		impl->return_type = move(t);
		return *this;
	}

	ostream &function::write_declaration(ostream &os) const
	{
		if (impl->template_parameters.size() > 0)
		{
			os << "template<";
			write_vector(os, impl->template_parameters);
			os << ">";
		}

		if (impl->is_const_expr)
			os << "constexpr ";
		if (impl->is_inline)
			os << "inline ";
		if (impl->is_static)
			os << "static ";

		if (impl->has_trailing_return_type)
			os << "auto ";
		else
			os << impl->return_type->get_name();

		os << " " << impl->name << "(";

		write_vector(os, impl->parameters);

		os << ")" << endl;

		if (impl->has_trailing_return_type)
			os << " -> " << impl->return_type->get_name();

		os << ";" << endl;

		return os;
	}

	ostream &function::write_definition(ostream & os) const
	{
		if (impl->template_parameters.size() > 0)
		{
			os << "template<";
			write_vector(os, impl->template_parameters);
			os << ">";
		}

		if (impl->is_const_expr)
			os << "constexpr ";
		if (impl->is_inline)
			os << "inline ";
		if (impl->is_static)
			os << "static ";

		if (impl->has_trailing_return_type)
			os << "auto ";
		else
			os << impl->return_type->get_name();

		os << " " << impl->name << "(";

		write_vector(os, impl->parameters);

		os << ")" << endl;

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