#include "if_directive.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::preprocessor;

if_directive::if_directive(const string &name, bool flag, const global_entity_list &true_block)
    : macro(name), is_ifndef(flag), if_block(true_block)
{
}

if_directive::if_directive(const string &name, bool flag, const global_entity_list &true_block, const global_entity_list &false_block)
    : macro(name), is_ifndef(flag), if_block(true_block), else_block(false_block)
{
}

ostream &if_directive::write_definition(ostream &os) const
{
    os << (is_ifndef ? "#ifndef " : "#ifdef ") << macro;
    utils::write_definitions(os, if_block);

    if (!else_block.empty())
    {
        os << "#else" << endl;
        utils::write_definitions(os, else_block);
    }
    return os;
}

ostream &if_directive::write_declaration(ostream &os) const
{
    os << (is_ifndef ? "#ifndef " : "#ifdef ") << macro;
    utils::write_declarations(os, if_block);

    if (!else_block.empty())
    {
        os << "#else" << endl;
        utils::write_declarations(os, else_block);
    }
    return os;
}