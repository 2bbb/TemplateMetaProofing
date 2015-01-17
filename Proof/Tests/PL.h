//
//  PL_test.cpp
//  Proof
//
//  Created by ISHII 2bit on 2015/01/04.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/PL.h"

namespace {
    Proposition(P);
    Proposition(Q);
    
    auto proofOfPorQthenQorP()
    -> Theorem<Imp<Or<P, Q>, Or<Q, P>>>
    {
        Proof(assume P\/Q) proof1 = Axiom::PL::assume<Or<P, Q>>();
        Proof(assume P) proof2 = Axiom::PL::assume<P>();
        Proof(assume Q) proof3 = Axiom::PL::assume<Q>();
        Proof(if P then Q\/P) proof4 = Axiom::PL::orIR<Q, P>(proof2);
        Proof(if Q then Q\/P) proof5 = Axiom::PL::orIL<Q, P>(proof3);
        Proof() proof6 = Axiom::PL::orE<P, Q, Or<Q, P>, Or<P, Q>>(proof1, proof4, proof5);
        Theorem<Imp<Or<P, Q>, Or<Q, P>>> proof = Axiom::PL::impI(proof6);
        
        return proof;
    }

    auto proofOfPandQthenQandP()
    -> Theorem<Imp<And<P, Q>, And<Q, P>>>
    {
        using namespace Axiom;
        Proof(assume P/\Q) proof1 = PL::assume<And<P, Q>>();
        Proof(elim P from P/\Q) proof2 = PL::andER(proof1);
        Proof(elim Q from P/\Q) proof3 = PL::andEL(proof1);
        Proof() proof4 = PL::andI(proof2, proof3);
        Theorem<Imp<And<P, Q>, And<Q, P>>> proof = PL::impI(proof4);
        
        return proof;
    }
    
    auto exampleOfNotE()
    -> Formula<False, Assumptions<P, Not<P>>>
    {
        using namespace Axiom;
        Proof() proof1 = PL::assume<P>();
        Proof() proof2 = PL::assume<Not<P>>();
        Proof() proof3 = PL::notE(proof1, proof2);
        return proof3;
    }
};

#include "PrintDebug/PL.h"

namespace PLTest {
    void test() {
        using namespace std;
        cout << And<P, Q>() << endl
             << And<P, Q>() << endl
             << proofOfPorQthenQorP() << endl
             << proofOfPandQthenQandP() << endl
             << exampleOfNotE() << endl;
    }
};