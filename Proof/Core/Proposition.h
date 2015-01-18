//
//  Core/Proposition.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/06.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"

namespace Types {
    struct Proposition : public Kind {};
}

#define Proposition(name) CreateVariable(name, Types::Proposition)

template <typename P>
using IsProp = HasType<P, Types::Proposition>;

template <typename ... Ps>
using AreProps = Reduce<Meta::And, Meta::True, Map<IsProp, Set<Ps ...>>>;

struct Tautology : public Types::Proposition { static const char * const val() { return "Ｔ"; } };
struct Contradiction : public Types::Proposition { static const char * const val() { return "⊥"; } };