//
//  Core/PL.h
//  Proof
//
//  Created by ISHII 2bit on 2014/12/30.
//  Copyright (c) 2014年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"
#include "Core/Assumptions.h"
#include "Core/Proposition.h"
#include "Core/Formula.h"

template <typename P, requires(AreProps<P>)> struct Not : public Requires(Types::Proposition) {};
template <typename P, typename Q, requires(AreProps<P, Q>)> struct And : public Requires(Types::Proposition) {};
template <typename P, typename Q, requires(AreProps<P, Q>)> struct Or  : public Requires(Types::Proposition) {};
template <typename P, typename Q, requires(AreProps<P, Q>)> struct Imp : public Requires(Types::Proposition) {};

namespace Axiom {
    class PL {
    public:
        // {} |- P --> P
        template <typename P, requires(AreProps<P>)>
        static auto assume()
        -> Formula<P, Assumptions<P>>
        {
            fulfill();
            return Formula<P, Assumptions<P>>();
        }
        
        // P, Gamma |- F --> Gamma |- -P
        template <typename P, typename ... Gamma, requires(AreProps<P>)>
        static auto notI(const Formula<Contradiction, Assumptions<P, Gamma ...>> &)
        -> Formula<Not<P>, Assumptions<Gamma ...>>
        {
            fulfill(AreProps<P>);
            return Formula<Not<P>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P + Delta |- -P --> Gamma, Delta |- Contradiction
        template <typename P, typename ... Gamma, typename ... Delta, requires(AreProps<P>)>
        static auto notE(const Formula<P, Assumptions<Gamma ...>> &,
                         const Formula<Not<P>, Assumptions<Delta ...>> &)
        -> Formula<Contradiction, MakeAssumptions<Gamma ..., Delta ...>>
        {
            fulfill(AreProps<P>);
            return Formula<Contradiction, MakeAssumptions<Gamma ..., Delta ...>>();
        }
        
        // Gamma |- P + Delta |- Q --> Gamma, Delta |- P /\ Q
        template <typename P, typename Q, typename ... Gamma, typename ... Delta, requires(AreProps<P, Q>)>
        static auto andI(const Formula<P, Assumptions<Gamma ...>> &proof1,
                         const Formula<Q, Assumptions<Delta ...>> &proof2)
        -> Formula<And<P, Q>, MakeAssumptions<Gamma ..., Delta ...>>
        {
            fulfill(AreProps<P, Q>);
            return Formula<And<P, Q>, MakeAssumptions<Gamma ..., Delta ...>>();
        }
        
        // Gamma |- P /\ Q --> Gamma |- P
        template <typename P, typename Q, typename ... Gamma, requires(AreProps<P, Q>)>
        static auto andEL(const Formula<And<P, Q>, Assumptions<Gamma ...>> &)
        -> Formula<P, Assumptions<Gamma ...>>
        {
            fulfill(AreProps<P, Q>);
            return Formula<P, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P /\ Q --> Gamma |- Q
        template <typename P, typename Q, typename ... Gamma, requires(AreProps<P, Q>)>
        static auto andER(const Formula<And<P, Q>, Assumptions<Gamma ...>> &)
        -> Formula<Q, Assumptions<Gamma ...>>
        {
            fulfill(AreProps<P, Q>);
            return Formula<Q, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P --> Gamma |- P\/Q
        template <typename P, typename Q, typename ... Gamma, requires(AreProps<P, Q>)>
        static auto orIL(const Formula<P, Assumptions<Gamma ...>> &)
        -> Formula<Or<P, Q>, Assumptions<Gamma ...>>
        {
            fulfill(AreProps<P, Q>);
            return Formula<Or<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- Q --> Gamma |- P\/Q
        template <typename P, typename Q, typename ... Gamma, requires(AreProps<P, Q>)>
        static auto orIR(const Formula<Q, Assumptions<Gamma ...>> &)
        -> Formula<Or<P, Q>, Assumptions<Gamma ...>>
        {
            fulfill(AreProps<P, Q>);
            return Formula<Or<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P\/Q + P, Delta |- R + Q, Lambda |- R --> Gamma, Delta, Lambda |- R
        template <typename P, typename Q, typename R, typename ... Gamma, typename ... Delta, typename ... Lambda, requires(AreProps<P, Q, R>)>
        static auto orE(const Formula<Or<P, Q>, Assumptions<Gamma ...>> &,
                        const Formula<R, Assumptions<P, Delta ...>> &,
                        const Formula<R, Assumptions<Q, Lambda ...>> &)
        -> Formula<R, MakeAssumptions<Gamma ..., Delta ..., Lambda ...>>
        {
            fulfill(AreProps<P, Q, R>);
            return Formula<R, MakeAssumptions<Gamma ..., Delta ..., Lambda ...>>();
        }
        
        // P, Gamma |- Q --> Gamma |- P=>Q
        template <typename P, typename Q, typename ... Gamma, requires(AreProps<P, Q>)>
        static auto impI(const Formula<Q, Assumptions<P, Gamma ...>> &)
        -> Formula<Imp<P, Q>, Assumptions<Gamma ...>>
        {
            fulfill(AreProps<P, Q>);
            return Formula<Imp<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P => Q + Delta |- P --> Gamma, Delta |- Q
        template <typename P, typename Q, typename ... Gamma, typename ... Delta, requires(AreProps<P, Q>)>
        static auto impE(const Formula<Imp<P, Q>, Assumptions<Gamma ...>> &,
                         const Formula<P, Assumptions<Delta ...>> &)
        -> Formula<Q, MakeAssumptions<Gamma ..., Delta ...>>
        {
            fulfill(AreProps<P, Q>);
            return Formula<Q, MakeAssumptions<Gamma ..., Delta ...>>();
        }
        
        // Gamma |- ⊥ --> Gamma |- P
        template <typename P, typename ... Gamma, requires(AreProps<P>)>
        static auto contradiction(const Formula<Contradiction, Assumptions<Gamma ...>> &)
        -> Formula<P, Assumptions<Gamma ...>>
        {
            fulfill(AreProps<P>);
            return Formula<P, Assumptions<Gamma ...>>();
        }
        
#ifdef IS_CLASSICAL
        // Law of excluded middle
        // {} |- P\/-P
        template <typename P>
        static auto lem()
        -> Formula<Or<P, Not<P>>, Assumptions<>, requires(AreProps<P>)>
        {
            fulfill(AreProps<P>);
            return Formula<Or<P, Not<P>>, Assumptions<>>();
        }
#endif
    };
};