//
//  PrintDebug/Nat.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/14.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PrintDebug/Utilities.h"
#include "Core/Nat.h"

namespace Nat {
    std::ostream &operator<<(std::ostream &os, const Zero &) {
        os << "zero";
        return os;
    }

    template <typename T, typename S = Enable<IsNat<T>>>
    std::ostream &operator<<(std::ostream &os, const Suc<T> &) {
        os << "s(" << T() << ")";
        return os;
    }

    template <typename M, typename N, typename S = Enable<Meta::And<IsNat<M>, IsNat<N>>>>
    std::ostream &operator<<(std::ostream &os, const Add<M, N> &) {
        os << "(" << M() << ") + (" << N() << ")";
        return os;
    }

    template <typename M, typename N, typename S = Enable<Meta::And<IsNat<M>, IsNat<N>>>>
    std::ostream &operator<<(std::ostream &os, const Mul<M, N> &) {
        os << "(" << M() << ") * (" << N() << ")";
        return os;
    }
};