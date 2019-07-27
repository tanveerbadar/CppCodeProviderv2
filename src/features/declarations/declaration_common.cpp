#include "common.h"
#include "../types/common.h"

using namespace std;
using namespace cpp::codeprovider::declarations;

declaration::declaration(const declarator_specifier &ds)
    : var_specifier(ds)
{
}

const declarator_specifier &declaration::specifier() const
{
    return var_specifier;
}
