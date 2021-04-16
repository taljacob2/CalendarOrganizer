//
// Created by Tal on 17-Nov-20.
//

#include "List.h"

/*!TODO: ALL SORTING IS NOT WELL MADE !*/
namespace lst {
    List::List() {
        /*+ 1 argument +*/
        /*  make a 4 (change as you wish) sized list and initialize as follows:
            head = 0, next = 1, next = 2, next = 3   */
        Node *node;
        int i = 0;
        for (node = head; i < 4; i++, node = node->next) {
            node = new Node(i);
            addNodeToTail(node);
        }
    }
    List::List(const List &List) {//    Copy constructor
//    while getting how many nodes are there to copy, copy the nodes to the new list, deep copying
        Node *node1, *node2;
        for (node1 = head, node2 = List.head; node2; node2 = node2->next) {// TODO: why can I access 'List.head'? its is private!
            node1 = new Node(*node2);/*+using the copy constructor of 'Node' class+*/
            addNodeToTail(node1);/*add lst1_node to the new lst1*/
        }
    }
    List::~List() {
        /*delete list*/
        Node *node;
        for (; head; node = head->next, delete head, head = node);
    }
    void List::addNodeToHead(Node *node) {
        if (!tail)
            tail = node;
        else {
            node->next = head;
        }
        head = node;
    }
    void List::addNodeToTail(Node *node) {
        if (!head)
            head = node;
        else {
            /*tail->next = node; *//*?why this doesn't work?*/
            tail->next = node;
        }
        tail = node;
    }
    void List::addNodeAfter(Node *insert_after_this_node, Node *node) {
        if (!insert_after_this_node) //means, the new node should be marked as the new head
            addNodeToHead(node);
        else {
            Node *tmp = insert_after_this_node->next;
            insert_after_this_node->next = node;
            node->next = tmp;
        }
    }
    void List::removeFromHead() {
        if (head) {
            Node *tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void List::removeFromTail() {
        if (tail) {
            Node *node;
            for (node = head; node->next != tail; node = node->next);
            delete tail;
            node->next = nullptr;
            tail = node;
            if (!(head->next)) {
                head = node;
            }
        }
    }
    void List::removeFromMid(Node *node) {
        /*the list has at least 3 nodes*/
        Node *prev;
        for (prev = head; prev->next != node; prev = prev->next);/*initialize prev to the correct position*/
        prev->next = node->next;
        delete node;
    }
    void List::removeNode(Node *node) {
        if (node == head)
            removeFromHead();
        else if (node == tail)
            removeFromTail();
        else
            removeFromMid(node);
    }
//    void List::sortList() {
//        Node *node, *node2;
//
//        for (node2 = head; node2; node2 = node2->next)/*TODO: bubble sort n^2*/
//            for (node = head; node; node = node->next) {
//                if (node > node->next) { //!  using the operator> here    !
//                    swapNodes(node, node->next);
//                }
//            }
//    }
//    void List::swapNodes(Node *node1, Node *node2) {
//        /*deep copying*/
//        Node *tmp = nullptr;
//        *tmp = *node1;
//        *node1 = *node2;
//        *node2 = *tmp;
//    }
    Node *List::get_node_i(int i) {
        int size = get_size();
        if (i > size || i < 0) {// check for legal input
            throw "ERROR: index inputed is out of range...";
        }
        Node *node_i;
        int j = 0;
        for (node_i = head; node_i && j < i; node_i = node_i->next, j++);
        return node_i;
    }
    int List::get_size() {
        Node *node_i;
        int i;
        for (i = 0, node_i = head; node_i; node_i = node_i->next, i++);
        return i;
    }

    Node *List::RecieveSplittedAndReturnSortedAndMerged(Node *head1, Node *head2) {//TODO: Remember to check the tail
        Node *res;
        //if we encountered the last nodes that are left in one of the lists.
        if (!head1)
            return head2;
        else if (!head2)
            return head1;

        //check values:
        if (head1->SORT_VALUE() < head2->SORT_VALUE()) {
            res = head1;
            res->next = RecieveSplittedAndReturnSortedAndMerged(head1->next, head2);
        } else {
            res = head2;
            res->next = RecieveSplittedAndReturnSortedAndMerged(head1, head2->next);
        }
        return res;
    }

    void List::SplitThenMergeAsSorted(Node **_head) {/*TODO: need to implement*/
        Node *head1, *head2;

        if ((!(*_head)) || (!((*_head)->next)))/*stop condition*/
            return;

        //Splitting List:
        SplitLists(*_head, &head1, &head2);
        //Sort each and then Merge:
        SplitThenMergeAsSorted(&head1);
        SplitThenMergeAsSorted(&head2);

        RecieveSplittedAndReturnSortedAndMerged(head1, head2);
    }

    void List::SplitLists(Node *_head, Node **head1, Node **head2) {
        Node *slow = _head, *fast = _head->next;
        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *head1 = _head;//beginning
        *head2 = slow->next;//mid-point
        slow->next = nullptr;
    }














//int *List::get_data_from_index(int index) {
//    Node *tmp = head;
//    int i = 0;
//    for (tmp = head; tmp; tmp = tmp->next, i++) {
//        if (i == index)
//            return &tmp->data;
//    }
//    throw std::runtime_error("no such index in the list\nexiting...");
//    /*in case we didn't find this index in the list*/
//}

/*+Operators+*/
    Node *List::operator[](int i) {
        return get_node_i(i);
    }

/*+FRIEND+*/
    std::ostream &operator<<(std::ostream &os, const List *lst) {
        /*for std::cout print*/
        Node *node;
        for (node = lst->head; node; node = node->next)
            os << node << " -> ";
        return os;
    }
}