//
// Created by Tal on 17-Nov-20.
//

#ifndef TARGIL4_LO_LEAGASHA_Q1_DAY_H
#define TARGIL4_LO_LEAGASHA_Q1_DAY_H

#include "List.h"

using namespace lst;
namespace day {
    class Day {
        List lst;
    public:
        List *get_list() { return &lst; }
        List *operator->() { return get_list(); }
    };
}
#endif //TARGIL4_LO_LEAGASHA_Q1_DAY_H
