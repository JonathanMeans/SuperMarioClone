#include <file_util.h>
#include <experimental/filesystem>

std::string findRootDirectory(const std::string& argv0)
{
    auto lastSlash = argv0.rfind('/');
    auto directory = argv0.substr(0, lastSlash + 1);
    while (!std::experimental::filesystem::exists(directory + "/resources"))
    {
        lastSlash = argv0.rfind('/', lastSlash - 1);
        if (lastSlash == 0 || lastSlash == std::string::npos)
            throw std::runtime_error("Unable to find project root");
        directory = argv0.substr(0, lastSlash + 1);
    }
    return directory;
}