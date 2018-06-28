
//
// Created by kwh331 on 6/27/2018.
//

#include "test_big_int_class.h"

using std::cout;

void test_comparisons(std::vector<bool> &);

void test_addition(std::vector<bool> &);

void test_subtraction(std::vector<bool> &);

void test_multiplication(std::vector<bool> &);

void test_division(std::vector<bool> &);

void test_bigint_class() {
    cout << "Testing started.\n";
    std::vector<bool> test_results;
    test_comparisons(test_results);
    test_addition(test_results);
    test_subtraction(test_results);
    test_multiplication(test_results);
    test_division(test_results);
    int passed = 0, failed = 0;
    for (const auto &v: test_results) {
        if (v == 1) {
            cout << '.';
            ++passed;
        } else {
            cout << 'F';
            ++failed;
        }
    }
    cout << "\nPassed successfuly on " << static_cast<int>((passed / 41.0) * 100.0) << "%. \n";
}

void test_comparisons(std::vector<bool> &test_results) {
    test_results.push_back((bigint("345") > bigint("344")) == 1);
    test_results.push_back((bigint("3566") == bigint("3566")) == 1);
    // 3 4
    test_results.push_back((bigint("3566") >= bigint("2344")) == 1);
    test_results.push_back((bigint("3566") < bigint("0")) == 0);
    // 5 6
    test_results.push_back((bigint("345") > bigint("344")) == 1);
    test_results.push_back((bigint("-9999") < bigint("-88")) == 1);
    // 7 8
    test_results.push_back(((bigint("-9999") > bigint("-888808"))) == 1);
    test_results.push_back(((bigint("-88")) < bigint("-78")) == 1);
    // 9 10
    test_results.push_back((bigint("5946") > bigint("4566")) == 1);
    test_results.push_back((bigint("5946") < bigint("4656")) == 0);
    // 11 12
    test_results.push_back(bigint("4555") == bigint("4554") == 0);
    test_results.push_back(bigint("-4555") <= bigint("-4555") == 1);
    // 13 14
    test_results.push_back(bigint("-34") >= bigint("-36") == 1);
    test_results.push_back(bigint("-45") > bigint("-46") == 1);
    // 15 16
    test_results.push_back(bigint("47") > bigint("-33") == 1);
    test_results.push_back(bigint("45") != bigint("45") == 0);
}

void test_addition(std::vector<bool> &test_results) {
    test_results.push_back((bigint("88") + bigint("99")).to_string() == "187");
    test_results.push_back((bigint("11") + bigint("999")).to_string() == "1010");
    // 19 20
    test_results.push_back((bigint("0") + bigint("999")).to_string() == "999");
    test_results.push_back((bigint("11") + bigint("-33")).to_string() == "-22");
    // 21 22
    test_results.push_back((bigint("88888333") + bigint("999999999933")).to_string() == "1000088888266");
    test_results.push_back((bigint("-345") + bigint("-123")).to_string() == "-468");
    // 23 24
    test_results.push_back((bigint("-1300") + bigint("256")).to_string() == "-1044");
    test_results.push_back((bigint("7456") + bigint("-123")).to_string() == "7333");
    // 25 26
    test_results.push_back((bigint("-3566") + bigint("-1203")).to_string() == "-4769");
    test_results.push_back((bigint("333") + bigint("-444")).to_string() == "-111");
}

void test_subtraction(std::vector<bool> &test_results) {
    test_results.push_back((bigint("33") - bigint("22")).to_string() == "11");
    test_results.push_back((bigint("11") - bigint("33")).to_string() == "-22");
    // 29 30
    test_results.push_back((bigint("11") - bigint("-33")).to_string() == "44");
    test_results.push_back((bigint("-11") - bigint("33")).to_string() == "-44");
    // 31 32
    test_results.push_back((bigint("333") - bigint("444")).to_string() == "-111");
    test_results.push_back((bigint("3566") - bigint("1203")).to_string() == "2363");
    // 33 34
    test_results.push_back((bigint("3566") - bigint("-1203")).to_string() == "4769");
    test_results.push_back((bigint("-3566") - bigint("-1203")).to_string() == "-2363");

}

void test_multiplication(std::vector<bool> &test_results) {
    test_results.push_back((bigint("3566") * bigint("1203")).to_string() == "4289898");
    test_results.push_back((bigint("-3566") * bigint("-1203")).to_string() == "4289898");
    test_results.push_back(((bigint("3566") * bigint("0")).to_string() == "0"));

}

void test_division(std::vector<bool> &test_results) {
    auto one = bigint("-9999");
    auto two = bigint("88");
    auto three = bigint("-88");
    auto four = bigint("3455");
    auto five = bigint("-348");
    auto six = bigint("0");
    auto result = one / two;
    test_results.push_back(result.to_string() == "-114");
    result = one / three;
    test_results.push_back(result.to_string() == "113");
    result = four / five;
    test_results.push_back(result.to_string() == "-10");
    result = six / two;
    test_results.push_back(result.to_string() == "0");
}