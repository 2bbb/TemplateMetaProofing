//
//  Core/FOL.h
//  Proof
//
//  Created by ISHII 2bit on 2014/12/31.
//  Copyright (c) 2014年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"
#include "Core/PL.h"

namespace {
    template<typename P, typename X, typename V, typename = AreProps<P>>
    struct substitute_impl {
        using type = P;
    };
    
    template<typename X, typename V>
    struct substitute_impl<X, X, V> {
        using type = V;
    };
    
    template <template <typename ...> class Prop, typename ... Ts, typename X, typename V>
    struct substitute_impl<Prop<Ts ...>, X, V> {
        using type = Prop<Reduction<substitute_impl<Ts, X, V>> ...>;
    };
};

template<typename P, typename X, typename V>
using Substitute = Reduction<substitute_impl<P, X, V>>;

template <typename T>
struct NewType {
    using type = NewType;
};

template <typename X, typename Prop> struct ForAll : public PropositionType {};
template <typename X, typename Prop> struct Exists : public PropositionType {};

namespace {
    template <typename X, typename P>
    struct is_free_impl {
        using type = Meta::True;
    };

    template <typename X, typename Prop>
    struct is_free_impl<X, ForAll<X, Prop>> {
        using type = Meta::False;
    };

    template <typename X, typename Prop>
    struct is_free_impl<X, Exists<X, Prop>> {
        using type = Meta::False;
    };
    
    template <typename X, template <typename ...> class Prop, typename ... Ts>
    struct is_free_impl<X, Prop<Ts ...>> {
        template <typename T>
        using is_free_impl_mod = is_free_impl<X, T>;
        using type = Reduce<Meta::And, Meta::True, Map<is_free_impl_mod, Set<Ts ...>>>;
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

/**
 *  check variable is free
 *  @param X Variable
 *  @param P Proposition
 *  @return <b>Meta::True</b> if X is free in P else <b>False</b>
 */

template <typename X, typename P>
using IsFree = is_free_impl<X, P>;

namespace Axiom {
    class FOL {
        template <typename X, typename Y, typename Prop, typename ... As, typename B = Enable<IsFree<Y, Prop>>>
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
        
        template <typename ResultProp, typename X, typename A, typename Prop, typename ... As, typename ... Bs, typename Cs = Enable<Reduce<Meta::And, Meta::True, Set<IsFree<A, Bs> ...>>>>
        auto existsE(const Formula<Exists<X, Prop>, Assumptions<As ...>> &,
                     const Formula<ResultProp, Assumptions<Substitute<Prop, X, A>, Bs ...>> &)
        -> Formula<ResultProp, MakeAssumptions<As ..., Bs ...>> {
            return Formula<ResultProp, MakeAssumptions<As ..., Bs ...>>();
        }
    };
};

struct VariableType : public type_ {};

#define Variable(name) struct name : public VariableType { static const char * const val() { return #name; } };

#define AnonymousVariable() struct {}