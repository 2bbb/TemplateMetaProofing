//
//  Set_PrintDebug.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/09.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Set.h"

#include <sstream>
#include <type_traits>

#include "PrintDebugUtilities.h"

template <typename ... As>
std::ostream &operator<<(std::ostream &os, const Set<As ...> &) {
    os << "{" << Reduction(Set<As ...>)() << "}";
    return os;
}