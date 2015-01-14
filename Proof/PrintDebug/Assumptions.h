//
//  Assumptions_PrintDebug.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/14.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PrintDebug/Utilities.h"
#include "Core/Assumptions.h"

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
