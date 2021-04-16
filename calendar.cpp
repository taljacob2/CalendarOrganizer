//
// Created by Tal on 15-Nov-20.
//

#include "calendar.h"

namespace calendar {
    void Calendar::display_menu1() {
        std::cout << "Choose day:" << std::endl;
        std::cout << (Keys_menu1::By_Date) << ". By date (day/month)" << std::endl;
        std::cout << (Keys_menu1::By_Day_In_Year) << ". By day in year (1-365)" << std::endl;
        std::cout << (Keys_menu1::Exit_Menu) << ". Exit" << std::endl;
    }
    void Calendar::run_menu2(int day, int month) {/*TODO*/
        display_menu2(day, month);
        int input;
        std::cin >> input;
        while (input != (Keys_menu2::Return_To_Main_Menu)) {
            switch_menu2(day, month, input);

            display_menu2(day, month);
            std::cin >> input;
        }
//        std::cout << "Goodbye..." << std::endl;
    }
    void Calendar::run_List_Meetings(int day, int month) {
//        prints today's meetings.//TODO: need to check for clashed meetings and print an error if so
//        std::cout << months[month_names::January].get_days()[day].get_list();//TODO: Doesn't work for some reason
//        std::cout << months[month - 1].get_days()[day].get_list();
        std::cout << months[month - 1][day].get_list() << std::endl;
    }
    void Calendar::switch_menu2(int day, int month, int input) {
        /*note that the input is legal because we have already checked it*/
        if (input == (Keys_menu2::List_Meetings)) {
            run_List_Meetings(day, month);
        } else if (input == (Keys_menu2::Add_Meeting)) {
            run_Add_Meeting(day, month);
        } else if (input == (Keys_menu2::EDIT_Day)) {
            run_EDIT_day(day, month);
        }
    }
    void Calendar::run_EDIT_day(int day, int month) {
        Day &currDay = months[month - 1][day];
        int i = Signals::Good_Input;
        Node *node;
        while (i != Signals::Cancel) {
            int size = currDay->get_size();
            std::cout << day << "/" << month << " EDIT MODE:" << std::endl << currDay.get_list() << std::endl;
            std::cout << "Choose a meeting to edit: insert index: (" << 0 << " - " << size - 1 << "): ";
            std::cout << "(input '" << (Signals::Cancel) << "' to cancel): ";
            std::cin >> i;
            bool is_inputOKAY = false;
            while ((!is_inputOKAY) && (i != Signals::Cancel)) {
                try {
                    node = currDay->get_node_i(i);
                    is_inputOKAY = true;
                }
                catch (const char *msg) {
                    std::cout << msg << std::endl;
                    std::cout << "Choose a meeting to edit: insert index: (" << 0 << " - " << size - 1 << "): ";//TODO: fix throw
                    std::cout << "(input '" << (Signals::Cancel) << "' to cancel): ";
                    std::cin >> i;
                }
            }
            if (i != Signals::Cancel)
                run_EDIT_meeting_menu(currDay, node);
        }
    }
    void Calendar::run_EDIT_meeting_menu(Day &day, Node *node) {
        display_EDIT_day_menu(node);
        int input;
        int signal;
        std::cin >> input;
        while ((signal = switch_EditMode(day, node, input)) != Keys_EditMode::Return_To_Day_Menu) {
            if (signal == Signals::Bad_Input) {
                std::cout << "Bad input. Please try again:" << std::endl;
                display_EDIT_day_menu(node);
                std::cin >> input;
            } else break; /*else, this is a good input so break the loop*/
        }
    }
    int Calendar::switch_EditMode(Day &day, Node *node, int input) {
        if (input == Keys_EditMode::Return_To_Day_Menu)
            return input;
        else if (input == Keys_EditMode::Edit_Meeting) {/*Edit Meeting*/
            run_EDIT_Meeting(day, node);
            return Signals::Good_Input;
        } else if (input == Keys_EditMode::Remove_Meeting) {
            run_Remove_Meeting(day, node);
            return Signals::Good_Input;
        } else return Signals::Bad_Input;
    }
    void Calendar::run_EDIT_Meeting(Day &day, Node *node) {
        std::cout << "Enter new start / end hours (HH HH): (input '" << Signals::Cancel << " " << Signals::Cancel << "' to cancel)" << std::endl;
        float start, end;
        std::cin >> start >> end;
        /*remove the current node temporarily for the checks below.
         * if the edit is clashing with another meeting we will revert to the old meeting.
         * else we will keep the old replace meeting deleted forever and replace it with the new meeting instead.
        */
        Node savedMtg = Node(node);//temporary save // copy the contents for this scope only
        *node = Node(start, end);//overwrite this input as the node and check for its OKAYness:*/
        int signal;
        while ((signal = check_legal_meeting(node, day, nullptr)) == (Signals::Bad_Input)) { // defined bad hour inputed
            std::cout << "Please try again:" << std::endl;
            std::cout << "enter start and end of meeting: hours: (HH HH) (input '" << Signals::Cancel << " " << Signals::Cancel << "' to cancel)" << std::endl;
            std::cin >> start >> end;
            *node = Node(start, end);//overwrite this input as the node and check for its OKAYness:*/
        }
        if (signal == Signals::Cancel) {
            *node = savedMtg;//re-use the old meeting
        }
    }
    void Calendar::run_Remove_Meeting(Day &day, Node *node) {
        std::cout << "Meeting " << node << " Removed" << std::endl;
        /*(we print that the Meeting has been removed before we actually did it)*/
        day->removeNode(node);
    }
    void Calendar::display_EDIT_day_menu(Node *node) {
        std::cout << "you edit: " << node << std::endl;
        std::cout << (Keys_EditMode::Edit_Meeting) << ". Edit meeting" << std::endl;
        std::cout << (Keys_EditMode::Remove_Meeting) << ". Remove meeting" << std::endl;
        std::cout << (Keys_EditMode::Return_To_Day_Menu) << ". Return to day menu" << std::endl;
    }
    void Calendar::run_Add_Meeting(int day, int month) {
        float start, end;
        std::cout << "enter start and end of meeting: hours: (HH HH) (input '" << Signals::Cancel << " " << Signals::Cancel << "' to cancel)" << std::endl;
        std::cin >> start >> end;
        auto newMtg = new Node(start, end);/*create this input as a node and check for its OKAYness:*/
        Day &currDay = months[month - 1][day];
        int signal;
        Node *insert_after_this_node = nullptr;
        while ((signal = check_legal_meeting(newMtg, currDay, &insert_after_this_node)) == (Signals::Bad_Input)) { // defined bad hour inputed
            std::cout << "Please try again:" << std::endl;
            std::cout << "enter start and end of meeting: hours: (HH HH) (input '" << Signals::Cancel << " " << Signals::Cancel << "' to cancel)" << std::endl;
            std::cin >> start >> end;
            delete newMtg; /*delete old trial and create a new one instead:*/
            newMtg = new Node(start, end);/*create this new input as a node and check for its OKAYness instead*/
        }
        if (signal != Signals::Cancel) { // only if the user wished to proceed:
            currDay->addNodeAfter(insert_after_this_node, newMtg); // Works!
//            currDay->mergeSort();   // TODO - !SORT THE LIST!
        } else delete newMtg;
    }
    int Calendar::check_legal_meeting(Node *newMtg, Day &day, Node **insert_after_this_node) {
        Node *clshMtg = nullptr;
        float newStrt = newMtg->g_strt();
        float newEnd = newMtg->g_end();
        if (newMtg->g_strt() == (Signals::Cancel) && newMtg->g_end() == (Signals::Cancel)) {/*Cancel input*/
            /*print a message here if you wish*/
            return (Signals::Cancel);
        }
        if (newStrt == newEnd) {
            std::cout << "meetings must have length" << std::endl;
            return (Signals::Bad_Input);
        }
        if (newStrt > Node::max_hour_size || newEnd > Node::max_hour_size || newStrt < Node::min_hour_size || newEnd < Node::min_hour_size) {//+out of range input+
            std::cout << "inputed hours are out of range (0 - 24)" << std::endl;
            return (Signals::Bad_Input);
        }
        if (is_clashing_meetings(day, newMtg, &clshMtg, insert_after_this_node)) {/*+clashed meetings+*/ /*!FOR FINDING insert_after_this_node, THE FUNCTION ASSUMES THE LIST IS ORDERED!*/
            std::cout << "ERROR: meetings are clashing!: " << clshMtg << " and your new: " << newMtg << std::endl;
            return (Signals::Bad_Input);
        } else return (Signals::Good_Input);
    }
    bool Calendar::is_clashing_meetings(Day &day, Node *newMtg, Node **clshMtg, Node **insert_after_this_node) {
        /*check whether there are two meetings that their 'start/end' values are clashing.
         if so, return the meetings as Nodes*/
        /*!FOR FINDING insert_after_this_node, THE FUNCTION ASSUMES THE LIST IS ORDERED!*/
        /*second, check for clashing:*/
        float node_strt = 0, node_end = 0, newMtg_strt = newMtg->g_strt(), newMtg_end = newMtg->g_end();
        bool newMtg_is_before_node = false, newMtg_is_after_node = false, is_legal = false;
        Node *node = day->get_head();
        if (node == nullptr)//if the list is empty, return
            return false;
        else {
            while (node != nullptr) {
                node_strt = node->g_strt(); // extract value
                node_end = node->g_end(); // extract value

                newMtg_is_before_node = (newMtg_end <= node_strt) && (newMtg_strt <= node_strt); //+newMtg_is_before_node+
//            newMtg_is_before_node = (newMtg_end <= node_strt) && (newMtg_end <= node_end); //+newMtg_is_before_node+

                if ((newMtg_strt >= node_end) && (newMtg_end >= node_end)) { //+newMtg_is_after_node+
                    newMtg_is_after_node = true;
                    *insert_after_this_node = node;
                } else newMtg_is_after_node = false;

                is_legal = (newMtg_is_before_node || newMtg_is_after_node);
                if (!is_legal)// CHECK FOR ILLEGAL CONDITION
                    break; // <- means, we recieved an illegal meeting

                if ((node->next) == nullptr)//LEGAL
                    break;
                /*step and reset booleans:*/
                node = node->next; // step
                newMtg_is_before_node = false; //reset
                newMtg_is_after_node = false; //reset
            }
        }

        if ((is_legal) && (node->next == nullptr)) {//LEGAL
            return false;
        } else {//ILLEGAL
            *clshMtg = node;
            return true;
        }
    }
    void Calendar::display_menu2(int day, int month) {
        std::cout << day << "/" << month << ": choose an option: " << std::endl;
        std::cout << (Keys_menu2::List_Meetings) << ". List meetings" << std::endl;
        std::cout << (Keys_menu2::Add_Meeting) << ". Add meeting" << std::endl;
        std::cout << (Keys_menu2::EDIT_Day) << ". EDIT Day" << std::endl;
        std::cout << (Keys_menu2::Return_To_Main_Menu) << ". Return to main menu" << std::endl;
    }
    void Calendar::run_menu1() {
        int input;
        std::cout << "Calendar 2020" << std::endl;
        std::cout << "-------------" << std::endl;
        display_menu1();
        std::cin >> input;
        while (input != (Keys_menu1::Exit_Menu)) {
            switch_menu1(input);

            display_menu1();
            std::cin >> input;
        }
        std::cout << "Goodbye..." << std::endl;
    }
    int Calendar::convert_num_to_day_and_month_and_run_menu2(int num) {
        if (num == (Signals::Cancel)) {/*Cancel input*/
            /*print a message here if you wish*/
            return num;
        } else if (num > 365 || num < 1) {/*Bad input*/
            return (Signals::Bad_Input);
        } else {/*Good input*/
            /*converting:::*/
            /*+January+*/
            is_legal_January_and_if_true_run_menu2(num);
            num -= month_size::January;
            /*+February+*/
            is_legal_February_and_if_true_run_menu2(num);
            num -= month_size::February;
            /*+March+*/
            is_legal_March_and_if_true_run_menu2(num);
            num -= month_size::March;
            /*+April+*/
            is_legal_April_and_if_true_run_menu2(num);
            num -= month_size::April;
            /*+May+*/
            is_legal_May_and_if_true_run_menu2(num);
            num -= month_size::May;
            /*+June+*/
            is_legal_June_and_if_true_run_menu2(num);
            num -= month_size::June;
            /*+July+*/
            is_legal_July_and_if_true_run_menu2(num);
            num -= month_size::July;
            /*+August+*/
            is_legal_August_and_if_true_run_menu2(num);
            num -= month_size::August;
            /*+September+*/
            is_legal_September_and_if_true_run_menu2(num);
            num -= month_size::September;
            /*+October+*/
            is_legal_October_and_if_true_run_menu2(num);
            num -= month_size::October;
            /*+November+*/
            is_legal_November_and_if_true_run_menu2(num);
            num -= month_size::November;
            /*+December+*/
            is_legal_December_and_if_true_run_menu2(num);
            return (Signals::Good_Input);
        }
    }
    void Calendar::run_input_By_Date() {
        std::cout << "Enter day/month (DD MM): (input '" << Signals::Cancel << " " << Signals::Cancel << "' to cancel): ";
        int day_int, month_int;
        std::cin >> day_int >> month_int;
        int signal;
        while ((signal = is_legal_day_and_month(day_int, month_int)) != Signals::Cancel) {
            if (signal == Signals::Good_Input)
                break;
            std::cout << "Bad input. Please try again:" << std::endl;
            std::cout << "Enter day/month (DD MM): (input '" << Signals::Cancel << " " << Signals::Cancel << "' to cancel): ";
            std::cin >> day_int >> month_int;
        }
        run_menu2(day_int, month_int);
//~        else std::cout << "you canceled";//print a message here if you wish
    }
    void Calendar::run_input_By_Day_In_Year() {
        std::cout << "Choose a day via a number in the range of 1 - 365 (input '" << (Signals::Cancel) << "' to cancel): ";
        int num;
        std::cin >> num;
        while (convert_num_to_day_and_month_and_run_menu2(num) == (Signals::Bad_Input)) {
            std::cout << "Bad input. Please try again:" << std::endl;
            std::cout << "Choose a day via a number in the range of 1 - 365: ";
            std::cin >> num;
        }
    }
    void Calendar::switch_menu1(int input) {
        if (input == (Keys_menu1::By_Date)) {
            run_input_By_Date();
        } else if (input == (Keys_menu1::By_Day_In_Year)) {
            run_input_By_Day_In_Year();
        } else std::cout << "Bad input. Please try again:" << std::endl;
    }
    int Calendar::is_legal_day_and_month(int day_int, int month_int) {
        if ((day_int == Signals::Cancel) && (month_int == Signals::Cancel)) {/*Cancel input*/
            /*print a message here if you wish*/
            return (Signals::Cancel);
        } else if (day_int > Month::max_month_size || day_int < Month::min_month_size || month_int < month_names::January || month_int > month_names::December) {/*Bad input*/
            return (Signals::Bad_Input);
        } else {/*may be Good input*/
            /*checking: */

            if (month_int == month_names::January) {
                if (Month::is_legal_January(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::February) {
                if (Month::is_legal_February(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::March) {
                if (Month::is_legal_March(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::April) {
                if (Month::is_legal_April(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::May) {
                if (Month::is_legal_May(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::June) {
                if (Month::is_legal_June(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::July) {
                if (Month::is_legal_July(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::August) {
                if (Month::is_legal_August(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::September) {
                if (Month::is_legal_September(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::October) {
                if (Month::is_legal_October(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::November) {
                if (Month::is_legal_November(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            if (month_int == month_names::December) {
                if (Month::is_legal_December(day_int))
                    return (Signals::Good_Input);//input is GOOD!
            }
            return (Signals::Bad_Input);//input is Bad!
        }
    }

    /*---CheckLegalMonths---*/
    void Calendar::is_legal_January_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::January));
        }
    }
    void Calendar::is_legal_February_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::February));
        }
    }
    void Calendar::is_legal_March_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::March));
        }
    }
    void Calendar::is_legal_April_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::April));
        }
    }
    void Calendar::is_legal_May_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::May));
        }
    }
    void Calendar::is_legal_June_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::June));
        }
    }
    void Calendar::is_legal_July_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::July));
        }
    }
    void Calendar::is_legal_August_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::August));
        }
    }
    void Calendar::is_legal_September_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::September));
        }
    }
    void Calendar::is_legal_October_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::October));
        }
    }
    void Calendar::is_legal_November_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::November));
        }
    }
    void Calendar::is_legal_December_and_if_true_run_menu2(int num) {
        if (Month::is_legal_January(num)) {
            run_menu2(num, (month_names::December));
        }
    }

/*+operators+*/
    Month &Calendar::operator[](int i) {
        /*unused but may be usable on other projects*/
        return months[i];
    }
}



