//
//  ofx1plus1is2Eq.h
//
//  Created by ISHII 2bit on 2014/12/29.
//
//

#pragma once

#include "Core/Includes.h"
#include "Core/FOL.h"

template<typename S, typename T>
struct Eq {};

namespace Axiom {
    class Equality {
    public:
        // m = m
        template<typename S>
        static auto reflexive()
        -> Formula<Eq<S, S>, Assumptions<>> {
            return Formula<Eq<S, S>, Assumptions<>>();
        }
        
        // m = n -> n = m
        template<typename S, typename T, typename ... As>
        static auto symmetric(const Formula<Eq<T, S>, Assumptions<As ...>> &)
        -> Formula<Eq<S, T>, Assumptions<As ...>> {
            return Formula<Eq<S, T>, Assumptions<As ...>>();
        }
        
        // m = n, n = k -> m = k
        template <typename S, typename T, typename U, typename ... As, typename ... Bs>
        static auto transitive(const Formula<Eq<S, T>, Assumptions<As ...>> &,
                               const Formula<Eq<T, U>, Assumptions<Bs ...>> &)
        -> Formula<Eq<S, U>, MakeAssumptions<As ..., Bs ...>> {
            return Formula<Eq<S, U>, MakeAssumptions<As ..., Bs ...>>();
        };
    };
};