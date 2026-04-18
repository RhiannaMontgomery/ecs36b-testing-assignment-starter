#include "test_helpers.h"

/*
 * Creates a generator for a string made up of characters from [a - z].
 * This is used for generating mock command line argument strings.
 */

rc::Gen<std::string> word_generator() {
    return rc::gen::string<std::string> (
        rc::gen::map(rc::gen::inRange('a', 'z'), [](char c) { return c; })
    );
}

/*
 * Converts a vector of integers into a vector of strings.
 * This simulates the 'argv' format received by the main function.
 */

std::vector<std::string> vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    std::vector<std::string> strings;
    for (int n : numbers) {
        strings.push_back(std::to_string(n));
    }
    return strings;
}