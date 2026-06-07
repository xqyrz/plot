//
// Created by 25137 on 26-6-1.
//

#include "mdb.h"
MDB* MDB::instance()
{
    static MDB inst;
    return &inst;
}
