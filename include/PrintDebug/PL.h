//
//  PrintDebug/PL.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/04.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PrintDebug/Utilities.h"
#include "Core/PL.h"

template <typename P>
std::ostream &operator<<(std::ostream &os, const Not<P> &) {
    os << "-" << P();
    return os;
}

template <typename P, typename Q>
std::ostream &operator<<(std::ostream &os, const And<P, Q> &) {
    os << "(" << P() << ") /\\ (" << Q() << ")";
    return os;
}

template <typename P, typename Q>
std::ostream &operator<<(std::ostream &os, const Or<P, Q> &) {
    os << "(" << P() << ") \\/ (" << Q() << ")";
    return os;
}

template <typename P, typename Q>
std::ostream &operator<<(std::ostream &os, const Imp<P, Q> &) {
    os << "(" << P() << ") -> (" << Q() << ")";
    return os;
}