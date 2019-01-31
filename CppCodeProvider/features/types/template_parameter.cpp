#include "template_parameter.h"

using namespace std;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;

ostream &template_parameter::write_declaration(ostream &os) const
{
	os << "typename " << get_name();
}

ostream &template_parameter::write_definition(ostream &os) const
{
	os << "typename " << get_name();
}

unique_ptr<type> template_parameter::clone() const
{
	return make_unique<template_parameter>(*this);
}
