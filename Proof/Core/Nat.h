//
//  Nat.h
//  Proof
//
//  Created by ISHII 2bit on 2014/12/29.
//  Copyright (c) 2014年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"
#include "Core/Eq.h"

namespace Nat {
    struct NatType : public type_ {};
    
    template <typename M>
    using IsNat = HasType<M, NatType>;
    
    template <typename ... Ms>
    using AreNat = Reduce<Meta::And, True, Map<IsNat, Set<Ms ...>>>;
    
    struct Zero : public NatType {};
    
    template <typename M, typename Validate = Enable<Nat::AreNat<M>>>
    struct Suc : public NatType {};
    
    template <typename M, typename N, typename Validate = Enable<Nat::AreNat<M, N>>>
    struct Add : public NatType {};
    
    template <typename M, typename N, typename Validate = Enable<Nat::AreNat<M, N>>>
    struct Mul : public NatType {};
};

namespace Axiom {
    class PA {
    public:
        // m = n -> s(m) = s(n)
        template <typename M, typename N, typename ... As, typename Validate = Enable<Nat::AreNat<M, N>>>
        static auto eq_suc(const Formula<Eq<M, N>, Assumptions<As ...>> &)
        -> Formula<Eq<Nat::Suc<M>, Nat::Suc<N>>, Assumptions<As ...>> {
            return Formula<Eq<Nat::Suc<M>, Nat::Suc<N>>, Assumptions<As ...>>();
        }
        
        // add(m, 0) = m
        template <typename M, typename Validate = Enable<Nat::AreNat<M>>>
        static auto add_m_0_is_m()
        -> Formula<Eq<Nat::Add<M, Nat::Zero>, M>, Assumptions<>> {
            return Formula<Eq<Nat::Add<M, Nat::Zero>, M>, Assumptions<>>();
        }

        // add(m, s(n)) = s(add(m, n))
        template <typename M, typename N, typename Validate = Enable<Nat::AreNat<M, N>>>
        static auto add_m_sn_is_s_add_m_n()
        -> Formula<Eq<Nat::Add<M, Nat::Suc<N>>, Nat::Suc<Nat::Add<M, N>>>, Assumptions<>> {
            return Formula<Eq<Nat::Add<M, Nat::Suc<N>>, Nat::Suc<Nat::Add<M, N>>>, Assumptions<>>();
        }

        // mul(m, 0) = 0
        template <typename M, typename Validate = Enable<Nat::AreNat<M>>>
        static auto mul_m_0_is_0()
        -> Formula<Eq<Nat::Mul<M, Nat::Zero>, Nat::Zero>, Assumptions<>> {
            return Formula<Eq<Nat::Mul<M, Nat::Zero>, Nat::Zero>, Assumptions<>>();
        }
        
        // mul(m, s(n)) = add(m, mul(m, n))
        template <typename M, typename N, typename Validate = Enable<Nat::AreNat<M, N>>>
        static auto mul_m_sn_is_add_m_mul_m_n()
        -> Formula<Eq<Nat::Mul<M, Nat::Suc<N>>, Nat::Add<M, Nat::Mul<M, N>>>, Assumptions<>> {
            return Formula<Eq<Nat::Mul<M, Nat::Suc<N>>, Nat::Add<M, Nat::Mul<M, N>>>, Assumptions<>>();
        }
        
        // induction
        // P(0) => P(m) => P(s(m)) => ∀m.P(m)
        template <typename X, typename Prop, typename K, typename ... As, typename ... Bs, typename Validate = Enable<Nat::AreNat<X, K>>>
        static auto induction(const Formula<Substitute<Prop, X, Nat::Zero>, Assumptions<As ...>> &,
                              const Formula<Imp<Substitute<Prop, X, K>, Substitute<Prop, X, Nat::Suc<K>>>, Assumptions<Bs ...>> &)
        -> Formula<ForAll<X, Prop>, MakeAssumptions<As ..., Bs ...>> {
            return Formula<ForAll<X, Prop>, MakeAssumptions<As ..., Bs ...>>();
        }
    };
};

#define NaturalNumber(name) struct name : public Nat::NatType { static const char * const val() { return #name; } };
