//
//  Assumption.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/06.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Includes.h"
#include "Proposition.h"

template <typename ... As>
struct Assumptions : Enable<AreProps<As ...>>{};

namespace {
    template <typename ... As>
    struct make_assumptions_impl {
        using type = Reduction<make_assumptions_impl<MakeUnique<As ...>>>;
    };

    template <typename ... As>
    struct make_assumptions_impl<TypeHolder<As ...>> {
        using type = Assumptions<As ...>;
    };
};

template <typename ... As>
using MakeAssumptions = Reduction<make_assumptions_impl<As ...>>;