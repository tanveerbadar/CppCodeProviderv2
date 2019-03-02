#ifndef COPYABLE_PTR_HEADER
#define COPYABLE_PTR_HEADER

#pragma once

#include <memory>

namespace cpp::codeprovider::utils
{
template <typename T>
class copyable_ptr
{
    std::unique_ptr<T> ptr;

  public:
    copyable_ptr() = default;

    copyable_ptr(std::unique_ptr<T> &&p)
        : ptr(move(p))
    {
    }

    copyable_ptr(const copyable_ptr &other)
        : ptr(other.ptr ? (T*)other.ptr->clone().release() : 0)
    {
    }

    copyable_ptr &operator=(const copyable_ptr &other)
    {
        if (this != &other)
        {
			ptr.reset(other.ptr ? (T*)other.ptr->clone().release() : 0);
        }
        return *this;
    }

    T *operator->()
    {
        return ptr.get();
    }

    T &operator*()
    {
        return *ptr;
    }

    const T *operator->() const
    {
        return ptr.get();
    }

    const T &operator*() const
    {
        return *ptr;
    }

    explicit operator bool () const
    {
        return ptr.operator bool();
    }
};
} // namespace cpp::codeprovider::utils

#endif