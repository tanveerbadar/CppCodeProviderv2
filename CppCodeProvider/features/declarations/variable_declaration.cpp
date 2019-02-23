#include "variable_declaration.h"
#include "../expressions/common.h"
#include "../types/common.h"

namespace cpp::codeprovider::declarations
{
	using namespace std;

	variable_declaration::variable_declaration(const declarator_specifier& specifier)
		:var_specifier(specifier)
	{
	}

	const declarator_specifier& variable_declaration::specifier() const
	{
		return var_specifier;
	}

	declarations::declarator& variable_declaration::var_declarator()
	{
		return var_decl;
	}

	unique_ptr<declaration> variable_declaration::clone() const
	{
		return make_unique<variable_declaration>(*this);
	}

	ostream& variable_declaration::write_declaration(ostream& os) const
	{
		os << var_specifier << var_decl;
		return os;
	}

	ostream &variable_declaration::write_definition(ostream &os) const
	{
		os << var_specifier << var_decl;
		return os;
	}

	const declarations::declarator& variable_declaration::var_declarator() const
	{
		return var_decl;
	}

}