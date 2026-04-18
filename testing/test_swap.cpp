#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"

TEST(SwapTests, SimpleSwapTwoValues) {
    int a = 5;
    int b = 10;
    swap(&a, &b);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 5);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    int ar[] = {1, 2, 3, 4, 5};
    swap(&ar[1], &ar[3]); // swap 2 and 4
    EXPECT_EQ(ar[1], 4);
    EXPECT_EQ(ar[3], 2);
    EXPECT_EQ(ar[0], 1);
    EXPECT_EQ(ar[2], 3);
    EXPECT_EQ(ar[4], 5);
}

RC_GTEST_PROP(SwapTests, PropertySwapTwoValues, (int a_start, int b_start)) {
    int a = a_start;
    int b = b_start;
    swap(&a, &b);
    RC_ASSERT(a == b_start);
    RC_ASSERT(b == a_start);
}

RC_GTEST_PROP(SwapTests, PropertySwapValuesInArray, (const std::vector<int>& values)) {
    RC_PRE((int)values.size() >= 2);
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);

    int i = *rc::gen::inRange(0, (int)values.size());
    int j = *rc::gen::inRange(0, (int)values.size());

    int val_i = ar[i];
    int val_j = ar[j];

    swap(&ar[i], &ar[j]);

    RC_ASSERT(ar[i] == val_j);
    RC_ASSERT(ar[j] == val_i);

    for (int k = 0; k < (int)values.size(); ++k) {
        if (k != i && k != j) {
            RC_ASSERT(ar[k] == values[k]);
        }
    }
    free(ar);
}