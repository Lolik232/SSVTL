//
// Created by vladv on 30.04.2022.
//

#include "queue.hpp"
#include "gtest/gtest.h"
#include <cmath>

TEST(eq, equal) {
    EXPECT_EQ(1, 1);
}

bool isPrime(const unsigned x) {
    if (x == 1)
        return false;
    else {
        int sqrtX = sqrt(x);
        for (int i = 2; i <= sqrtX; ++i)
            if (x % i == 0)
                return false;
        return true;
    }
}

int main() {
    Ssvtl::Queue<int> q;

    q.push(3);
    q.push(2);
    q.push(4);

    Ssvtl::List<int> list = {1, 2};

    Ssvtl::List<int> nl = {422, 2, 3, 5};

    list.splice(list.begin(), nl);

    list.remove_if(isPrime);

    for (auto &elem: list) {
        std::cout << elem << ' ';
    }

    for (auto &elem: nl) {
        std::cout << elem << ' ';
    }

    return 0;
}