// (c) Copyright 2016 Josh Wright
#include <iostream>
#include <gtest/gtest.h>
#include "add.h"
#include "vec.h"
#include "get.h"
#include "map.h"
#include "str.h"
#include "bool.h"
#include "if.h"
#include "var.h"
//#include "func.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
