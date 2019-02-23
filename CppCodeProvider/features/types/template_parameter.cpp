#include "template_parameter.h"

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
