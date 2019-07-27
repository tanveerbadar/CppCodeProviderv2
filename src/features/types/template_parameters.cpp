#include "template_parameters.h"

using namespace std;
using namespace cpp::codeprovider::namespaces;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;

template_parameter::template_parameter(const string &n)
	: type(n)
{
}

ostream &template_parameter::write_forward_declaration(ostream &os) const
{
	return os;
}

ostream &template_parameter::write_declaration(ostream &os) const
{
	os << "typename" << (is_parameter_pack() ? "... " : " ") << get_name();
	return os;
}

ostream &template_parameter::write_definition(ostream &os) const
{
	os << "typename" << (is_parameter_pack() ? "... " : " ") << get_name();
	return os;
}

unique_ptr<namespace_scope_entity> template_parameter::clone() const
{
	auto ptr(make_unique<template_parameter>(*this));
	return unique_ptr<namespace_scope_entity>(ptr.release());
}

ACCESSOR_IMPL_2(template_parameter, is_parameter_pack, bool, pack)

non_type_template_parameter::non_type_template_parameter(const string &type, const string &param)
	: template_parameter(type), p(param)
{
}

ostream &non_type_template_parameter::write_declaration(ostream &os) const
{
	os << get_name() << (is_parameter_pack() ? "... " : " ") << p;
	return os;
}

ostream &non_type_template_parameter::write_definition(ostream &os) const
{
	os << get_name() << (is_parameter_pack() ? "... " : " ") << p;
	return os;
}

unique_ptr<namespace_scope_entity> non_type_template_parameter::clone() const
{
	auto ptr(make_unique<non_type_template_parameter>(*this));
	return unique_ptr<namespace_scope_entity>(ptr.release());
}

template_template_parameter::template_template_parameter(const string &type, int n)
	: template_parameter(type), arguments(n)
{
}

namespace
{
void write(ostream &os, const string &name, int n, bool is_parameter_pack)
{
	os << "template<";
	if (n > 1)
		for (auto i = 1; i < n; ++i)
			os << "typename ,";
	os << "typename";
	os << "> class" << (is_parameter_pack ? "... " : " ") << name;
}
} // namespace

ostream &template_template_parameter::write_declaration(ostream &os) const
{
	write(os, get_name(), arguments, is_parameter_pack());
	return os;
}

ostream &template_template_parameter::write_definition(ostream &os) const
{
	write(os, get_name(), arguments, is_parameter_pack());
	return os;
}

unique_ptr<namespace_scope_entity> template_template_parameter::clone() const
{
	auto ptr(make_unique<template_template_parameter>(*this));
	return unique_ptr<namespace_scope_entity>(ptr.release());
}
