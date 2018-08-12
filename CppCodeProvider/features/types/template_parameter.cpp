#include "template_parameter.h"

using namespace std;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;

void template_parameter::write(ostream& os) const
{
	os << "typename " << get_name();
}

unique_ptr<type> template_parameter::clone() const
{
	return make_unique<template_parameter>(*this);
}
