//
//  main.cpp
//  Proof
//
//  Created by ISHII 2bit on 2014/12/30.
//  Copyright (c) 2014年 bufferRenaiss. All rights reserved.
//

#include <iostream>

#include "Tests/Utilities.h"
#include "Tests/Set.h"
#include "Tests/PL.h"
#include "Tests/Nat.h"

int main(int argc, const char * argv[]) {
    SetTest::test();
    PLTest::test();
    NatTest::test();
    
    return 0;
}
