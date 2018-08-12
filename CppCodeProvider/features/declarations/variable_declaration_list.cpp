#include "variable_declaration_list.h"
#include "..\expressions\common.h"
#include "..\types\common.h"

namespace cpp::codeprovider::declarations
{
	using namespace std;

	variable_declaration_list::variable_declaration_list(const declarator_specifier& specifier)
		:var_specifier(specifier)
	{
	}

	vector<declarator>& variable_declaration_list::declarations()
	{
		return var_decls;
	}

	const vector<declarator>& variable_declaration_list::declarations() const
	{
		return var_decls;
	}

	unique_ptr<declaration> variable_declaration_list::clone() const
	{
		return make_unique<variable_declaration_list>(*this);
	}

	void variable_declaration_list::write(ostream& os)
	{
		os << *this;
	}

	const declarator_specifier& variable_declaration_list::specifier() const
	{
		return var_specifier;
	}

	ostream& operator<<(ostream& os, const variable_declaration_list& list)
	{
		os << list.specifier();

		const auto& variables = list.declarations();

		if (variables.size() > 1)
			for (auto i = 0; i < variables.size() - 1; ++i)
				os << variables[i] << ", ";
		os << variables[variables.size() - 1] << endl;

		return os;
	}
}
