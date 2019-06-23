#include "variable_declaration.h"
#include "../expressions/common.h"
#include "../types/common.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::namespaces;

variable_declaration::variable_declaration(const declarator_specifier &ds)
	: declaration(ds)
{
}

declarator &variable_declaration::var_declarator()
{
	return var_decl;
}

unique_ptr<namespace_scope_entity> variable_declaration::clone() const
{
	return make_unique<variable_declaration>(*this);
}

ostream &variable_declaration::write_declaration(ostream &os) const
{
	os << specifier() << var_decl;
	return os;
}

ostream &variable_declaration::write_definition(ostream &os) const
{
	os << specifier() << var_decl;
	return os;
}

const declarator &variable_declaration::var_declarator() const
{
	return var_decl;
}