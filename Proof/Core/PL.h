//
//  PL.h
//  Proof
//
//  Created by ISHII 2bit on 2014/12/30.
//  Copyright (c) 2014年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"
#include "Core/Assumptions.h"
#include "Core/Formula.h"

struct PropositionType : public type_ {};
#define Proposition(name) struct name : public PropositionType { static const char * const val() { return #name; } };

template <typename M>
using IsProp = HasType<M, PropositionType>;

template <typename ... Ms>
using AreProps = Reduce<Meta::And, True, Map<IsProp, Set<Ms ...>>>;

template <typename P> class Not : public PropositionType {};
template <typename P, typename Q> class And : public PropositionType {};
template <typename P, typename Q> class Or  : public PropositionType {};
template <typename P, typename Q> class Imp : public PropositionType {};

namespace Axiom {
    class PL {
    public:
        // {} |- P --> P
        template <typename P, typename = AreProps<P>>
        static auto assume()
        -> Formula<P, Assumptions<P>>
        {
            return Formula<P, Assumptions<P>>();
        }
        
        // P, Gamma |- F --> Gamma |- -P
        template <typename P, typename ... Gamma, typename = AreProps<P>>
        static auto notI(const Formula<False, Assumptions<P, Gamma ...>> &)
        -> Formula<Not<P>, Assumptions<Gamma ...>>
        {
            return Formula<Not<P>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P + Delta |- -P --> Gamma, Delta |- False
        template <typename P, typename ... Gamma, typename ... Delta, typename = AreProps<P>>
        static auto notE(const Formula<P, Assumptions<Gamma ...>> &,
                         const Formula<Not<P>, Assumptions<Delta ...>> &)
        -> Formula<False, MakeAssumptions<Gamma ..., Delta ...>>
        {
            return Formula<False, MakeAssumptions<Gamma ..., Delta ...>>();
        }
        
        // Gamma |- P + Delta |- Q --> Gamma, Delta |- P /\ Q
        template <typename P, typename Q, typename ... Gamma, typename ... Delta, typename = AreProps<P, Q>>
        static auto andI(const Formula<P, Assumptions<Gamma ...>> &proof1,
                         const Formula<Q, Assumptions<Delta ...>> &proof2)
        -> Formula<And<P, Q>, MakeAssumptions<Gamma ..., Delta ...>>
        {
            return Formula<And<P, Q>, MakeAssumptions<Gamma ..., Delta ...>>();
        }
        
        // Gamma |- P /\ Q --> Gamma |- P
        template <typename P, typename Q, typename ... Gamma, typename = AreProps<P, Q>>
        static auto andEL(const Formula<And<P, Q>, Assumptions<Gamma ...>> &)
        -> Formula<P, Assumptions<Gamma ...>>
        {
            return Formula<P, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P /\ Q --> Gamma |- Q
        template <typename P, typename Q, typename ... Gamma, typename = AreProps<P, Q>>
        static auto andER(const Formula<And<P, Q>, Assumptions<Gamma ...>> &)
        -> Formula<Q, Assumptions<Gamma ...>>
        {
            return Formula<Q, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P --> Gamma |- P\/Q
        template <typename P, typename Q, typename ... Gamma, typename = AreProps<P, Q>>
        static auto orIL(const Formula<P, Assumptions<Gamma ...>> &)
        -> Formula<Or<P, Q>, Assumptions<Gamma ...>>
        {
            return Formula<Or<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- Q --> Gamma |- P\/Q
        template <typename P, typename Q, typename ... Gamma, typename = AreProps<P, Q>>
        static auto orIR(const Formula<Q, Assumptions<Gamma ...>> &)
        -> Formula<Or<P, Q>, Assumptions<Gamma ...>>
        {
            return Formula<Or<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P\/Q + P, Delta |- R + Q, Lambda |- R --> Gamma, Delta, Lambda |- R
        template <typename P, typename Q, typename R, typename ... Gamma, typename ... Delta, typename ... Lambda, typename = AreProps<P, Q, R>>
        static auto orE(const Formula<Or<P, Q>, Assumptions<Gamma ...>> &,
                        const Formula<R, Assumptions<P, Delta ...>> &,
                        const Formula<R, Assumptions<Q, Lambda ...>> &)
        -> Formula<R, MakeAssumptions<Gamma ..., Delta ..., Lambda ...>>
        {
            return Formula<R, MakeAssumptions<Gamma ..., Delta ..., Lambda ...>>();
        }
        
        // P, Gamma |- Q --> Gamma |- P=>Q
        template <typename P, typename Q, typename ... Gamma, typename = AreProps<P, Q>>
        static auto impI(const Formula<Q, Assumptions<P, Gamma ...>> &)
        -> Formula<Imp<P, Q>, Assumptions<Gamma ...>>
        {
            return Formula<Imp<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P => Q + Delta |- P --> Gamma, Delta |- Q
        template <typename P, typename Q, typename ... Gamma, typename ... Delta, typename = AreProps<P, Q>>
        static auto impE(const Formula<Imp<P, Q>, Assumptions<Gamma ...>> &,
                         const Formula<P, Assumptions<Delta ...>> &)
        -> Formula<Q, MakeAssumptions<Gamma ..., Delta ...>>
        {
            return Formula<Q, MakeAssumptions<Gamma ..., Delta ...>>();
        }
        
#ifdef IS_CLASSICAL
        // Law of excluded middle
        // {} |- P\/-P
        template <typename P>
        static auto lem()
        -> Formula<Or<P, Not<P>>, Assumptions<>, typename = AreProps<P>>
        {
            return Formula<Or<P, Not<P>>, Assumptions<>>();
        }
#endif
    };
};