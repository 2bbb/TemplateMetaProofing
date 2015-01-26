//
//  Core/Constants.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Macros.h"

namespace Types {
    struct Kind {};
};

namespace Meta {
    struct True;
    struct False;
};

DeclareType(Bool);

namespace Meta {
    struct True {
        SetType(Bool);
        using type = True;
        static const char * const val() { return "T"; }
    };
    struct False {
        SetType(Bool);
        using type = False;
        static const char * const val() { return "F"; }
    };
}

namespace {
    template <typename A>
    struct is_bool_impl : public Meta::False {};
    
    template <>
    struct is_bool_impl<Meta::True> : public Meta::True {};

    template <>
    struct is_bool_impl<Meta::False> : public Meta::True {};
};

template <typename A>
using IsBool = typename is_bool_impl<A>::type;

namespace Meta {
    template <typename T>
    struct AssertValue;
    
    template <>
    struct AssertValue<True> {
        static const bool value = true;
    };
    
    template <>
    struct AssertValue<False> {
        static const bool value = false;
    };
};