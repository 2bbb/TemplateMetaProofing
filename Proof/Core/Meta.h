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
        struct equal_impl {
            Type(Bool) type = False;
        };
        
        template <typename A>
        struct equal_impl<A, A> {
            Type(Bool) type = True;
        };
        
        template <typename A>
        struct not_impl;
        
        template <>
        struct not_impl<True> {
            Type(Bool) type = False;
        };
        
        template <>
        struct not_impl<False> {
            Type(Bool) type = True;
        };
        
        template <typename, typename>
        struct and_impl {
            Type(Bool) type = False;
        };
        
        template <>
        struct and_impl<True, True> {
            Type(Bool) type = True;
        };
        
        template <typename, typename>
        struct or_impl {
            Type(Bool) type = True;
        };
        
        template <>
        struct or_impl<False, False> {
            Type(Bool) type = False;
        };
    };
    
    template <typename A, typename B>
    using Equal = Reduction<equal_impl<A, B>>;
    
    template <typename A>
    using Not = Reduction<not_impl<A>>;
    
    template <typename A, typename B>
    using And = Reduction<and_impl<A, B>>;
    
    template <typename A, typename B>
    using Or = Reduction<or_impl<A, B>>;
    
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
    
    template <typename Condition, typename Then, typename Else = disabler>
    Function(Bool->X->X->X) If = Reduction<if_impl<Condition, Then, Else>>;
};