#include "namespace_scope.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::namespaces;
using namespace cpp::codeprovider::utils;

ostream &operator<<(ostream &os, const namespace_scope &ns)
{
    ns.write_declaration(os);
    return os;
}

namespace_scope::namespace_scope(const string &ns)
    : name(ns)
{
}

entity_list &namespace_scope::entities()
{
    return contained_entities;
}

const entity_list &namespace_scope::entities() const
{
    return contained_entities;
}

ostream &namespace_scope::write_declaration(ostream &os) const
{
    write_declarations(os, contained_entities);
    return os;
}

ostream &namespace_scope::write_definition(ostream &os) const
{
    write_declarations(os, contained_entities);
    return os;
}
