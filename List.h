//
// Created by Tal on 17-Nov-20.
//

#ifndef TARGIL4_LO_LEAGASHA_Q1_LIST_H
#define TARGIL4_LO_LEAGASHA_Q1_LIST_H

#include <iostream>
#include "List_Node_meeting.h"

using namespace node;
/*!TODO: ALL SORTING IS NOT WELL MADE !*/
namespace lst {
/*!     REMEMBER:   YOU MUST INCLUDE A NODE AS YOU WISH     !*/
    class List {/*+List is a linked list of Nodes+*/
    private:
        Node *head = nullptr;
        Node *tail = nullptr;

        /*--------methods--------*/
    private:
        void removeFromHead();
        void removeFromTail();
        void removeFromMid(Node *node);
//        void swapNodes(Node *node1, Node *node2);
        void SplitLists(Node *head, Node **head1, Node **head2);
        Node *RecieveSplittedAndReturnSortedAndMerged(Node *head1, Node *head2);
        void SplitThenMergeAsSorted(Node **_head);
    public:
        void addNodeToHead(Node *node);
        void addNodeToTail(Node *node);
        void addNodeAfter(Node *insert_after_this_node, Node *node);

//    int *get_data_from_index(int index);
        List();
        ~List();
        List(const List &lst); // copy constructor
        Node *get_head() { return head; }
        Node *get_tail() { return tail; }
//        void sortList();
//        void mergeSort() { SplitThenMergeAsSorted(&head); }

//    void set_value_for_index_alive();
        int get_size();
        Node *get_node_i(int i);
        bool is_list() { return head != nullptr; }
        void removeNode(Node *node);
        /*+Operators+*/
        Node *operator[](int i);
        /*+ FRIEND +*/
        friend std::ostream &operator<<(std::ostream &os, const List *lst);
    };
}
#endif //TARGIL4_LO_LEAGASHA_Q1_LIST_H
