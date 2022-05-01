//
// Created by vladv on 30.04.2022.
//

#include "queue.hpp"
#include "gtest/gtest.h"

TEST(eq, equal) {
    EXPECT_EQ(1, 1);
}


int main() {
    Ssvtl::Queue<int> q;

    q.push(3);
    q.push(2);
    q.push(4);

    Ssvtl::List<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(4);

    for (auto& elem: list) {
        elem++;
    }

    for (auto& elem: list) {
        std::cout << elem << ' ';
    }

    return 0;
}