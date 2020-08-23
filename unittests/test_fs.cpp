#include <file_util.h>
#include <gtest/gtest.h>

// TODO: This method is not robust. If the user has
// the build directory on the system PATH, it will
// make bad assumptions. Try to reimplement with readlink
// and not call this at all.

TEST(FilesystemUtils, FindRootDirFromCommand)
{
    const auto argv0 = "SuperMarioBros";
    const auto expectedOutput = "..";
    EXPECT_EQ(expectedOutput, findRootDirectory(argv0));
}

TEST(FilesystemUtils, FindRootDirFromRootDir)
{
    const auto argv0 = "cmake-build-debug/SuperMarioBros";
    const auto expectedOutput = ".";
    EXPECT_EQ(expectedOutput, findRootDirectory(argv0));
}

TEST(FilesystemUtils, FindRootDirFromExternalDir)
{
    const auto argv0 = "../SuperMario/cmake-build-debug/SuperMarioBros";
    const auto expectedOutput = "../SuperMario/";
    EXPECT_EQ(expectedOutput, findRootDirectory(argv0));
}
