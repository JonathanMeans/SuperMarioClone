#include <file_util.h>
#include <sys/stat.h>
#include <stdexcept>

bool dirExists(const std::string& path)
{
    struct stat info;

    if(stat( path.c_str(), &info ) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

std::string findRootDirectory(const std::string& argv0)
{
    auto lastSlash = argv0.rfind('/');
    auto directory = argv0.substr(0, lastSlash + 1);
    while (!dirExists(directory + "/resources"))
    {
        lastSlash = argv0.rfind('/', lastSlash - 1);
        if (lastSlash == 0 || lastSlash == std::string::npos)
            throw std::runtime_error("Unable to find project root");
        directory = argv0.substr(0, lastSlash + 1);
    }
    return directory;
}

