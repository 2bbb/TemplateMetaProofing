//
//  Set.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Utilities.h"
#include "Constants.h"

template <typename ... As>
struct Set {
    using type = Reduction(MakeUnique<As ...>);
};

template <typename ... As>
struct MakeSet;

template <typename ... As>
struct MakeSet<TypeHolder<As ...>> {
    using type = Set<As ...>;
};


Type(Set) EmptySet = Set<>;

#pragma mark Map
/**
 *  f: A → B
 *  A: Set
 *  f(A) = {f(a) | a ∈ A}
 */

template <template <typename> class F, typename ... As>
struct Map;

template <template <typename> class F, typename ... As>
struct Map<F, Set<As ...>> {
    template <template <typename> class G, typename ...>
    struct map_impl;
    
    template <template <typename> class G, typename A, typename ... Bs>
    struct map_impl<G, TypeHolder<A, Bs ...>> {
        using type = Pair<F<A>, Reduction(map_impl<G, TypeHolder<Bs ...>>)>;
    };
    
    template <template <typename> class G, typename A>
    struct map_impl<G, TypeHolder<A>> {
        using type = G<A>;
    };
    
    Type(Set) type = Reduction(MakeSet<Reduction(Flatten<Reduction(map_impl<F, TypeHolder<As ...>>)>)>);
};

#pragma mark Reduce
/**
 *  f: (A, A) → A
 *  init: A
 *  A: Set
 *  f(a, f(b, f(..., init))) (a, b, ... ∈ A)
 */

template <template <typename, typename> class F, typename ... As>
struct Reduce;

template <template <typename, typename> class F, typename Init, typename A, typename ... As>
struct Reduce<F, Init, Set<A, As ...>> {
    Type(Value) type = Reduction(Reduce<F, Reduction(F<Init, A>), Set<As ...>>);
};

template <template <typename, typename> class F, typename Init>
struct Reduce<F, Init> {
    Type(Value) type = Init;
};

template <template <typename, typename> class F, typename Init>
struct Reduce<F, Init, Set<>> {
    Type(Value) type = Init;
};

#pragma mark In
/**
 *  a: element
 *  A: Set
 *  a in A = True if a ∈ A otherwise False
 */

template <typename ...>
struct In;

template <typename A, typename B, typename ... As>
struct In<A, Set<B, As ...>> {
    Type(Bool) type = Reduction(In<A, Set<As ...>>);
};

template <typename A, typename ... As>
struct In<A, Set<A, As ...>> {
    Type(Bool) type = True;
};

template <typename A>
struct In<A, EmptySet> {
    Type(Bool) type = False;
};

#pragma mark Union
/**
 *  A: Set
 *  B: Set
 *  A ∪ B = {a | a ∈ A ∨ a ∈ B}
 */

template <typename ...>
struct Union;

template <typename ... As, typename ... Bs>
struct Union<Set<As ...>, Set<Bs ...>> {
    Type(Set) type = Set<As ..., Bs ...>;
};

#pragma mark Intersection
/**
 *  A: Set
 *  B: Set
 *  A ∩ B = {a | a ∈ A ∧ a ∈ B}
 */

template <typename ...>
struct Intersection;

template <typename ... As>
struct Intersection<EmptySet, Set<As ...>> {
    Type(Set) type = EmptySet;
};

template <typename ... As>
struct Intersection<Set<As ...>, EmptySet> {
    Type(Set) type = EmptySet;
};

template <typename A, typename ... As, typename ... Bs>
struct Intersection<Set<A, As ...>, Set<Bs ...>> {
    template <typename B>
    Type(Function) equal_A = Reduction(TemplateDetail::Equal<A, B>);
    
    Type(Set)      mapped_values = Reduction(Map<equal_A, Set<Bs ...>>);
    Type(Bool)     is_A_in_Bs = Reduction(Reduce<TemplateDetail::Or, False, mapped_values>);
    
    Type(Set) type = Reduction(Union<Reduction(If<is_A_in_Bs, Set<A>, EmptySet>), Reduction(Intersection<Set<As ...>, Set<Bs ...>>)>);
};

#pragma mark Product
/**
 *  A: Set
 *  B: Set
 *  A × B = {(a, b) | a ∈ A, b ∈ B}
 */

template <typename ...>
struct Product;

template <typename A, typename ... As, typename ... Bs>
struct Product<Set<A, As ...>, Set<Bs ...>> {
    template <typename B>
    Type(Function) product_mod = Pair<A, B>;
    
    Type(Set) type = Reduction(Union<Reduction(Map<product_mod, Set<Bs ...>>), Reduction(Product<Set<As ...>, Set<Bs ...>>)>);
};

template <typename ... As>
struct Product<EmptySet, Set<As ...>> {
    Type(Set) type = EmptySet;
};