#include <string>
#include "primitive_expression.h"

using namespace std;
using namespace cpp::codeprovider::expressions;

primitive_expression::primitive_expression(const string &p)
    : e1(p)
{
}

const string &primitive_expression::expr() const
{
    return e1;
}

expression_type primitive_expression::type() const
{
    return expression_type::primitive;
}

unique_ptr<expression> primitive_expression::clone() const
{
    return make_unique<primitive_expression>(*this);
}

void primitive_expression::write(ostream &os) const
{
    os << e1;
}