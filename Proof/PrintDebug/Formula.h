//
//  Formula_PrintDebug.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/14.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PrintDebug/Utilities.h"
#include "Core/Formula.h"

template <typename Result, typename Asmps>
std::ostream &operator<<(std::ostream &os, const Formula<Result, Asmps> &) {
    os << "{" << Asmps() << "} |= " <<  Result();
    return os;
}

template <typename Result>
std::ostream &operator<<(std::ostream &os, const Formula<Result, Assumptions<>> &) {
    os << "|= " <<  Result();
    return os;
}