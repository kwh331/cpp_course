//
// Created by kwh331 on 6/27/2018.
//

#include "test_big_int_class.h"

using std::cout;

void test_bigint_class() {

    cout << "Testing started.\n";
    std::vector<bool> test_results;
    test_results.push_back((bigint("5946") > bigint("4566")) == 1);
    test_results.push_back((bigint("5946") < bigint("4656")) == 0);
    test_results.push_back(bigint("4555") == bigint("4554") == 0);
    test_results.push_back(bigint("-4555") <= bigint("-4555") == 1);
    test_results.push_back(bigint("-34") >= bigint("-36") == 1);
    test_results.push_back(bigint("-45") > bigint("-46") == 1);
    test_results.push_back(bigint("45") != bigint("45") == 0);
    test_results.push_back((bigint("88") + bigint("99")).to_string() == "187");
    test_results.push_back((bigint("11") + bigint("999")).to_string() == "1010");
    test_results.push_back((bigint("0") + bigint("999")).to_string() == "999");
    test_results.push_back((bigint("33") - bigint("22")).to_string() == "11");
    test_results.push_back((bigint("11") + bigint("-33")).to_string() == "-22");
    test_results.push_back((bigint("11") - bigint("33")).to_string() == "-22");
    test_results.push_back((bigint("11") - bigint("-33")).to_string() == "44");
    test_results.push_back((bigint("-11") - bigint("33")).to_string() == "-44");
    test_results.push_back((bigint("88888333") + bigint("999999999933")).to_string() == "1000088888266");
    test_results.push_back((bigint("-345") + bigint("-123")).to_string() == "-468");
    test_results.push_back((bigint("-1300") + bigint("256")).to_string() == "-1044");
    test_results.push_back((bigint("7456") + bigint("-123")).to_string() == "7333");
    test_results.push_back((bigint("-3566") + bigint("-1203")).to_string() == "-4769");
    test_results.push_back((bigint("333") + bigint("-444")).to_string() == "-111");
    test_results.push_back((bigint("333") - bigint("444")).to_string() == "-111");
    test_results.push_back((bigint("3566") - bigint("1203")).to_string() == "2363");
    test_results.push_back((bigint("3566") - bigint("-1203")).to_string() == "4769");
    test_results.push_back((bigint("-3566") - bigint("-1203")).to_string() == "-2363");
    test_results.push_back((bigint("345") > bigint("344")) == 1);
    test_results.push_back((bigint("3566") == bigint("3566")) == 1);
    test_results.push_back((bigint("3566") >= bigint("2344")) == 1);
    test_results.push_back((bigint("3566") < bigint("0")) == 0);
    test_results.push_back((bigint("345") > bigint("344")) == 1);
    test_results.push_back((bigint("-9999") < bigint("-88")) == 1);
    test_results.push_back(((bigint("-9999") > bigint("-888808"))) == 1);
    test_results.push_back(((bigint("-88")) < bigint("-78")) == 1);
    test_results.push_back((bigint("3566") * bigint("1203")).to_string() == "4289898");
    test_results.push_back((bigint("-3566") * bigint("-1203")).to_string() == "4289898");
    test_results.push_back(((bigint("3566") * bigint("0")).to_string() == "0"));

    int passed = 0;
    int failed = 0;
    for (const auto &v: test_results) {
        if (v == 1) {
            cout << '.';
            ++passed;
        } else {
            cout << 'F';
            ++failed;
        }
    }
    cout << '\n';
    cout << "Passed " << passed << ". ";
    cout << "Failed " << failed << ".\n";
}