//
// Created by Tal on 15-Nov-20.
//

#ifndef TARGIL4_LO_LEAGASHA_Q1_CALENDAR_H
#define TARGIL4_LO_LEAGASHA_Q1_CALENDAR_H

#include <iostream>
#include "month.h"

using namespace month;

namespace calendar {
    class Calendar {

    private:
        static const int num_of_months = 12;
        Month months[num_of_months];
        /*+Keys+:*/
        class Keys_menu1 {
        public:
            static const int By_Date = 1;
            static const int By_Day_In_Year = 2;
            static const int Exit_Menu = 0;
        };
        class Keys_menu2 {
        public:
            static const int List_Meetings = 1;
            static const int Add_Meeting = 2;
            static const int EDIT_Day = 3;
            static const int Return_To_Main_Menu = 0;
        };
        class Keys_EditMode {
        public:
            static const int Edit_Meeting = 1;
            static const int Remove_Meeting = 2;
            static const int Return_To_Day_Menu = 0;
        };
        class Signals {
        public:
            static const int Good_Input = -3;
            static const int Bad_Input = -2;
            static const int Cancel = -1;
        };

    private:
/*-----Calendar methods------*/
        void run_menu2(int day, int month);
        int convert_num_to_day_and_month_and_run_menu2(int num);
        void run_input_By_Date();
        void run_input_By_Day_In_Year();
        void run_List_Meetings(int day, int month);
        void run_Add_Meeting(int day, int month);
        void run_EDIT_day(int day, int month);
        static void run_EDIT_Meeting(Day &day, Node *node);
        static void run_Remove_Meeting(Day &day, Node *node);
        void switch_menu1(int input);
        void switch_menu2(int day, int month, int input);
        void run_menu1();
        static void display_menu1();
        static void display_menu2(int day, int month);
        static int check_legal_meeting(Node *newMtg, Day &day, Node **insert_after_this_node);
        static bool is_clashing_meetings(Day &day, Node *newMtg, Node **clshMtg, Node **insert_after_this_node);
        int is_legal_day_and_month(int day_int, int month_int);
        static void display_EDIT_day_menu(Node *node);
        void run_EDIT_meeting_menu(Day &day, Node *node);
        static int switch_EditMode(Day &day, Node *node, int input);
        /*---CheckLegalMonths---*/
        void is_legal_January_and_if_true_run_menu2(int num);
        void is_legal_February_and_if_true_run_menu2(int num);
        void is_legal_March_and_if_true_run_menu2(int num);
        void is_legal_April_and_if_true_run_menu2(int num);
        void is_legal_May_and_if_true_run_menu2(int num);
        void is_legal_June_and_if_true_run_menu2(int num);
        void is_legal_July_and_if_true_run_menu2(int num);
        void is_legal_August_and_if_true_run_menu2(int num);
        void is_legal_September_and_if_true_run_menu2(int num);
        void is_legal_October_and_if_true_run_menu2(int num);
        void is_legal_November_and_if_true_run_menu2(int num);
        void is_legal_December_and_if_true_run_menu2(int num);
    public:
        void run() { run_menu1(); }

        /*+operators+*/
        Month &operator[](int i);
    };
}

#endif //TARGIL4_LO_LEAGASHA_Q1_CALENDAR_H
