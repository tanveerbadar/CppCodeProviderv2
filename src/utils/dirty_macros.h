#ifndef DIRTY_MACRO_HEADER
#define DIRTY_MACRO_HEADER

#pragma once

#define ACCESSOR_DECLARATION(typeName, accessor_name, accessor_type) \
    accessor_type accessor_name() const;                             \
    typeName &accessor_name(accessor_type obj);

#define ACCESSOR_DECLARATION_2(typeName, accessor_name, accessor_type, parameter_type) \
    accessor_type accessor_name() const;                                               \
    typeName &accessor_name(parameter_type obj);

#define ACCESSOR_IMPL(typeName, accessor_name, accessor_type, field_name) \
    typeName &typeName::accessor_name(accessor_type val)                  \
    {                                                                     \
        impl->field_name = val;                                           \
        return *this;                                                     \
    }                                                                     \
                                                                          \
    accessor_type typeName::accessor_name() const                         \
    {                                                                     \
        return impl->field_name;                                          \
    }

#define ACCESSOR_IMPL_2(typeName, accessor_name, accessor_type, field_name) \
    typeName &typeName::accessor_name(accessor_type val)                    \
    {                                                                       \
        field_name = val;                                                   \
        return *this;                                                       \
    }                                                                       \
                                                                            \
    accessor_type typeName::accessor_name() const                           \
    {                                                                       \
        return field_name;                                                  \
    }

#define ACCESSOR_IMPL_3(typeName, accessor_name, accessor_type, field_name, parameter_type) \
    typeName &typeName::accessor_name(parameter_type val)                    \
    {                                                                       \
        field_name = val;                                                   \
        return *this;                                                       \
    }                                                                       \
                                                                            \
    accessor_type typeName::accessor_name() const                           \
    {                                                                       \
        return field_name;                                                  \
    }

#endif