//#include "tcl.h"
#include <iostream>

#define VERSION_MAJOR  0 
#define VERSION_MINOR  0
#define VERSION_UPDATE 0
typedef struct version
{
    int major, minor, update;
} version;

const struct version getVersion()
{
    struct version v;
    v.major = VERSION_MAJOR;
    v.minor = VERSION_MINOR;
    v.update = VERSION_UPDATE;
    return v;
}

int main()
{
    struct version v = getVersion();
    std::cout << v.major << "." << v.minor << "." << v.update << "\n";
    return 0;
}