//
//  Core/Types.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/17.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Utilities.h"
#include "Core/Meta.h"

template <typename T>
using IsType = typename T::IsType;

template <typename T>
using TypeOf = typename T::TypeInfo;

template <typename X, typename T>
using HasType = Meta::And<IsType<T>, Meta::Equal<TypeOf<X>, T>>;

template <typename X, typename Y>
using IsSameType = Meta::Equal<TypeOf<X>, TypeOf<Y>>;

namespace {
    template <typename ...>
    struct are_same_type_impl;
    
    template <typename X, typename Y, typename ... Zs>
    struct are_same_type_impl<X, Y, Zs ...> {
        using type = Meta::And<Meta::Equal<TypeOf<X>, TypeOf<Y>>, Reduction<are_same_type_impl<Y, Zs ...>>>;
    };
    
    template <typename X>
    struct are_same_type_impl<X> {
        using type = Meta::True;
    };
    
    template <>
    struct are_same_type_impl<> {
        using type = Meta::True;
    };
};

template <typename ... Xs>
using AreSameType = Reduction<are_same_type_impl<Xs ...>>;
