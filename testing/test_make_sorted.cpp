#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    int ar[] = {1, 2, 3};
    make_sorted(ar, 3);
    EXPECT_TRUE(std::is_sorted(ar, ar + 3));
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    int ar[] = {3, 2, 1};
    make_sorted(ar, 3);
    EXPECT_TRUE(std::is_sorted(ar, ar + 3));
}

TEST(MakeSortedTests, SimpleSortAverageArray) {
    int ar[] = {10, 2, 5, 1, 8};
    make_sorted(ar, 5);
    EXPECT_TRUE(std::is_sorted(ar, ar + 5));
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    int ar[] = {2, 1, 2, 1};
    make_sorted(ar, 4);
    EXPECT_TRUE(std::is_sorted(ar, ar + 4));
}

RC_GTEST_PROP(MakeSortedTests, PropertyAfterSortingValuesAreInAscendingOrder, (std::vector<int> values)) {
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);
    make_sorted(ar, (int)values.size());
    std::sort(values.begin(), values.end());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, ar));
    free(ar);
}