//
//  PrintDebug/Set.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/09.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PrintDebug/Utilities.h"
#include "Core/Set.h"

template <typename ... As>
std::ostream &operator<<(std::ostream &os, const Set<As ...> &) {
    os << "{" << Reduction<Set<As ...>>() << "}";
    return os;
}