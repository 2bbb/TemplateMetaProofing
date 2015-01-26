//
//  Core/Macros.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/11.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#define Type(...) using
#define Function(...) using

#define requires(...) typename _ = Enable<__VA_ARGS__>
#define Requires(...) __VA_ARGS__, _
#define fulfill(...) _();

#define CreateVariable(name, type) struct name {\
    using IsType = Meta::False;\
    using TypeInfo = type;\
    static const char * const val() { return #name; }\
};\

#define DeclareType(type) namespace Types {\
    struct type : public Types::Kind {\
        using TypeInfo = type;\
        using IsType = Meta::True;\
    };\
};

#define SetType(type) using TypeInfo = Types::type;