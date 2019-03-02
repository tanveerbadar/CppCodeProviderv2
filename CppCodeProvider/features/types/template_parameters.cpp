#include "template_parameters.h"

using namespace std;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;

template_parameter::template_parameter(const string& n)
	:type(n)
{
	
}

ostream &template_parameter::write_declaration(ostream &os) const
{
	os << "typename " << get_name();
	return os;
}

ostream &template_parameter::write_definition(ostream &os) const
{
	os << "typename " << get_name();
	return os;
}

unique_ptr<type> template_parameter::clone() const
{
	return make_unique<template_parameter>(*this);
}

non_type_template_parameter::non_type_template_parameter(const string &type, const string& param)
	: template_parameter(type), p(param)
{
}

ostream &non_type_template_parameter::write_declaration(ostream &os) const
{
	os << get_name() << " " << p;
	return os;
}

ostream &non_type_template_parameter::write_definition(ostream &os) const
{
	os << get_name() << " " << p;
	return os;
}

unique_ptr<type> non_type_template_parameter::clone() const
{
	return make_unique<non_type_template_parameter>(*this);
}

template_template_parameter::template_template_parameter(const string &type, int n)
	: template_parameter(type), arguments(n)
{
}

namespace
{
	void write(ostream& os, const string& name, int n)
	{
		os << "template<";
		if (n > 1)
			for (auto i = 1; i < n; ++i)
				os << "typename ,";
		os << "typename";
		os << "> class " << name;
	}
}

ostream &template_template_parameter::write_declaration(ostream &os) const
{
	write(os, get_name(), arguments);
	return os;
}

ostream &template_template_parameter::write_definition(ostream &os) const
{
	write(os, get_name(), arguments);
	return os;
}

unique_ptr<type> template_template_parameter::clone() const
{
	return make_unique<template_template_parameter>(*this);
}
