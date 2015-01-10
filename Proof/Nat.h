//
//  ofx1plus1is2Nat.h
//
//  Created by ISHII 2bit on 2014/12/29.
//
//

#pragma once

#include "Utilities.h"
#include "Eq.h"

namespace Nat {
    class Zero {};
    
    template <typename S>
    class Suc {};
    
    template <typename S, typename T>
    class Add {};
    
    template <typename S, typename T>
    class Mul {};
};

namespace Axiom {
    class PA {
    public:
        // m = n -> s(m) = s(n)
        template <typename S, typename T>
        static Eq<Nat::Suc<S>, Nat::Suc<T>> suc(const Eq<S, T> &) { return Eq<Nat::Suc<S>, Nat::Suc<T>>(); };
        
        template <typename S, typename T>
        static Formula<Eq<Nat::Suc<S>, Nat::Suc<T>>, Assumptions<Eq<S, T>>> eq_suc() { return Formula<Eq<Nat::Suc<S>, Nat::Suc<T>>, Assumptions<Eq<S, T>>>(); };
        
        // add(m, 0) = m
        template <typename S>
        static Eq<Nat::Add<S, Nat::Zero>, S> add_m_0_is_m() { return Eq<Nat::Add<S, Nat::Zero>, S>(); };
        
        template <typename S>
        static Formula<Eq<Nat::Add<S, Nat::Zero>, S>, Assumptions<>> add_0() { return Formula<Eq<Nat::Add<S, Nat::Zero>, S>, Assumptions<>>(); };

        // add(m, s(n)) = s(add(m, n))
        template <typename S, typename T>
        static Eq<Nat::Add<S, Nat::Suc<T>>, Nat::Suc<Nat::Add<S, T>>> add_m_sn_is_s_add_m_n() { return Eq<Nat::Add<S, Nat::Suc<T>>, Nat::Suc<Nat::Add<S, T>>>(); };
        
        // mul(m, 0) = 0
        template <typename S>
        static Eq<Nat::Mul<S, Nat::Zero>, Nat::Zero> mul_m_0_is_0() { return Eq<Nat::Mul<S, Nat::Zero>, Nat::Zero>(); };
        
        // ,ul(m, s(n)) = add(m, mul(m, n))
        template <typename S, typename T>
        static Eq<Nat::Mul<S, Nat::Suc<T>>, Nat::Add<S, Nat::Mul<S, T>>> mul_m_sn_is_add_m_mul_m_n() { return Eq<Nat::Mul<S, Nat::Suc<T>>, Nat::Add<S, Nat::Mul<S, T>>>(); };
    };
};