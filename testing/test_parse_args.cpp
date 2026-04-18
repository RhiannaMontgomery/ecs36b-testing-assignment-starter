#include <cstdlib>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    std::vector<std::string> strings;
    strings.push_back("program_name");
    for (int n : numbers) {
        strings.push_back(std::to_string(n));
    }
    return strings;
}

TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    char* argv[] = {(char*)"prog", (char*)"10", (char*)"20", (char*)"30"};
    int* ar_out = nullptr;
    int len_out = 0;
    parse_args(4, argv, &ar_out, &len_out);

    ASSERT_EQ(len_out, 3);
    ASSERT_NE(ar_out, nullptr);
    EXPECT_EQ(ar_out[0], 10);
    EXPECT_EQ(ar_out[1], 20);
    EXPECT_EQ(ar_out[2], 30);
    free(ar_out);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    char* argv[] = {(char*)"prog"};
    int* ar_out = nullptr;
    int len_out = 0;
    parse_args(1, argv, &ar_out, &len_out);
    EXPECT_EQ(len_out, 0);
    EXPECT_EQ(ar_out, nullptr);
}

RC_GTEST_PROP(ParseArgsTests, PropertyCheckArgumentsParsedSuccessfully, (const std::vector<int>& values)) {
    RC_PRE(!values.empty());
    auto strings = vector_of_ints_to_vector_of_strings(values);
    int argc = (int)strings.size();
    char** argv = (char**)malloc(argc * sizeof(char*));
    for(int i=0; i<argc; ++i) argv[i] = strdup(strings[i].c_str());

    int* ar_out = nullptr;
    int len_out = 0;
    parse_args(argc, argv, &ar_out, &len_out);

    RC_ASSERT(len_out == (int)values.size());
    RC_ASSERT(ar_out != nullptr);
    RC_ASSERT(elements_in_vector_and_array_are_same(values, ar_out));

    for(int i=0; i<argc; ++i) free(argv[i]);
    free(argv);
    free(ar_out);
}

RC_GTEST_PROP(ParseArgsTests, PropertyCheckParseNoArgs, ()) {
    char* argv[] = {(char*)"prog"};
    int* ar_out = nullptr;
    int len_out = -1;
    parse_args(1, argv, &ar_out, &len_out);
    RC_ASSERT(len_out == 0);
    RC_ASSERT(ar_out == nullptr);
}