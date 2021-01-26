#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "myjson.h"

using namespace myjson;

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

template<typename T>
static inline void expect_eq(T expect, T actual){
    test_count++;
    if(expect == actual) test_pass++;
    else{
        std::cerr << __FILE__ << ":" << __LINE__ << ":\texpect: " <<  expect << "\tactual: " << actual << std::endl;
        main_ret = 1;
    }
}

static void test_parse_null() {
    myjson::Item v;
    v.type = myjson::_TRUE;
    expect_eq<int>(PARSE_OK, parse(v, "null"));
    expect_eq<int>(_NULL, get_type(v));
}

/* ... */

static void test_parse() {
    test_parse_null();
    /* ... */
}

int main() {
    test_parse();
    std::cout << test_pass << "/" << test_count << "(" << test_pass * 100.0 / test_count << "%) passed" << std::endl;
    return main_ret;
}