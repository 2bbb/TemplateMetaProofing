//
//  Set_test.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Set.h"
#include <typeinfo>

#define Element(name) struct name { static const char * const val() { return #name; } };

namespace SetTest {
    Element(A);
    Element(B);
    Element(C);
    Element(D);
    Element(E);
    
    Type(Set) X = Set<A, B, C, D>;
    Type(Set) Y = Set<A, C, E>;
    Type(Set) Z = Set<B, D>;
    
    Type(Set) XorY  = Reduction(Union<X, Y>);
    Type(Set) XandY = Reduction(Intersection<X, Y>);
    
    Type(Set) YandZ = Reduction(Intersection<Y, Z>);
};

#include "Set_PrintDebug.h"

namespace SetTest {
    void test() {
        std::cout << XorY() << std::endl;
        std::cout << XandY() << std::endl;
        std::cout << YandZ() << std::endl;
    }
};