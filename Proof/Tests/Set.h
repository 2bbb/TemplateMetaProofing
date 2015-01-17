//
//  Set_test.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/07.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Set.h"

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
    
    Assert<Contain<XorY, Set<A, B, C, D, E>>, Meta::True> _04;
    Assert<Contain<Set<A, B, C, D, E>, XorY>, Meta::True> _05;
    Assert<EqualSet<XorY, Set<A, B, C, D, E>>, Meta::True> _06;
    
    Type(Set) XprodY = Product<X, Y>;
    Type(Set) ZprodZ = Product<Z, Z>;
    
    template <typename P>
    Type() tuple_mod = Tuple<A, P>;
    Type() Mapped = Map<tuple_mod, X>;
    
    Assert<In<A, X>, Meta::True> _11;
    Assert<In<E, X>, Meta::False> _12;
    Assert<In<E, Y>, Meta::True> _13;
    Assert<In<A, Z>, Meta::False> _14;
};

#include "PrintDebug/Set.h"

namespace SetTest {
    void test() {
        std::cout   << XorY() << std::endl
                    << XandY() << std::endl
                    << YandZ() << std::endl
                    << std::endl
        
                    << XprodY() << std::endl
                    << ZprodZ() << std::endl
                    << std::endl
        
                    << Mapped() << std::endl
                    << std::endl
        
                    << In<A, X>() << std::endl
                    << In<E, X>() << std::endl
                    << In<A, Z>() << std::endl
                    << In<E, Y>() << std::endl
                    << std::endl;
    }
};