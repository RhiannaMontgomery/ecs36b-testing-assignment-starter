#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    int ar[] = {1, 2, 3};
    int* sorted = get_sorted(ar, 3);
    EXPECT_TRUE(std::is_sorted(sorted, sorted + 3));
    free(sorted);
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    int ar[] = {3, 2, 1};
    int* sorted = get_sorted(ar, 3);
    EXPECT_TRUE(std::is_sorted(sorted, sorted + 3));
    free(sorted);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    int ar[] = {10, 5, 2};
    int* sorted = get_sorted(ar, 3);
    EXPECT_TRUE(std::is_sorted(sorted, sorted + 3));
    free(sorted);
}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    int ar[] = {2, 1, 2};
    int* sorted = get_sorted(ar, 3);
    EXPECT_TRUE(std::is_sorted(sorted, sorted + 3));
    free(sorted);
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    int ar[] = {3, 1, 2};
    int orig[] = {3, 1, 2};
    int* sorted = get_sorted(ar, 3);
    for(int i=0; i<3; ++i) EXPECT_EQ(ar[i], orig[i]);
    free(sorted);
}

TEST(GetSortedTests, SimpleCopyWasMade) {
    int ar[] = {1, 2, 3};
    int* sorted = get_sorted(ar, 3);
    EXPECT_NE(ar, sorted);
    free(sorted);
}

RC_GTEST_PROP(GetSortedTests, PropertyAfterSortingValuesAreInAscendingOrder, (std::vector<int> values)) {
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);
    int* sorted = get_sorted(ar, (int)values.size());
    std::sort(values.begin(), values.end());
    if (!values.empty()) {
        RC_ASSERT(elements_in_vector_and_array_are_same(values, sorted));
        free(sorted);
    }
    free(ar);
}

RC_GTEST_PROP(GetSortedTests, PropertyOriginalDoesNotChange, (const std::vector<int>& values)) {
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);
    int* sorted = get_sorted(ar, (int)values.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, ar));
    if (sorted) free(sorted);
    free(ar);
}

RC_GTEST_PROP(GetSortedTests, PropertyCopyWasMade, (const std::vector<int>& values)) {
    RC_PRE(!values.empty());
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);
    int* sorted = get_sorted(ar, (int)values.size());
    RC_ASSERT(ar != sorted);
    free(sorted);
    free(ar);
}