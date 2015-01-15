//
//  ofx1plus1is2Nat.h
//
//  Created by ISHII 2bit on 2014/12/29.
//
//

#pragma once

#include "Core/Utilities.h"
#include "Core/Eq.h"

namespace Nat {
    class Zero {};
    
    template <typename>
    class Suc {};
    
    template <typename, typename>
    class Add {};
    
    template <typename, typename>
    class Mul {};
    
    namespace {
        template <typename>
        struct is_nat_impl {
            using type = False;
        };
        
        template <>
        struct is_nat_impl<Zero> {
            using type = True;
        };
        
        template <typename M>
        struct is_nat_impl<Suc<M>> {
            using type = Reduction<is_nat_impl<M>>;
        };
    };
    
    template <typename M>
    using IsNat = Reduction<is_nat_impl<M>>;
};

namespace Axiom {
    namespace {
        template <typename X, typename Prop, typename ... As>
        struct ind_step_impl {
            template <typename N>
            using type = Formula<Imp<Substitute<Prop, X, N>, Substitute<Prop, X, Nat::Suc<N>>>, Assumptions<As ...>>;
        };
        
        template <typename X, typename Prop, typename ... As>
        using IndStep = Reduction<ind_step_impl<X, Prop, As ...>>;
    };
    class PA {
    public:
        // m = n -> s(m) = s(n)
        template <typename M, typename N, typename ... As>
        static auto eq_suc(const Formula<Eq<M, N>, Assumptions<As ...>> &)
        -> Formula<Eq<Nat::Suc<M>, Nat::Suc<N>>, Assumptions<As ...>> {
            return Formula<Eq<Nat::Suc<M>, Nat::Suc<N>>, Assumptions<As ...>>();
        }
        
        // add(m, 0) = m
        template <typename M>
        static auto add_m_0_is_m()
        -> Formula<Eq<Nat::Add<M, Nat::Zero>, M>, Assumptions<>> {
            return Formula<Eq<Nat::Add<M, Nat::Zero>, M>, Assumptions<>>();
        }

        // add(m, s(n)) = s(add(m, n))
        template <typename M, typename N>
        static auto add_m_sn_is_s_add_m_n()
        -> Formula<Eq<Nat::Add<M, Nat::Suc<N>>, Nat::Suc<Nat::Add<M, N>>>, Assumptions<>> {
            return Formula<Eq<Nat::Add<M, Nat::Suc<N>>, Nat::Suc<Nat::Add<M, N>>>, Assumptions<>>();
        }

        // mul(m, 0) = 0
        template <typename N>
        static auto mul_m_0_is_0()
        -> Formula<Eq<Nat::Mul<N, Nat::Zero>, Nat::Zero>, Assumptions<>> {
            return Formula<Eq<Nat::Mul<N, Nat::Zero>, Nat::Zero>, Assumptions<>>();
        }
        
        // mul(m, s(n)) = add(m, mul(m, n))
        template <typename M, typename N>
        static auto mul_m_sn_is_add_m_mul_m_n()
        -> Formula<Eq<Nat::Mul<M, Nat::Suc<N>>, Nat::Add<M, Nat::Mul<M, N>>>, Assumptions<>> {
            return Formula<Eq<Nat::Mul<M, Nat::Suc<N>>, Nat::Add<M, Nat::Mul<M, N>>>, Assumptions<>>();
        }
        
        // induction
        // P(0) => P(m) => P(s(m)) => ∀m.P(m)
        template <typename X, typename Prop, typename K, typename ... As, typename ... Bs>
        static auto induction(const Formula<Substitute<Prop, X, Nat::Zero>, Assumptions<As ...>> &,
                              const Formula<Imp<Substitute<Prop, X, K>, Substitute<Prop, X, Nat::Suc<K>>>, Assumptions<Bs ...>> &)
        -> Formula<ForAll<X, Prop>, MakeAssumptions<As ..., Bs ...>> {
            return Formula<ForAll<X, Prop>, MakeAssumptions<As ..., Bs ...>>();
        }
    };
};