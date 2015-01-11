//
//  Set_test.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Set.h"

#define Element(name) struct name { static const char * const val() { return #name; } };

namespace {
    Element(A);
    Element(B);
    Element(C);
    Element(D);
    Element(E);
    
    Type(Set) X = Set<A, B, C, D>;
    Type(Set) Y = Set<A, C, E>;
    Type(Set) Z = Set<B, D>;
    
    Type(Set) XorY  = Union<X, Y>;
    Type(Set) XandY = Intersection<X, Y>;
    Type(Set) YandZ = Intersection<Y, Z>;

    Assert<XorY, Set<A, B, C, D, E>> _01;
    Assert<XandY, Set<A, C>> _02;
    Assert<YandZ, Set<>> _03;
    
    Assert<Contain<XorY, Set<A, B, C, D, E>>, True> _04;
    Assert<Contain<Set<A, B, C, D, E>, XorY>, True> _05;
    Assert<EqualSet<XorY, Set<A, B, C, D, E>>, True> _06;
    
    Type(Set) XprodY = Product<X, Y>;
    Type(Set) ZprodZ = Product<Z, Z>;
    
    template <typename P>
    Type() tuple_mod = Tuple<A, P>;
    Type() Mapped = Map<tuple_mod, X>;
    
    Assert<In<A, X>, True> _11;
    Assert<In<E, X>, False> _12;
    Assert<In<E, Y>, True> _13;
    Assert<In<A, Z>, False> _14;
};

#include "Set_PrintDebug.h"

namespace SetTest {
    void test() {
        std::cout << XorY() << std::endl;
        std::cout << XandY() << std::endl;
        std::cout << YandZ() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << XprodY() << std::endl;
        std::cout << ZprodZ() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << Mapped() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << In<A, X>() << std::endl;
        std::cout << In<E, X>() << std::endl;
        std::cout << In<A, Z>() << std::endl;
        std::cout << In<E, Y>() << std::endl;
        std::cout << std::endl;
    }
};