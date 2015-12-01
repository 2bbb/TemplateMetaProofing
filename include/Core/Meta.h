//
//  Core/Meta.h
//  Proof
//
//  Created by ISHII 2bit on 2015/01/11.
//  Copyright (c) 2015年 bufferRenaiss. All rights reserved.
//

#pragma once

#include "Core/Constants.h"
#include "Core/Macros.h"
#include "Core/Utilities.h"

namespace Meta {
    namespace {
        template <typename A, typename B>
        struct equal_impl : public False {};
        
        template <typename A>
        struct equal_impl<A, A> : public True {};
        
        template <typename A>
        struct not_impl;
        
        template <>
        struct not_impl<True> : public False {};
        
        template <>
        struct not_impl<False> : public False {};
        
        template <typename, typename>
        struct and_impl;
        
        template <>
        struct and_impl<True, True> : public True {};
        
        template <>
        struct and_impl<True, False> : public False {};
        
        template <>
        struct and_impl<False, True> : public False {};
        
        template <>
        struct and_impl<False, False> : public False {};
        
        template <typename, typename>
        struct or_impl;
        
        template <>
        struct or_impl<False, False> : public False {};
        
        template <>
        struct or_impl<True, False> : public True {};
        
        template <>
        struct or_impl<False, True> : public True {};
        
        template <>
        struct or_impl<True, True> : public True {};
    };
    
    /**
     *  TMP Equal
     *
     *  @param A any type
     *  @param B any type
     *
     *  @return Bool A == B
     */
    template <typename A, typename B>
    Type(Bool) Equal = Reduction<equal_impl<A, B>>;
    
    /**
     *  TMP Not
     *
     *  @param A <b>requires</b> Types::Bool
     *
     *  @return Bool !A
     */
    template <typename A>
    Type(Bool) Not = Reduction<not_impl<A>>;
    
    /**
     *  TMP And
     *
     *  @param A <b>requires</b> Types::Bool
     *  @param B <b>requires</b> Types::Bool
     *
     *  @return Bool A && B
     */
    template <typename A, typename B>
    Type(Bool) And = Reduction<and_impl<A, B>>;
    
    /**
     *  TMP Or
     *
     *  @param A <b>requires</b> Types::Bool
     *  @param B <b>requires</b> Types::Bool
     *
     *  @return Bool A || B
     */
    template <typename A, typename B>
    Type(Bool) Or = Reduction<or_impl<A, B>>;
    
    namespace {
        struct disabler;
        
        template <typename Condition, typename Then, typename Else> struct if_impl;
        
        template <typename Then, typename Else>
        struct if_impl<True, Then, Else> {
            Type(Value) type = Then;
        };
        
        template <typename Then, typename Else>
        struct if_impl<False, Then, Else> {
            Type(Value) type = Else;
        };
        
        template <typename Then>
        struct if_impl<False, Then, disabler>;
    };
    
    /**
     *  TMP If function
     *
     *  @param Condition <b>requires</b> Types::Bool
     *  @param Then if Condition is True
     *  @param Else if Condition is False, default = disabler. i.e. if we don't give this parameter and Condition is False then we failed to compile.
     *
     *  @return Then or Else
     */
    template <typename Condition, typename Then, typename Else = disabler>
    Function(Bool->X->X->X) If = Reduction<if_impl<Condition, Then, Else>>;
};