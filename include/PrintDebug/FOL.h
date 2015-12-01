//
//  PrintDebug/FOL.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/14.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PrintDebug/Utilities.h"
#include "Core/FOL.h"

template <typename X, typename Prop>
std::ostream &operator<<(std::ostream &os, const ForAll<X, Prop> &) {
    os << "∀" << X() << ".(" << Prop() << ")";
    return os;
}

template <typename X, typename Prop>
std::ostream &operator<<(std::ostream &os, const Exists<X, Prop> &) {
    os << "∀" << X() << ".(" << Prop() << ")";
    return os;
}