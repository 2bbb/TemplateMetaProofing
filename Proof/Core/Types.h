//
//  Types.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/17.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Utilities.h"
#include "Core/Meta.h"

template <typename X, typename T>
using HasType = Meta::And<IsDerived<T, type_>, IsDerived<X, T>>;