//
//  FOL.h
//  Proof
//
//  Created by ISHII 2bit on 2014/12/31.
//  Copyright (c) 2014年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "PL.h"

template <typename X, template<typename ...> class Prop> class ForAll {};
template <typename X, template<typename ...> class Prop> class Exists {};

namespace Axiom {
    class FOL {
        
    };
}