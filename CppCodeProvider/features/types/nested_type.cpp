#include <algorithm>
#include "nested_type.h"

using namespace std;
using namespace cpp::codeprovider::types;

nested_type::~nested_type()
{
}

ostream &nested_type::write_qualified_name(ostream &os) const
{
    if (container.get() != nullptr)
        container->write_qualified_name(os);
    write_elaborated_name(os);
    os << "::";
    return os;
}

vector<const nested_type *> nested_type::get_containers() const
{
    vector<const nested_type *> containers;
    auto c = this;
    do
    {
        containers.push_back(c);
        c = c->container.get();
    } while (c != nullptr);

    reverse(begin(containers), end(containers));

    return containers;
}