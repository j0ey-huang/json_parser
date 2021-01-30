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

static inline void test_literal(const std::string json, Vtype val) {
    Parser parser(json);
    expect_eq<int>(PARSE_OK, parser.parse());
    expect_eq<int>(val, parser.getValue().type);
}

static inline void test_number(double expect, const std::string json) {
    Parser parser(json);
    expect_eq<int>(PARSE_OK, parser.parse());
    expect_eq<int>(_NUMBER, parser.getValue().type);
    expect_eq<double>(expect, parser.getValue().num);
}

#define EXPECT_EQ(expect, actual)\
    do {\
        test_count++;\
        if (expect == actual)\
            test_pass++;\
        else {\
            std::cerr << __FILE__ << ":" << __LINE__ << ":\texpect: " <<  expect << "\tactual: " << actual << std::endl;\
            main_ret = 1;\
        }\
    } while(0)

#define GENERAL_TEST(json, val)\
    Parser parser(json);\
    EXPECT_EQ(PARSE_OK, parser.parse());\
    EXPECT_EQ(val, parser.getValue().type)

#define TEST_LITERAL(json, val)\
    do {\
        GENERAL_TEST(json, val);\
    } while(0)

#define TEST_NUMBER(expect, json)\
    do {\
        GENERAL_TEST(json, _NUMBER);\
        EXPECT_EQ(expect, parser.getValue().num);\
    } while(0)
/* ... */

static void test_parse() {
    TEST_LITERAL("\t null \n", _NULL);
    TEST_LITERAL("\ntrue\t", _TRUE);
    TEST_LITERAL(" false", _FALSE);
    TEST_NUMBER(0.0, "0");
    TEST_NUMBER(0.0, "-0");
    TEST_NUMBER(0.0, "-0.0");
    TEST_NUMBER(1.0, "1");
    TEST_NUMBER(-1.0, "-1");
    TEST_NUMBER(1.5, "1.5");
    TEST_NUMBER(-1.5, "-1.5");
    TEST_NUMBER(3.1416, "3.1416");
    TEST_NUMBER(1E10, "1E10");
    TEST_NUMBER(1e10, "1e10");
    TEST_NUMBER(1E+10, "1E+10");
    TEST_NUMBER(1E-10, "1E-10");
    TEST_NUMBER(-1E10, "-1E10");
    TEST_NUMBER(-1e10, "-1e10");
    TEST_NUMBER(-1E+10, "-1E+10");
    TEST_NUMBER(-1E-10, "-1E-10");
    TEST_NUMBER(1.234E+10, "1.234E+10");
    TEST_NUMBER(1.234E-10, "1.234E-10");
    /*invalid number*/
    test_number(0.0, "1e-10000");
    test_number(0, "+0");
    test_number(0, "+1");
    test_number(0, ".123"); /* at least one digit before '.' */
    test_number(0, "1.");   /* at least one digit after '.' */
    test_number(0, "INF");
    test_number(0, "inf");
    test_number(0, "NAN");
    test_number(0, "nan");
    /* ... */
}

int main() {
    test_parse();
    std::cout << test_pass << "/" << test_count << "(" << test_pass * 100.0 / test_count << "%) passed" << std::endl;
    return main_ret;
}