#include <gtest/gtest.h>
#include "Goomba.h"
#include "Mario.h"
#include "Pipe.h"
#include "SpriteMaker.h"
#include "file_util.h"

namespace {

    SpriteMaker* shared_resource_;

    class EntityCollisionTest: public ::testing::Test {
    protected:

        Mario * mario;

        EntityCollisionTest() {}

        virtual ~EntityCollisionTest() {}

        virtual void SetUp() {

        }

    };
}

TEST_F(EntityCollisionTest, TestRuns)
{
    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
    std::cout << "Running main() from gtest_main.cc\n";
    ::testing::GTEST_FLAG(output) = "xml:hello.xml";
    testing::InitGoogleTest(&argc, argv);
    shared_resource_ = new SpriteMaker(findRootDirectory(argv[0]) + "resources/");
    return RUN_ALL_TESTS();
}