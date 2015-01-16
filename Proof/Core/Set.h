//
//  Set.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"

struct AbstractElementType : public type_ {};
#define Element(name) struct name : public AbstractElementType { static const char * const val() { return #name; } };

struct SetType : public type_ {};

template <typename ... As>
struct Set : SetType {
    using type = MakeUnique<As ...>;
};

namespace {
    template <typename ... As>
    struct make_set_impl {
        using type = Reduction<make_set_impl<MakeUnique<As ...>>>;
    };

    template <typename ... As>
    struct make_set_impl<TypeHolder<As ...>> {
        using type = Set<As ...>;
    };
};

template <typename ... As>
Function(X->...->X->Set) MakeSet = Reduction<make_set_impl<As ...>>;

Type(Set) EmptySet = Set<>;

#pragma mark Map
/**
 *  f: A → B
 *  A: Set
 *  f(A) = {f(a) | a ∈ A}
 */

namespace {
    template <template <typename> class F, typename ... As>
    struct map_impl;
    
    template <template <typename> class F, typename ... As>
    struct map_impl<F, Set<As ...>> {
        Type(Set) type = Set<F<As> ...>;
    };
};

template <template <typename> class F, typename S>
Function(Function->Set->Set) Map = Reduction<map_impl<F, S>>;

#pragma mark Reduce
/**
 *  f: (A, A) → A
 *  init: A
 *  A: Set
 *  f(a, f(b, f(..., init))) (a, b, ... ∈ A)
 */

namespace {
    template <template <typename, typename> class F, typename ... As>
    struct reduce_impl;

    template <template <typename, typename> class F, typename Init, typename A, typename ... As>
    struct reduce_impl<F, Init, Set<A, As ...>> {
        Type(Value) type = Reduction<reduce_impl<F, F<Init, A>, Set<As ...>>>;
    };

    template <template <typename, typename> class F, typename Init>
    struct reduce_impl<F, Init, Set<>> {
        Type(Value) type = Init;
    };
};

template <template <typename, typename> class F, typename Init, typename A>
Function(Function->Value->Set) Reduce = Reduction<reduce_impl<F, Init, A>>;

#pragma mark In
/**
 *  a: element
 *  A: Set
 *  a ∈ A = True if a ∈ A otherwise False
 */

namespace {
    template <typename X, typename A>
    struct in_impl;

    template <typename X, typename ... As>
    struct in_impl<X, Set<As ...>> {
        template <typename Y>
        using eq_X = Meta::Equal<X, Y>;
        Type(Bool) type = Reduce<Meta::Or, False, Map<eq_X, Set<As ...>>>;
    };
};

template <typename X, typename A>
Function(X->Set->Bool) In = Reduction<in_impl<X, A>>;

#pragma mark Contain
/**
 *  A: Set
 *  B: Set
 *  A ⊂ B = True if ∀x, x ∈ B, otherwise False
 */

namespace {
    template <typename A, typename B>
    struct contain_impl;
    
    template <typename ... As, typename ... Bs>
    struct contain_impl<Set<As ...>, Set<Bs ...>> {
        template <typename B>
        using in_map = In<B, Set<Bs ...>>;
        Type(Bool) type = Reduce<Meta::And, True, Map<in_map, Set<As ...>>>;
    };
};

template <typename A, typename B>
Function(Set->Set->Bool) Contain = Reduction<contain_impl<A, B>>;

#pragma mark Union
/**
 *  A: Set
 *  B: Set
 *  A ∪ B = {a | a ∈ A ∨ a ∈ B}
 */

namespace {
    template <typename ...>
    struct union_impl;

    template <typename ... As, typename ... Bs>
    struct union_impl<Set<As ...>, Set<Bs ...>> {
        Type(Set) type = MakeSet<As ..., Bs ...>;
    };
};

template <typename A, typename B>
Function(Set->Set->Set) Union = Reduction<union_impl<A, B>>;

#pragma mark Intersection
/**
 *  A: Set
 *  B: Set
 *  A ∩ B = {a | a ∈ A ∧ a ∈ B}
 */

namespace {
    template <typename ...>
    struct intersection_impl;

    template <typename ... As>
    struct intersection_impl<EmptySet, Set<As ...>> {
        Type(Set) type = EmptySet;
    };

    template <typename ... As>
    struct intersection_impl<Set<As ...>, EmptySet> {
        Type(Set) type = EmptySet;
    };

    template <typename A, typename ... As, typename ... Bs>
    struct intersection_impl<Set<A, As ...>, Set<Bs ...>> {
        Type(Set) type = Union<Meta::If<In<A, Set<Bs ...>>, Set<A>, EmptySet>, Reduction<intersection_impl<Set<As ...>, Set<Bs ...>>>>;
    };
};

template <typename A, typename B>
Function(Set->Set->Set) Intersection = Reduction<intersection_impl<A, B>>;

#pragma mark Product
/**
 *  A: Set
 *  B: Set
 *  A × B = {(a, b) | a ∈ A, b ∈ B}
 */

namespace {
    template <typename ...>
    struct product_impl;

    template <typename A, typename ... As, typename ... Bs>
    struct product_impl<Set<A, As ...>, Set<Bs ...>> {
        template <typename B>
        Function(X->X->Tuple) product_mod = Tuple<A, B>;
        
        Type(Set) type = Union<Map<product_mod, Set<Bs ...>>, Reduction<product_impl<Set<As ...>, Set<Bs ...>>>>;
    };

    template <typename ... As>
    struct product_impl<EmptySet, Set<As ...>> {
        Type(Set) type = EmptySet;
    };
};

template <typename A, typename B>
Function(Set->Set->Set) Product = Reduction<product_impl<A, B>>;

namespace {
    template <typename, typename>
    struct equal_set_impl;
    
    template <typename ... As, typename ... Bs>
    struct equal_set_impl<Set<As ...>, Set<Bs ...>> {
        Type(Bool) type = Meta::And<Contain<Set<As ...>, Set<Bs ...>>, Contain<Set<Bs ...>, Set<As ...>>>;
    };
};

template <typename A, typename B>
using EqualSet = Reduction<equal_set_impl<A, B>>;