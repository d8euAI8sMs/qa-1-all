#include <gtest/gtest.h>

#include "tests/iscorrect.test.h"

int main(int argc, char **argv) {
    bool xml = false;

    if (argc > 1)
    {
        if (std::strcmp(argv[1], "-a") == 0) xml = true;
        if (std::strcmp(argv[1], "-b") == 0) xml = false;
    }

    if (xml)
    {
        ::testing::GTEST_FLAG(output) = "xml:report.xml";
    }

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
