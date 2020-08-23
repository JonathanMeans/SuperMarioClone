#include <file_util.h>

std::string findRootDirectory(const std::string& argv0)
{
    const auto lastSlash = argv0.rfind('/');
    if (lastSlash == std::string::npos)
        return "..";
    const auto secondLastSlash = argv0.rfind('/', lastSlash - 1);
    if (secondLastSlash == std::string::npos)
        return ".";
    return argv0.substr(0, secondLastSlash + 1);
}