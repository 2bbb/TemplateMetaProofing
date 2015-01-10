//
//  Assumption.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/06.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Utilities.h"

template <typename ... As>
class Assumptions {};

template <typename ... As>
struct MakeAssumptions {
    using type = Reduction(MakeAssumptions<Reduction(MakeUnique<As ...>)>);
};

template <typename ... As>
struct MakeAssumptions<TypeHolder<As ...>> {
    using type = Assumptions<As ...>;
};