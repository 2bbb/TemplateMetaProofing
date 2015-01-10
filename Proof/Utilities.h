//
//  Utilities.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/04.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Constants.h"

#define GetType(name, ...) typename __VA_ARGS__::name
#define Reduction(...) GetType(type, __VA_ARGS__)
#define Eval(...) GetType(value, __VA_ARGS__)

#define Type(...) using

namespace TemplateDetail {
    template <typename A, typename B>
    struct Equal {
        Type(Bool) type = False;
    };

    template <typename A>
    struct Equal<A, A> {
        Type(Bool) type = True;
    };
    
    template <typename, typename>
    struct And {
        Type(Bool) type = False;
    };
    
    template <>
    struct And<True, True> {
        Type(Bool) type = False;
    };

    template <typename, typename>
    struct Or {
        Type(Bool) type = True;
    };
    
    template <>
    struct Or<False, False> {
        Type(Bool) type = False;
    };
};
template <template <typename ...> class TemplateClass, typename ... As>
struct Rewrap {
    using type = TemplateClass<As ...>;
};

template <typename ...>
struct TypeHolder {};

struct Null {};

template <typename A, typename B>
struct Pair {};

template <typename ...>
struct Flatten;

template <typename A>
struct Flatten<A> {
    using type = TypeHolder<A>;
};

template <typename A, typename B>
struct Flatten<Pair<A, B>> {
    using type = Reduction(Flatten<B, TypeHolder<A>>);
};

template <typename A, typename ... Bs>
struct Flatten<A, TypeHolder<Bs ...>> {
    using type = TypeHolder<Bs ..., A>;
};

template <typename A, typename B, typename ... Bs>
struct Flatten<Pair<A, B>, TypeHolder<Bs ...>> {
    using type = Reduction(Flatten<B, TypeHolder<Bs ..., A>>);
};

template <>
struct Flatten<Null> {
    using type = TypeHolder<>;
};

namespace {
    template <typename ...>
    struct make_unique_impl;

    template <typename A>
    struct make_unique_impl<A> {
        using type = A;
    };

    template <typename A>
    struct make_unique_impl<A, TypeHolder<>, TypeHolder<>> {
        using type = A;
    };

    template <typename A, typename ... Bs>
    struct make_unique_impl<A, Bs ...> {
        using type = Reduction(make_unique_impl<A, TypeHolder<Bs ...>, TypeHolder<>>);
    };

    template <typename A, typename ... Bs, typename ... Cs>
    struct make_unique_impl<A, TypeHolder<A, Bs ...>, TypeHolder<Cs ...>> {
        using type = Reduction(make_unique_impl<A, TypeHolder<Bs ...>, TypeHolder<Cs ...>>);
    };

    template <typename A, typename B, typename ... Cs, typename ... Ds>
    struct make_unique_impl<A, TypeHolder<B, Cs ...>, TypeHolder<Ds ...>> {
        using type = Reduction(make_unique_impl<A, TypeHolder<Cs ...>, TypeHolder<Ds ..., B>>);
    };

    template <typename A, typename ... Bs>
    struct make_unique_impl<A, TypeHolder<>, TypeHolder<Bs ...>> {
        using type = Pair<A, Reduction(make_unique_impl<Bs ...>)>;
    };

    template <>
    struct make_unique_impl<> {
        using type = Null;
    };
};

template <typename ... As>
struct MakeUnique {
    using type = Reduction(Flatten<Reduction(make_unique_impl<As ...>)>);
};

template <typename Condition, typename Then, typename Else> struct If;

template <typename Then, typename Else>
struct If<True, Then, Else> {
    Type(Value) type = Then;
};

template <typename Then, typename Else>
struct If<False, Then, Else> {
    Type(Value) type = Else;
};
