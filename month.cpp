//
// Created by Tal on 17-Nov-20.
//

#include "month.h"

namespace month {
    bool Month::is_legal_January(int num) {
        return ((num >= min_month_size) && (num <= month_size::January));
    }
    bool Month::is_legal_February(int num) {
        return ((num >= min_month_size) && (num <= month_size::February));
    }
    bool Month::is_legal_March(int num) {
        return ((num >= min_month_size) && (num <= month_size::March));
    }
    bool Month::is_legal_April(int num) {
        return ((num >= min_month_size) && (num <= month_size::April));
    }
    bool Month::is_legal_May(int num) {
        return ((num >= min_month_size) && (num <= month_size::May));
    }
    bool Month::is_legal_June(int num) {
        return ((num >= min_month_size) && (num <= month_size::June));
    }
    bool Month::is_legal_July(int num) {
        return ((num >= min_month_size) && (num <= month_size::July));
    }
    bool Month::is_legal_August(int num) {
        return ((num >= min_month_size) && (num <= month_size::August));
    }
    bool Month::is_legal_September(int num) {
        return ((num >= min_month_size) && (num <= month_size::September));
    }
    bool Month::is_legal_October(int num) {
        return ((num >= min_month_size) && (num <= month_size::October));
    }
    bool Month::is_legal_November(int num) {
        return ((num >= min_month_size) && (num <= month_size::November));
    }
    bool Month::is_legal_December(int num) {
        return ((num >= min_month_size) && (num <= month_size::December));
    }
}
