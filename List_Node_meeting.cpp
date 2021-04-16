//
// Created by Tal on 17-Nov-20.
//

#include "List_Node_meeting.h"

namespace node {
    Node::Node(float start_meeting_hour, float end_meeting_hour) {
        this->start_meeting_hour = start_meeting_hour;
        this->end_meeting_hour = end_meeting_hour;
    }
    Node::Node(int i) {   /*!generic 1 argument constructor!*/
        /* by default, creates Node with 1 hour long meeting, and minutes are rounded to 0 */
        this->start_meeting_hour = static_cast<float>(i % max_hour_size);
        this->end_meeting_hour = static_cast<float>((i + 1) % max_hour_size);
    }
    Node::Node(Node *node) : start_meeting_hour(node->start_meeting_hour), end_meeting_hour(node->end_meeting_hour) {//copy constructor of Nodes
        this->next = node->next;
    }

//void Node::copy_fields(Node *node){// same as operator=
//    this->start_meeting_hour = node->start_meeting_hour;
//    this->end_meeting_hour = node->end_meeting_hour;
//}

/*+operators+*/
    Node &Node::operator=(const Node node) {
        start_meeting_hour = node.start_meeting_hour;
        end_meeting_hour = node.end_meeting_hour;
        return *this;
    }

    bool Node::operator>(const Node &node) const {
        return start_meeting_hour > node.g_strt();
    }
/*+FRIEND+*/
    std::ostream &operator<<(std::ostream &os, const Node *node) {
        /*for std::cout print*/
        os << "(" << node->start_meeting_hour << " - " << node->end_meeting_hour << ")";
        return os;
    }
}

