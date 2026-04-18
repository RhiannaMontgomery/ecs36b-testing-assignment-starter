#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    int original[] = {1, 2, 3, 4, 5};
    int* copy = copy_array(original, 5);
    for(int i=0; i<5; ++i) EXPECT_EQ(original[i], copy[i]);
    free(copy);
}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    int original[] = {1, 2, 3};
    int before[] = {1, 2, 3};
    int* copy = copy_array(original, 3);
    for(int i=0; i<3; ++i) EXPECT_EQ(original[i], before[i]);
    free(copy);
}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    int original[] = {1, 2, 3};
    int* copy = copy_array(original, 3);
    EXPECT_NE(original, copy);
    free(copy);
}

RC_GTEST_PROP(CopyArrayTests, PropertyValuesAreSame, (const std::vector<int>& values)) {
    if (values.empty()) return;
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);
    int* copy = copy_array(ar, (int)values.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, copy));
    free(copy);
    free(ar);
}

RC_GTEST_PROP(CopyArrayTests, PropertyOriginalDoesNotChange, (const std::vector<int>& values)) {
    if (values.empty()) return;
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);
    int* copy = copy_array(ar, (int)values.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, ar));
    free(copy);
    free(ar);
}

RC_GTEST_PROP(CopyArrayTests, PropertyCopyWasMade, (const std::vector<int>& values)) {
    RC_PRE(!values.empty());
    int* ar = (int*)malloc(values.size() * sizeof(int));
    copy_vector_to_array(values, ar);
    int* copy = copy_array(ar, (int)values.size());
    RC_ASSERT(ar != copy);
    free(copy);
    free(ar);
}