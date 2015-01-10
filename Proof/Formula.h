//
//  Formula.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/06.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Assumption.h"

namespace Axiom { class PL; };

template <typename Result, typename Asmp>
class Formula {
    Formula() {};
    friend class Axiom::PL;
};

template <typename Result>
class Formula<Result, Assumptions<>> {
    Formula() {};
    friend class Axiom::PL;
public:
    void qed() const {};
};

#define DefineAxiom(name, Type) static Type name() { return Type(); };