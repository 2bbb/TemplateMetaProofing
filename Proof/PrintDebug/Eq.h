//
//  Eq_PrintDebug.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/14.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PrintDebug/Utilities.h"
#include "Core/Eq.h"

template <typename S, typename T>
std::ostream &operator<<(std::ostream &os, const Eq<S, T> &) {
    os << S() << " == " << T();
    return os;
}