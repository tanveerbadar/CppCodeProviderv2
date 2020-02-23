#include "constructor.h"
#include "../../formatters/formatter_settings.h"
#include "../../utils/write_helpers.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/template_parameters.h"
#include "../types/user_defined_type.h"

using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::functions::internals;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::utils;
using namespace cpp::codeprovider::formatting;

constructor::constructor(std::shared_ptr<user_defined_type> t)
	: udt(t)
{
}

const initializer_list &constructor::initializers() const
{
	return init_list;
}

initializer_list &constructor::initializers()
{
	return init_list;
}

const block_statement &constructor::body() const
{
	return impl.statements;
}

block_statement &constructor::body()
{
	return impl.statements;
}

parameter_list &constructor::parameters()
{
	return impl.parameters;
}

const parameter_list &constructor::parameters() const
{
	return impl.parameters;
}

template_parameter_list &constructor::template_parameters()
{
	return impl.template_parameters;
}

const template_parameter_list &constructor::template_parameters() const
{
	return impl.template_parameters;
}

catch_list &constructor::catch_blocks()
{
	return impl.catch_blocks;
}

const catch_list &constructor::catch_blocks() const
{
	return impl.catch_blocks;
}

access_levels constructor::accessibility() const
{
	return access;
}

ACCESSOR_IMPL_2(constructor, is_inline, bool, impl.is_inline)
ACCESSOR_IMPL_2(constructor, has_try_block, bool, impl.has_function_try_block)
ACCESSOR_IMPL_2(constructor, is_constexpr, bool, impl.is_const_expr)
ACCESSOR_IMPL_2(constructor, is_no_except, bool, impl.is_no_except)
ACCESSOR_IMPL_2(constructor, no_except_expr, copyable_ptr<expression>, impl.no_except_expr)

std::ostream &constructor::write_declaration(std::ostream &os) const
{
	write_template_parameters(os, impl.template_parameters);

	if (impl.is_const_expr)
		os << "constexpr ";
	if (impl.is_inline)
		os << "inline ";

	os << udt->get_name() << "(";

	write_vector(os, impl.parameters);

	os << ")";

	if (impl.is_no_except)
	{
		if (impl.no_except_expr)
		{
			os << " noexcept(" << *impl.no_except_expr << ")";
		}
		else
			os << " noexcept";
	}

	os << ";" << std::endl;
	return os;
}

void write_vector(std::ostream &os, const initializer_list &init)
{
	if (init.size() > 0)
	{
		if (init.size() > 1)
			for (auto i = 0; i < init.size() - 1; ++i)
			{
				os << init[i].first << '(' << *init[i].second << ')';
				os << ", ";
			}
		os << init[init.size() - 1].first << '(' << *init[init.size()-1].second << ')';
	}
}

class constructor::write_definition_helper
{
	const constructor *fn;

public:
	write_definition_helper(const constructor *f)
		: fn(f)
	{
		fn->inline_definition = true;
	}

	~write_definition_helper()
	{
		fn->inline_definition = false;
	}
};

std::ostream &constructor::write_inline_definition(std::ostream &os) const
{
	write_definition_helper helper(this);

	write_definition(os);

	return os;
}

std::ostream &constructor::write_definition(std::ostream &os) const
{
	std::vector<user_defined_type *> containers;

	containers.push_back(udt.get());
	auto ptr = udt->container().get();
	while (ptr)
	{
		containers.push_back(ptr);
		ptr = ptr->container().get();
	}

	if (!inline_definition)
	{
		for (auto iter = containers.rbegin(); iter != containers.rend(); ++iter)
		{
			(*iter)->write_template_parameters(os);
		}
	}
	write_template_parameters(os, impl.template_parameters);

	if (impl.is_const_expr)
		os << "constexpr ";
	if (impl.is_inline)
		os << "inline ";

	if (!inline_definition)
	{
		for (auto iter = containers.rbegin(); iter != containers.rend(); ++iter)
		{
			(*iter)->write_elaborated_name(os);
			os << "::";
		}
	}

	os << udt->get_name() << "(";

	write_vector(os, impl.parameters);

	os << ")";

	if (impl.is_no_except)
	{
		if (impl.no_except_expr)
		{
			os << " noexcept(" << *impl.no_except_expr << ")";
		}
		else
			os << " noexcept";
	}

	os << std::endl;

	auto indent = formatter_settings::settings.get_indent_string();

	if (impl.has_function_try_block)
		os << indent << "try" << std::endl;

	if (!init_list.empty())
	{
		os << indent << indent << ": ";
		write_vector(os, init_list);
		os << std::endl;
	}

	os << impl.statements;

	if (impl.has_function_try_block)
		write_vector(os, impl.catch_blocks);

	return os;
}
