//
//  PL_test.cpp
//  Proof
//
//  Created by ISHII 2bit on 2015/01/04.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PL.h"

namespace {
    Proposition(P);
    Proposition(Q);

    const Formula<Imp<Or<P, Q>, Or<Q, P>>, Assumptions<>>  &proofOfPorQthenQorP() {
        Formula<Or<P, Q>, Assumptions<Or<P, Q>>> proof1 = Axiom::PL::assume<Or<P, Q>>();
        Formula<P, Assumptions<P>> proof2 = Axiom::PL::assume<P>();
        Formula<Q, Assumptions<Q>> proof3 = Axiom::PL::assume<Q>();
        Formula<Or<Q, P>, Assumptions<P>> proof4 = Axiom::PL::orIR<Q, P>(proof2);
        Formula<Or<Q, P>, Assumptions<Q>> proof5 = Axiom::PL::orIL<Q, P>(proof3);
        Formula<Or<Q, P>, Assumptions<Or<P, Q>>> proof6 = Axiom::PL::orE<P, Q, Or<Q, P>, Or<P, Q>>(proof1, proof4, proof5);
        static Formula<Imp<Or<P, Q>, Or<Q, P>>, Assumptions<>> proof = Axiom::PL::impI(proof6);
        
        return proof;
    }

    const Formula<Imp<And<P, Q>, And<Q, P>>, Assumptions<>> &proofOfPandQthenQandP() {
        using namespace Axiom;
        auto proof1 = PL::assume<And<P, Q>>();
        auto proof2 = PL::andER(proof1);
        auto proof3 = PL::andEL(proof1);
        auto proof4 = PL::andI(proof2, proof3);
        static Formula<Imp<And<P, Q>, And<Q, P>>, Assumptions<>> proof = PL::impI(proof4);
        
        return proof;
    }
};

#include "PL_PrintDebug.h"

namespace PLTest {
    void test() {
        using namespace std;
        cout << And<P, Q>() << endl
             << proofOfPorQthenQorP()
             << proofOfPandQthenQandP();
    }
};