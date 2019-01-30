#include "variable_declaration_list.h"
#include "../expressions/common.h"
#include "../types/common.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::utils;

namespace cpp::codeprovider::declarations
{
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

	void variable_declaration_list::write(ostream& os) const
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

		write_vector(os, list.declarations());
		
		return os;
	}
}
