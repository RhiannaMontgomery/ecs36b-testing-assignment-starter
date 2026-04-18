#ifndef TESTINGANDDEBUGGING_TEST_HELPERS_H
#define TESTINGANDDEBUGGING_TEST_HELPERS_H

#include <vector>
#include <algorithm>
#include <string>
#include "rapidcheck.h"

/**
 * Copy the elements from vector_values into array values.
 * Space for array_values needs to already be allocated.
 */
template <typename T>
void copy_vector_to_array(const std::vector<T>& vector_values, T* array_values) {
    std::copy(vector_values.cbegin(), vector_values.cend(), array_values);
}

/**
 * Check that the elements in vector_values are the same as those in array_values.
 * array_values needs to have the same length as vector_values.
 */
template <typename T>
bool elements_in_vector_and_array_are_same(const std::vector<T>& vector_values, const T* array_values) {
    return std::equal(vector_values.cbegin(), vector_values.cend(), array_values);
}

// Helper functions for RapidCheck and argument parsing tests
rc::Gen<std::string> word_generator();
std::vector<std::string> vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers);

#endif //TESTINGANDDEBUGGING_TEST_HELPERS_H