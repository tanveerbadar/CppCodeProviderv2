#include "include_directive.h"

using namespace std;
using namespace cpp::codeprovider::preprocessor;

include_directive::include_directive(const string &name, bool sys)
    : header(name), is_system(sys)
{
}

ostream &include_directive::write_definition(ostream &os) const
{
    return write_declaration(os);
}

ostream &include_directive::write_declaration(ostream &os) const
{
    os << "#include " << (is_system ? '<' : '"') << header << (is_system ? '>' : '"');
    return os;
}