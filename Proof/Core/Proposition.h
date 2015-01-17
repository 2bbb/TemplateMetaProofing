//
//  Core/Proposition.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/06.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Includes.h"

struct PropositionType : public type_ {};
#define Proposition(name) struct name : public PropositionType { static const char * const val() { return #name; } };

template <typename P>
using IsProp = HasType<P, PropositionType>;

template <typename ... Ps>
using AreProps = Reduce<Meta::And, Meta::True, Map<IsProp, Set<Ps ...>>>;

struct Tautology : public PropositionType { static const char * const val() { return "Ｔ"; } };
struct Contradiction : public PropositionType { static const char * const val() { return "⊥"; } };