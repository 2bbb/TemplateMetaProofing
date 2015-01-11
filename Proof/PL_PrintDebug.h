//
//  PL_PrintDebug.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/04.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PL.h"
#include "PrintDebugUtilities.h"

template <typename P>
std::ostream &operator<<(std::ostream &os, const Not<P> &) {
    os << "-" << P();
    return os;
}

template <typename P, typename Q>
std::ostream &operator<<(std::ostream &os, const And<P, Q> &) {
    os << "(" << P() << "/\\" << Q() << ")";
    return os;
}

template <typename P, typename Q>
std::ostream &operator<<(std::ostream &os, const Or<P, Q> &) {
    os << "(" << P() << "\\/" << Q() << ")";
    return os;
}

template <typename P, typename Q>
std::ostream &operator<<(std::ostream &os, const Imp<P, Q> &) {
    os << "(" << P() << "->" << Q() << ")";
    return os;
}

template <typename A, typename B, typename ... Asmps>
std::ostream &operator<<(std::ostream &os, const Assumptions<A, B, Asmps ...> &) {
    os << A() << ", " << Assumptions<B, Asmps ...>();
    return os;
}

template <typename A>
std::ostream &operator<<(std::ostream &os, const Assumptions<A> &) {
    os << A();
    return os;
}

std::ostream &operator<<(std::ostream &os, const Assumptions<> &) {
    return os;
}

template <typename Result, typename Asmps>
std::ostream &operator<<(std::ostream &os, const Formula<Result, Asmps> &) {
    os << "{" << Asmps() << "} |- " <<  Result() << std::endl;
    
    return os;
}