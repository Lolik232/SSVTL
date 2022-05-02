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

    Ssvtl::List<int> list = {1, 2};

    Ssvtl::List<int> nl = {421, 2, 3, 5};

    nl.reverse();

    for (auto &elem: list) {
        std::cout << elem << ' ';
    }

    for (auto &elem: nl) {
        std::cout << elem << ' ';
    }

    return 0;
}