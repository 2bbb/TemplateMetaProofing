//
//  FOL.h
//  Proof
//
//  Created by ISHII 2bit on 2014/12/31.
//  Copyright (c) 2014年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"
#include "Core/PL.h"

template<typename P, typename X, typename V>
struct Substitute {
    using type = P;
};

template<typename X, typename V>
struct Substitute<X, X, V> {
    using type = V;
};

template <template <typename ...> class Prop, typename ... Ts, typename X, typename V>
struct Substitute<Prop<Ts ...>, X, V> {
    using type = Reduction<Prop<Substitute<Ts ..., X, V>>>;
};

template <typename T>
struct NewType {
    using type = NewType;
};

template <typename X, typename Prop> class ForAll {};
template <typename X, typename Prop> class Exists {};

namespace {
    template <typename X, typename P>
    struct is_free_impl {
        using type = True;
    };

    template <typename X, typename Prop>
    struct is_free_impl<X, ForAll<X, Prop>> {
        using type = False;
    };

    template <typename X, typename Prop>
    struct is_free_impl<X, Exists<X, Prop>> {
        using type = False;
    };
    
    template <typename X, template <typename ...> class Prop, typename ... Ts>
    struct is_free_impl<X, Prop<Ts ...>> {
        template <typename T>
        using is_free_impl_mod = is_free_impl<X, T>;
        using type = Reduce<Meta::And, True, Map<is_free_impl_mod, Set<Ts ...>>>;
    };
    
    template <typename X, typename Y, template <typename ...> class Prop, typename ... Ts>
    struct is_free_impl<X, ForAll<Y, Prop<Ts ...>>> {
        using type = Reduction<is_free_impl<X, Prop<Ts ...>>>;
    };
    
    template <typename X, typename Y, template <typename ...> class Prop, typename ... Ts>
    struct is_free_impl<X, Exists<Y, Prop<Ts ...>>> {
        using type = Reduction<is_free_impl<X, Prop<Ts ...>>>;
    };
};

template <typename X, typename P>
using IsFree = is_free_impl<X, P>;

namespace Axiom {
    class FOL {
        template <typename X, typename Y, typename Prop, typename ... As>
        auto forAllI(const Formula<Substitute<Prop, X, Y>, Assumptions<As ...>> &)
        -> Formula<ForAll<X, Prop>, Assumptions<As ...>> {
            return Formula<ForAll<X, Prop>, Assumptions<As ...>>();
        }
        
        template <typename X, typename V, typename Prop, typename ... As>
        auto forAllE(const Formula<ForAll<X, Prop>, Assumptions<As ...>> &)
        -> Formula<Substitute<Prop, X, V>, Assumptions<As ...>> {
            return Formula<Substitute<Prop, X, V>, Assumptions<As ...>>();
        }
        
        template <typename X, typename T, typename Prop, typename ... As>
        auto existsI(const Formula<Substitute<Prop, X, T>, Assumptions<As ...>> &)
        -> Formula<Exists<X, Prop>, Assumptions<As ...>> {
            return Formula<Exists<X, Prop>, Assumptions<As ...>>();
        }
        
        template <typename ResultProp, typename X, typename A, typename Prop, typename ... As, typename ... Bs>
        auto existsE(const Formula<Exists<X, Prop>, Assumptions<As ...>> &,
                     const Formula<ResultProp, Assumptions<Substitute<Prop, X, A>, Bs ...>> &)
        -> Formula<ResultProp, MakeAssumptions<As ..., Bs ...>> {
            return Formula<ResultProp, MakeAssumptions<As ..., Bs ...>>();
        }
    };
};

struct _variable {};

#define Variable(name) struct name : public _variable { static const char * const val() { return #name; } };

#define AnonymousVariable() struct {}