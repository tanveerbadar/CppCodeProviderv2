#ifndef FORWARD_DECLARATIONS_HEADER
#define FORWARD_DECLARATIONS_HEADER

#pragma once

namespace cpp
{
namespace codeprovider
{
namespace expressions
{
class expression;
class lambda_expression;
}

namespace types
{
enum class access_levels;
class type;

namespace templates
{
class template_parameter;
}

class union_type;
class user_defined_type;
class base_type;
} // namespace types

namespace declarations
{
class declaration;
class variable_declaration;
class variable_declaration_list;
} // namespace declarations

namespace statements
{
class block_statement;
class catch_clause;
} // namespace statements

namespace functions
{
class function;
class member_function;

namespace internals
{
struct callable;
}
} // namespace functions

namespace namespaces
{
class namespace_scope_entity;
}
} // namespace codeprovider
} // namespace cpp

#endif // !FORWARD_DECLARATIONS_HEADER