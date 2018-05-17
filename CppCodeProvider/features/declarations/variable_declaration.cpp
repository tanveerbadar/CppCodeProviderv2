#include "variable_declaration.h"
#include "..\expressions\common.h"

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

	declarator& variable_declaration::declarator()
	{
		return var_decl;
	}

	const declarator& variable_declaration::declarator() const
	{
		return var_decl;
	}

	ostream& operator<<(ostream& os, const variable_declaration& var)
	{
		os << var.specifier() << " " << var.declarator();
		return os;
	}
}