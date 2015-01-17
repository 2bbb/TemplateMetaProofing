//
//  Core/Constants.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

struct type_ {};

namespace Meta {
    struct BoolType : public type_ {};
    struct True  : BoolType { static const char * const val() { return "T"; } };
    struct False : BoolType { static const char * const val() { return "F"; } };
}