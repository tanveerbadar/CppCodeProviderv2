#ifndef NESTED_TYPE_HEADER
#define NESTED_TYPE_HEADER

#pragma once

#include <memory>

namespace cpp::codeprovider::types
{
class nested_type
{
    std::shared_ptr<nested_type> container;
};
} // namespace cpp::codeprovider::types

#endif