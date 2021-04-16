//
// Created by Tal on 17-Nov-20.
//

#ifndef TARGIL4_LO_LEAGASHA_Q1_LIST_NODE_MEETING_H
#define TARGIL4_LO_LEAGASHA_Q1_LIST_NODE_MEETING_H

#include <iostream>

namespace node {
    class Node {
    private:
        float start_meeting_hour = 0;/*! with the format of: 'HH.MM'  !*/
        float end_meeting_hour = 0;/*! with the format of: 'HH.MM'  !*/
    public:
        Node *next = nullptr;
    public:
        static const int max_hour_size = 24;
        static const int min_hour_size = 0;
    public:
//    Node &operator=(Node *node);
        Node() = default;
        Node(int i);   /*!generic 1 argument constructor!*/
        Node(float start_meeting_hour, float end_meeting_hour);
        Node(Node *node);
//    getters:
        float g_strt() const { return start_meeting_hour; }
        float g_end() const { return end_meeting_hour; }
//    float &g_strt_ref() { return start_meeting_hour; }
//    float &g_end_ref() { return end_meeting_hour; }
        float SORT_VALUE() {//!important: List::MergeSort Depends on this VALUE in order to sort the list.!
        // !The list wil be sorted according to this value.!
            return start_meeting_hour;
        }
        bool operator>(const Node &node) const;
        Node &operator=(Node node);

        /*+FRIEND+*/
        friend std::ostream &operator<<(std::ostream &os, const Node *node);
    };
}
#endif //TARGIL4_LO_LEAGASHA_Q1_LIST_NODE_MEETING_H