//
//  Tests/Nat.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/12.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Nat.h"

namespace NatTest {
    using namespace Nat;
    
    auto proof_of_1_plus_1_is_2()
    -> Theorem<Eq<Add<Suc<Zero>, Suc<Zero>>, Suc<Suc<Zero>>>> {
        using namespace Axiom;
        // ├ s(0) + s(0) == s(s(0) + 0)
        Formula<Eq<Add<Suc<Zero>, Suc<Zero>>, Suc<Add<Suc<Zero>, Zero>>>, Assumptions<>> proof1
            = PA::add_m_sn_is_s_add_m_n<Suc<Zero>, Zero>();
        
        // ├ s(0) + 0 == s(0)
        Formula<Eq<Add<Suc<Zero>, Zero>, Suc<Zero>>, Assumptions<>> proof2
            = PA::add_m_0_is_m<Suc<Zero>>();
        
        // ├ s(s(0) + 0) == s(s(0))
        Formula<Eq<Suc<Add<Suc<Zero>, Zero>>, Suc<Suc<Zero>>>, Assumptions<>> proof3
            = PA::eq_suc(proof2);
        
        // ├ s(0) + s(0) == s(s(0))
        Theorem<Eq<Add<Suc<Zero>, Suc<Zero>>, Suc<Suc<Zero>>>> proof = Axiom::Equality::transitive(proof1, proof3);
        return proof;
    }
    
    template <typename M, typename X = NewType<M>>
    auto proofOf_m_plus_0_is_0_plus_m()
    -> Theorem<ForAll<M, Eq<Add<M, Zero>, Add<Zero, M>>>> {
        // ├
        auto proof_of_base_step = Axiom::Equality::reflexive<Add<Zero, Zero>>();
        std::cout << "base_step : " << proof_of_base_step << std::endl;
        
        // {m + 0 = 0 + m} ├ m + 0 = 0 + m
        auto proof2 = Axiom::PL::assume<Eq<Add<X, Zero>, Add<Zero, X>>>();
        // ├ m + 0 = m
        auto proof3 = Axiom::PA::add_m_0_is_m<X>();
        // ├ s(m + 0) = s(m)
        auto proof4 = Axiom::PA::eq_suc(proof3);
        // ├ s(m) + 0 = s(m)
        auto proof5 = Axiom::PA::add_m_0_is_m<Suc<X>>();
        
        // ├ 0 + s(m) = s(0 + m)
        auto proof6 = Axiom::PA::add_m_sn_is_s_add_m_n<Zero, X>();
        // ├ s(0 + m) = s(m + 0)
        auto proof7 = Axiom::Equality::symmetric(Axiom::PA::eq_suc(proof2));
        // ├ s(0 + m) = s(m)
        auto proof8 = Axiom::Equality::transitive(proof7, proof4);
        // ├ 0 + s(m) = s(m)
        auto proof9 = Axiom::Equality::transitive(proof6, proof8);
        
        // ├ m + 0 = 0 + m => s(m) + 0 = 0 + s(m)
        auto proof10 = Axiom::Equality::transitive(proof5, Axiom::Equality::symmetric(proof9));
        
        auto proof_of_induction_step = Axiom::PL::impI(proof10);
        std::cout << "induction_step : " << proof_of_induction_step << std::endl;
        
        Theorem<ForAll<M, Eq<Add<M, Zero>, Add<Zero, M>>>> proof
            = Axiom::PA::induction<M, Eq<Add<M, Zero>, Add<Zero, M>>, X>(proof_of_base_step,
                                   proof_of_induction_step);
        return proof;
    }
};

#include "PrintDebug/Nat.h"

namespace NatTest {
// TODO: fix about declare variable
    NaturalNumber(M);
    void test() {
        using namespace std;
        cout << Suc<Zero>() << endl
             << endl
        
             << Add<Suc<Zero>, Suc<Zero>>() << endl
             << endl
        
             << proof_of_1_plus_1_is_2() << endl
             << endl
        
             << proofOf_m_plus_0_is_0_plus_m<M>() << endl
             << endl;
    }
};