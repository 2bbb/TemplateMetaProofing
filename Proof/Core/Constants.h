//
//  Core/Constants.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

namespace Types {
    struct Kind {};
    struct Bool : public Kind {};
};

namespace Meta {
    struct True  : public Types::Bool {
        using type = True;
        static const char * const val() { return "T"; }
    };
    struct False : public Types::Bool {
        using type = False;
        static const char * const val() { return "F"; }
    };
}

namespace {
    template <typename A>
    struct is_bool_impl {
        using type = Meta::False;
    };
    
    template <>
    struct is_bool_impl<Meta::True> {
        using type = Meta::True;
    };

    template <>
    struct is_bool_impl<Meta::False> {
        using type = Meta::True;
    };
};

template <typename A>
using IsBool = typename is_bool_impl<A>::type;