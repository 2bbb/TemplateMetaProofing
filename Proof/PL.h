//
//  PL.h
//  Proof
//
//  Created by ISHII 2bit on 2014/12/30.
//  Copyright (c) 2014年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Utilities.h"
#include "Assumption.h"
#include "Formula.h"

#define Proposition(name) struct name { static const char * const val() { return #name; } };

template <typename P> class Not {  };
template <typename P, typename Q> class And { };
template <typename P, typename Q> class Or  { };
template <typename P, typename Q> class Imp { };

namespace Axiom {
    class PL {
    public:
        // {} |- P --> P
        template <typename P>
        static Formula<P, Assumptions<P>> assume() {
            return Formula<P, Assumptions<P>>();
        }
        
        // P, Gamma |- F --> Gamma |- -P
        template <typename P, typename ... Gamma>
        static Formula<Not<P>, Assumptions<Gamma ...>> notI(const Formula<False, Assumptions<P, Gamma ...>> &) {
            return Formula<Not<P>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P + Delta |- -P --> Gamma, Delta |- False
        template <typename P, typename ... Gamma, typename ... Delta>
        static Formula<False, typename MakeAssumptions<Gamma ..., Delta ...>::type> notE(const Formula<P, Assumptions<Gamma ...>> &, const Formula<Not<P>, Assumptions<Delta ...>> &) {
            return Formula<False, typename MakeAssumptions<Gamma ..., Delta ...>::type>();
        }
        
        // Gamma |- P + Delta |- Q --> Gamma, Delta |- P /\ Q
        template <typename P, typename Q, typename ... Gamma, typename ... Delta>
        static Formula<And<P, Q>, typename MakeAssumptions<Gamma ..., Delta ...>::type> andI(const Formula<P, Assumptions<Gamma ...>> &, const Formula<Q, Assumptions<Delta ...>> &) {
            return Formula<And<P, Q>, typename MakeAssumptions<Gamma ..., Delta ...>::type>();
        }
        
        // Gamma |- P /\ Q --> Gamma |- P
        template <typename P, typename Q, typename ... Gamma>
        static Formula<P, Assumptions<Gamma ...>> andEL(const Formula<And<P, Q>, Assumptions<Gamma ...>> &) {
            return Formula<P, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P /\ Q --> Gamma |- Q
        template <typename P, typename Q, typename ... Gamma>
        static Formula<Q, Assumptions<Gamma ...>> andER(const Formula<And<P, Q>, Assumptions<Gamma ...>> &) {
            return Formula<Q, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P --> Gamma |- P\/Q
        template <typename P, typename Q, typename ... Gamma>
        static Formula<Or<P, Q>, Assumptions<Gamma ...>> orIL(const Formula<P, Assumptions<Gamma ...>> &) {
            return Formula<Or<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- Q --> Gamma |- P\/Q
        template <typename P, typename Q, typename ... Gamma>
        static Formula<Or<P, Q>, Assumptions<Gamma ...>> orIR(const Formula<Q, Assumptions<Gamma ...>> &) {
            return Formula<Or<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P\/Q + P, Delta |- R + Q, Lambda |- R --> Gamma, Delta, Lambda |- R
        template <typename P, typename Q, typename R, typename ... Gamma, typename ... Delta, typename ... Lambda>
        static Formula<R, typename MakeAssumptions<Gamma ..., Delta ..., Lambda ...>::type> orE(
                                                                                                const Formula<Or<P, Q>, Assumptions<Gamma ...>> &,
                                                                                                const Formula<R, Assumptions<P, Delta ...>> &,
                                                                                                const Formula<R, Assumptions<Q, Lambda ...>> &
                                                                                                ) {
            return Formula<R, typename MakeAssumptions<Gamma ..., Delta ..., Lambda ...>::type>();
        }
        
        // P, Gamma |- Q --> Gamma |- P=>Q
        template <typename P, typename Q, typename ... Gamma>
        static Formula<Imp<P, Q>, Assumptions<Gamma ...>> impI(const Formula<Q, Assumptions<P, Gamma ...>> &) {
            return Formula<Imp<P, Q>, Assumptions<Gamma ...>>();
        }
        
        // Gamma |- P => Q + Delta |- P --> Gamma, Delta |- Q
        template <typename P, typename Q, typename ... Gamma, typename ... Delta>
        static Formula<Q, typename MakeAssumptions<Gamma ..., Delta ...>::type> impE(const Formula<Imp<P, Q>, Assumptions<Gamma ...>>&, const Formula<P, Assumptions<Delta ...>> &) {
            return Formula<Q, typename MakeAssumptions<Gamma ..., Delta ...>::type>();
        }
        
#ifdef IS_CLASSICAL
        // Law of excluded middle
        // {} |- P\/-P
        template <typename P>
        static Formula<Or<P, Not<P>>, Assumptions<>> lem() {
            return Formula<Or<P, Not<P>>, Assumptions<>>();
        }
#endif
    };
};