//
//  PrintDebug/Utilities.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/09.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include <iostream>

#include "Core/Includes.h"

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
        template <typename C>
        static Meta::True f(typename NameGetter::template get<C> *);
        
        template <typename>
        static Meta::False f(...);
    public:
        using type = decltype(f<T>(0));
    };
    
    struct check_has_val {
        template <typename T, const char * const (*)() = &T::val>
        struct get {};
    };
    
    template <typename T>
    using HasVal = Reduction<has_member_impl<T, check_has_val>>;
};

//// Why does this run by wrapping by the `namespace Types`?
//namespace Types {
//    template <typename P>
//    Meta::If<HasVal<P>, std::ostream &> operator<<(std::ostream &os, const P &) {
//        os << P::val();
//        return os;
//    }
//};

template <typename P>
std::ostream &operator<<(std::ostream &os, const Meta::If<HasVal<P>, P> &) {
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