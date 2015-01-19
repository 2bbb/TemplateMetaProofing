//
//  Core/Formula.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/06.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"
#include "Core/Assumptions.h"

namespace Axiom {
    class PL;
    class FOL;
    class Equality;
    class PA;
};

DeclareType(Formula)

template <typename Result, typename Asmp>
class Formula : public Types::Formula {
    friend class Axiom::PL;
    friend class Axiom::FOL;
    friend class Axiom::Equality;
    friend class Axiom::PA;
public:
    using IsTheorem = Meta::Equal<Asmp, Assumptions<>>;
    void qed(Enable<IsTheorem> = Enable<IsTheorem>()) const {
        std::cout << "  Q.E.D."
                  << std::endl;
    };
private:
    template <typename ... Formulas>
    Formula(const Formulas & ... formulas) {};
};

template <typename Result>
using Theorem = Formula<Result, Assumptions<>>;

#define Proof(...) auto