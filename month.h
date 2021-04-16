//
// Created by Tal on 17-Nov-20.
//

#ifndef TARGIL4_LO_LEAGASHA_Q1_MONTH_H
#define TARGIL4_LO_LEAGASHA_Q1_MONTH_H

#include "day.h"

using namespace day;

namespace month {
    class month_names {
    public:
        static const int January = 1;
        static const int February = 2;
        static const int March = 3;
        static const int April = 4;
        static const int May = 5;
        static const int June = 6;
        static const int July = 7;
        static const int August = 8;
        static const int September = 9;
        static const int October = 10;
        static const int November = 11;
        static const int December = 12;
    };

    class month_size {
    public:
        static const int January = 31;
        static const int February = 29;
        static const int March = 31;
        static const int April = 30;
        static const int May = 31;
        static const int June = 30;
        static const int July = 30;
        static const int August = 31;
        static const int September = 30;
        static const int October = 31;
        static const int November = 30;
        static const int December = 31;
    };

    class Month {
    public:
        static const int max_month_size = 31;
        static const int min_month_size = 1;
    private:
//        const int name = month_names::January;/*defaulting to January*/ //never used
        Day days[max_month_size];/*an array with the size of '31' days:*/

/*-----Month methods------*/
    public:
        Day *get_days() { return days; } /*TODO: not sure if it will cause problems in the future. if it does I should change 'name' to public*/

/*---CheckLegalMonths---*/
        static bool is_legal_January(int num);
        static bool is_legal_February(int num);
        static bool is_legal_March(int num);
        static bool is_legal_April(int num);
        static bool is_legal_May(int num);
        static bool is_legal_June(int num);
        static bool is_legal_July(int num);
        static bool is_legal_August(int num);
        static bool is_legal_September(int num);
        static bool is_legal_October(int num);
        static bool is_legal_November(int num);
        static bool is_legal_December(int num);

/*+Operators+*/
        Day &operator[](int day) { return get_days()[day]; }
    };
}
#endif //TARGIL4_LO_LEAGASHA_Q1_MONTH_H
