//
//  Core/Constants.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

namespace Types {
    struct Kind {};
    struct Bool : public Kind {};
};

namespace Meta {
    struct True  : public Types::Bool { static const char * const val() { return "T"; } };
    struct False : public Types::Bool { static const char * const val() { return "F"; } };
}