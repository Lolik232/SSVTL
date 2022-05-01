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

    Ssvtl::List<std::vector<int>> list = {{1, 2},
                                          {3, 4}};

    Ssvtl::List<std::vector<int>> nl = {{42},
                                        {1, 2, 3, 4},
                                        {5}};

    list.splice(++list.begin(), nl);

//    for (auto &elem: list) {
//        for (auto &x: elem) {
//            x++;
//        }
//    }

    for (auto &elem: list) {
        for (auto &x: elem) {
            std::cout << x << ' ';
        }
    }

    for (auto &elem: nl) {
        for (auto &x: elem) {
            std::cout << x << ' ';
        }
    }

    return 0;
}