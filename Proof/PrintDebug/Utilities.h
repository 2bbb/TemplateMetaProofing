//
//  PrintDebugUtilities.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/09.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include <iostream>

#include "PrintDebug/Set.h"
#include "PrintDebug/Assumptions.h"
#include "PrintDebug/Formula.h"
#include "PrintDebug/PL.h"
#include "PrintDebug/FOL.h"
#include "PrintDebug/Eq.h"
#include "PrintDebug/Nat.h"

namespace {
    template <typename T, typename NameGetter>
    class has_member_impl {
        typedef char matched_return_type;
        typedef long unmatched_return_type;
        
        template <typename C>
        static matched_return_type f(typename NameGetter::template get<C> *);
        
        template <typename>
        static unmatched_return_type f(...);
    public:
        static const bool value = (sizeof(f<T>(0)) == sizeof(matched_return_type));
    };
    
    template <typename T, typename NameGetter>
    struct has_member : std::integral_constant<bool, has_member_impl<T, NameGetter>::value> {};
    
    struct check_has_val {
        template <typename T, const char * const (*)() = &T::val>
        struct get {};
    };
    
    template <typename T>
    struct has_val : has_member<T, check_has_val> {};
}

template <typename P>
Reduction<std::enable_if<has_val<P>::value, std::ostream &>> operator<<(std::ostream &os, const P &) {
    os << P::val();
    return os;
}

template <typename A, typename B, typename ... Bs>
std::ostream &operator<<(std::ostream &os, const TypeHolder<A, B, Bs ...> &) {
    os << A() << ", " << TypeHolder<B, Bs ...>();
    return os;
}

template <typename A>
std::ostream &operator<<(std::ostream &os, const TypeHolder<A> &) {
    os << A();
    return os;
}

std::ostream &operator<<(std::ostream &os, const TypeHolder<> &) {
    return os;
}

template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const Pair<A, B> &) {
    os << "(" << A() << ", " << B() << ")";
    return os;
}

template <typename ... As>
std::ostream &operator<<(std::ostream &os, const Tuple<As ...> &) {
    os << "(" << TypeHolder<As ...>() << ")";
    return os;
}