#ifndef _TKL_H_
#define _TKL_H_

typedef struct version
{
    int major, minor, update;
} version;

const struct version getVersion();

#endif
