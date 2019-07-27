#include "fold_expression.h"

using namespace std;
using namespace cpp::codeprovider::expressions;

fold_expression::fold_expression(expression_type t, expression_type ft, unique_ptr<expression> l, unique_ptr<expression> r)
    : e_type(t), f_type(ft), e1(move(l)), e2(move(r))
{
}

const expression &fold_expression::left() const
{
    return *e1;
}

const expression &fold_expression::right() const
{
    return *e2;
}

expression_type fold_expression::type() const
{
    return e_type;
}

expression_type fold_expression::fold_type() const
{
    return f_type;
}

unique_ptr<expression> fold_expression::clone() const
{
    return make_unique<fold_expression>(*this);
}

void fold_expression::write(ostream &os) const
{
    switch (f_type)
    {
    case expression_type::binary_fold:
        os << *e1 << e_type << " ... " << e_type << *e2;
        break;
    case expression_type::right_unary_fold:
        os << *e1 << e_type << " ... ";
        break;
    case expression_type::left_unary_fold:
        os << " ... " << e_type << *e2;
        break;
    }
}
