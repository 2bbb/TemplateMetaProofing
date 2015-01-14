//
//  Formula.h
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

template <typename Result, typename Asmp>
class Formula {
    template <typename ... Formulas>
    Formula(const Formulas & ... formulas) {};
    friend class Axiom::PL;
    friend class Axiom::FOL;
    friend class Axiom::Equality;
    friend class Axiom::PA;
};

template <typename Result>
class Formula<Result, Assumptions<>> {
    Formula() {};
    friend class Axiom::PL;
    friend class Axiom::FOL;
    friend class Axiom::Equality;
    friend class Axiom::PA;
public:
    void qed() const {};
};

template <typename Result>
using Theorem = Formula<Result, Assumptions<>>;

#define Proof(...) auto