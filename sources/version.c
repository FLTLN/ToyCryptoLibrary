#include "tcl.h"

#define VERSION_MAJOR  0 
#define VERSION_MINOR  0
#define VERSION_UPDATE 0

const struct version getVersion()
{
    struct version v;
    v.major = VERSION_MAJOR;
    v.minor = VERSION_MINOR;
    v.update = VERSION_UPDATE;
    return v;
}