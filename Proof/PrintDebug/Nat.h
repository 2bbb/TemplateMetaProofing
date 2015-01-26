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

std::ostream &operator<<(std::ostream &os, const Nat::Zero &) {
    os << "zero";
    return os;
}

template <typename T, typename S = Enable<Nat::IsNat<T>>>
std::ostream &operator<<(std::ostream &os, const Nat::Suc<T> &) {
    os << "s(" << T() << ")";
    return os;
}

template <typename M, typename N, typename S = Enable<Meta::And<Nat::IsNat<M>, Nat::IsNat<N>>>>
std::ostream &operator<<(std::ostream &os, const Nat::Add<M, N> &) {
    os << "(" << M() << ") + (" << N() << ")";
    return os;
}

template <typename M, typename N, typename S = Enable<Meta::And<Nat::IsNat<M>, Nat::IsNat<N>>>>
std::ostream &operator<<(std::ostream &os, const Nat::Mul<M, N> &) {
    os << "(" << M() << ") * (" << N() << ")";
    return os;
}