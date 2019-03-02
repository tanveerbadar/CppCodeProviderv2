#include "base_type.h"
#include "custom_type.h"
#include "template_parameters.h"
#include "../declarations/common.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../functions/callable.h"
#include "../functions/member_function.h"
#include "../statements/try_statement.h"

using namespace std;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::types::internal;

namespace cpp::codeprovider::types::internal
{
    std::ostream & operator<<(std::ostream &os, type_key key)
    {
        switch (key)
        {
        case type_key::class_type:
            os << "class ";
            break;
        case type_key::enum_type:
            os << "enum ";
            break;
        case type_key::struct_type:
            os << "struct ";
            break;
        case type_key::union_type:
            os << "union ";
            break;
        }
        return os;
    }
} // namespace cpp::codeprovider::types::internal

custom_type::custom_type(type_key k)
    : key(k)
{
}

custom_type::custom_type(const custom_type &other)
    : key(other.key), is_scoped_enum(other.is_scoped_enum)
{
    for (auto &f : other.functions)
        functions.emplace_back(f);

    for (auto &f : other.fields)
        fields.push_back(make_pair(f.first, f.second->clone()));

    for (auto &param : other.template_params)
        template_params.emplace_back(make_unique<template_parameter>(*param));
}

custom_type &custom_type::operator=(const custom_type &other)
{
    if (this != &other)
    {
        member_function_list functionscopy;
        for (auto &f : other.functions)
            functionscopy.emplace_back(f);

        member_field_list fieldscopy;
        for (auto &f : other.fields)
            fieldscopy.push_back(make_pair(f.first, f.second->clone()));

        template_parameter_list template_paramscopy;
        for (auto &param : other.template_params)
            template_paramscopy.emplace_back(make_unique<template_parameter>(*param));

        key = other.key;
        is_scoped_enum = other.is_scoped_enum;
        swap(fields, fieldscopy);
        swap(functions, functionscopy);
        swap(template_params, template_paramscopy);
    }
    return *this;
}

bool custom_type::is_class() const
{
    return key == type_key::class_type;
}