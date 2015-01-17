//
//  Core/Nat.h
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
    using AreNats = Reduce<Meta::And, Meta::True, Map<IsNat, Set<Ms ...>>>;
    
    /**
     *  Zero
     *  @return 0
     */
    struct Zero : public NatType {};
    
    /**
     *  Succesor
     *
     *  @param M <b>requires</b> NatType
     *
     *  @return Suc(M) Succesor of M
     */
    template <typename M, requires(AreNats<M>)>
    struct Suc : public Requires(NatType) {};
    
    /**
     *  Addition of Nat
     *
     *  @param M <b>requires</b> NatType
     *  @param N <b>requires</b> NatType
     *
     *  @return M+N NatType
     */
    template <typename M, typename N, requires(AreNats<M, N>)>
    struct Add : public Requires(NatType) {};
    
    /**
     *  Multiply of Nat
     *
     *  @param M <b>requires</b> NatType
     *  @param N <b>requires</b> NatType
     *
     *  @return M*N NatType
     */
    template <typename M, typename N, requires(AreNats<M, N>)>
    struct Mul : public Requires(NatType) {};
};

namespace Axiom {
    using namespace Nat;
    class PA {
    public:
        /**
         *  m = n -> s(m) = s(n)
         *
         *  @param M <b>requires</b> NatType
         *  @param N <b>requires</b> NatType
         *  @param As... Array of Propositions <b>requires</b> PropositionType
         *  @param Formula<Eq<M,N>,Assumptions<As...>>
         *
         *  @return Formula<Eq<Nat::Suc<M>,Nat::Suc<N>>,Assumptions<As...>>
         */
        template <typename M, typename N, typename ... As, requires(Meta::And<AreNats<M, N>, AreProps<As ...>>)>
        static auto eq_suc(const Formula<Eq<M, N>, Assumptions<As ...>> &)
        -> Formula<Eq<Nat::Suc<M>, Nat::Suc<N>>, Assumptions<As ...>>
        {
            fulfill(AreNats<M, N>);
            return Formula<Eq<Nat::Suc<M>, Nat::Suc<N>>, Assumptions<As ...>>();
        }
        
        // add(m, 0) = m
        template <typename M, requires(AreNats<M>)>
        static auto add_m_0_is_m()
        -> Formula<Eq<Nat::Add<M, Nat::Zero>, M>, Assumptions<>>
        {
            fulfill(AreNats<M>);
            return Formula<Eq<Nat::Add<M, Nat::Zero>, M>, Assumptions<>>();
        }

        // add(m, s(n)) = s(add(m, n))
        template <typename M, typename N, requires(AreNats<M, N>)>
        static auto add_m_sn_is_s_add_m_n()
        -> Formula<Eq<Nat::Add<M, Nat::Suc<N>>, Nat::Suc<Nat::Add<M, N>>>, Assumptions<>>
        {
            fulfill(AreNats<M, N>);
            return Formula<Eq<Nat::Add<M, Nat::Suc<N>>, Nat::Suc<Nat::Add<M, N>>>, Assumptions<>>();
        }

        // mul(m, 0) = 0
        template <typename M, requires(AreNats<M>)>
        static auto mul_m_0_is_0()
        -> Formula<Eq<Nat::Mul<M, Nat::Zero>, Nat::Zero>, Assumptions<>>
        {
            fulfill(AreNats<M>);
            return Formula<Eq<Nat::Mul<M, Nat::Zero>, Nat::Zero>, Assumptions<>>();
        }
        
        // mul(m, s(n)) = add(m, mul(m, n))
        template <typename M, typename N, requires(AreNats<M, N>)>
        static auto mul_m_sn_is_add_m_mul_m_n()
        -> Formula<Eq<Nat::Mul<M, Nat::Suc<N>>, Nat::Add<M, Nat::Mul<M, N>>>, Assumptions<>>
        {
            fulfill(AreNats<M, N>);
            return Formula<Eq<Nat::Mul<M, Nat::Suc<N>>, Nat::Add<M, Nat::Mul<M, N>>>, Assumptions<>>();
        }
        
        // induction
        // P(0) => P(m) => P(s(m)) => ∀m.P(m)
        template <typename X, typename Prop, typename K, typename ... As, typename ... Bs, requires(Meta::And<AreNats<X, K>, AreProps<Prop, As ..., Bs ...>>)>
        static auto induction(const Formula<Substitute<Prop, X, Nat::Zero>, Assumptions<As ...>> &,
                              const Formula<Imp<Substitute<Prop, X, K>, Substitute<Prop, X, Nat::Suc<K>>>, Assumptions<Bs ...>> &)
        -> Formula<ForAll<X, Prop>, MakeAssumptions<As ..., Bs ...>>
        {
            fulfill(AreNats<X, K>, AreProps<Prop, As ..., Bs ...>);
            return Formula<ForAll<X, Prop>, MakeAssumptions<As ..., Bs ...>>();
        }
    };
};

#define NaturalNumber(name) struct name : public Nat::NatType { static const char * const val() { return #name; } };
