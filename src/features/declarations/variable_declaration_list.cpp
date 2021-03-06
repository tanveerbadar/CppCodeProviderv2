#include "variable_declaration_list.h"
#include "../expressions/common.h"
#include "../types/common.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::utils;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::namespaces;

variable_declaration_list::variable_declaration_list(const declarator_specifier &specifier)
	: declaration(specifier)
{
}

vector<declarator> &variable_declaration_list::declarations()
{
	return var_decls;
}

const vector<declarator> &variable_declaration_list::declarations() const
{
	return var_decls;
}

unique_ptr<namespace_scope_entity> variable_declaration_list::clone() const
{
	return make_unique<variable_declaration_list>(*this);
}

ostream &variable_declaration_list::write_declaration(ostream &os) const
{
	os << specifier();

	write_vector(os, var_decls);
	return os;
}

ostream &variable_declaration_list::write_definition(ostream &os) const
{
	os << specifier();

	write_vector(os, var_decls);
	return os;
}
