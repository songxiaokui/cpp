//
// Created by austsxk on 2021/8/9.
//

// 创建一个线 将其转化为三角形
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "string.h"

const std::vector<std::string> DEFAULT_SCALAR_LIST = {{"a"}, {"abc"}, {"d"}, {"e"}};
int main() {
    // 方案1
    std::string name[2] = {{"a"}, {"b"}};
    std::cout << name[0] << std::endl;
    std::cout << name[1] << std::endl;
    std::cout << DEFAULT_SCALAR_LIST.size() << std::endl;
    // 判断某个字符串在字符串数组中
    std::string a = "a";
//    for (int i = 0; i < name->size(); i++) {
//        if (a == name[i]) {
//            std::cout << "a is in list!" << std::endl;
//        }
//    }
    // 方案2
//    std::vector<std::string> testvec;
//    testvec.emplace_back("a");
//    testvec.emplace_back("b");

//    std::vector<std::string> testvec = {{"c"}, {"b"}};
//    testvec.emplace_back("a");
//    testvec.emplace_back("b");

    auto iter  = std::find(DEFAULT_SCALAR_LIST.begin(),DEFAULT_SCALAR_LIST.end(),"abc");
    if (iter == DEFAULT_SCALAR_LIST.end()){
        //none
        std::cout << "not found" << std::endl;
    } else {
        //todo
        std::cout << "ok" << std::endl;
    }

    // 判断字符串是否相等
    if (strcmp(a.c_str(), name[0].c_str()) == 0 ) {
        std::cout << "ok" << std::endl;
    }

}