#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"
#include "test_helpers.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    int ar[] = {1, 5, 10, 2, 8};
    EXPECT_EQ(min_index_of_array(ar, 5), 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    int ar[] = {10, 5, 10, 2, 1};
    EXPECT_EQ(min_index_of_array(ar, 5), 4);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    int ar[] = {10, 5, 1, 2, 8};
    EXPECT_EQ(min_index_of_array(ar, 5), 2);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    int ar[] = {10, 1, 10, 1, 8};
    EXPECT_EQ(min_index_of_array(ar, 5), 1);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    int ar[] = {10, 5, 1, 2, 8};
    int original[] = {10, 5, 1, 2, 8};
    min_index_of_array(ar, 5);
    for(int i=0; i<5; ++i) EXPECT_EQ(ar[i], original[i]);
}

RC_GTEST_PROP(MinIndexOfArrayTests, PropertyFindMinIndex, (const std::vector<int>& values)) {
    RC_PRE(!values.empty());
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);

    int min_idx = min_index_of_array(ar, (int)values.size());
    RC_ASSERT(min_idx >= 0 && min_idx < (int)values.size());

    int min_val = ar[min_idx];
    for (int val: values) {
        RC_ASSERT(min_val <= val);
    }
    free(ar);
}

RC_GTEST_PROP(MinIndexOfArrayTests, PropertyArrayDoesNotChange, (const std::vector<int>& values)) {
    RC_PRE(!values.empty());
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);
    min_index_of_array(ar, (int)values.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, ar));
    free(ar);
}