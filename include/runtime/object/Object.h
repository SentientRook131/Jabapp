//
// Created by FCWY on 24-11-24.
//

#pragma once
#include <typeinfo>

namespace Jabapp::Object{
    struct Object {
        enum class TypeTag{
            BUILTIN,
            USER_DEFINED
        };

        const TypeTag tag;

        Object(TypeTag tag): tag(tag) {}
    };

    template<typename T>
    struct BuiltInObject: Object {
        const std::type_info& type;
        T value;

        BuiltInObject(T v):
            Object(Object::TypeTag::BUILTIN),
            type(type),
            value(std::move(v)) {}
    };
}