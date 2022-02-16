#include <iostream>
#include <sstream>

using namespace std;

// Templetized Linked List Class
template <typename T>

class LinkedList : public LinkedListInterface <T> {
private:
    struct Node {
        T data;
        Node *nextNode;
        Node () {}
        Node (const T& data) : data(data), nextNode(NULL) {} 
        Node (const T& data, Node *n) : data(data), nextNode(n) {} 
    };

    Node *head;

public:
// Nested Iterator Class
    class Iterator {
        private:
            Node* iNode;
            friend class LinkedList;
        public:
            Iterator() : iNode() {}
            Iterator(Node* head) : iNode(head) { }
            ~Iterator() {}

            bool operator!=(const Iterator& rhs) const {
                return (iNode != rhs.iNode);
            }

            Iterator& operator++() {
                iNode = iNode->nextNode;
                return *this;
            }

            T& operator*() const {
                return iNode->data;
            }
    };

    LinkedList() {
        head = NULL;
    }

    LinkedList(const LinkedList &oldList) {
        head = NULL;
        Node *t = NULL;
        Node *curr = NULL;

        if (oldList.head != NULL) {
            t = oldList.head;
            head = new Node(t->data);
            curr = head;
 
            while (t->nextNode != NULL) {
                t = t->nextNode;
                curr->nextNode = new Node(t->data, t->nextNode);
                curr = curr->nextNode;
            }
        }

    }

    LinkedList& operator= (const LinkedList &oldList) {
        LinkedList<T> temp(oldList);
        std::swap(temp.head, head);
        return *this;
    }

    ~LinkedList() {
        if (!empty()) {
            clear();
        }
    }

	void push_front(const T& value) {
        if (head == NULL) {
            head = new Node(value);
            return;
        } 

        head = new Node(value, head);
    }

	void pop_front(void) {
        Node *t = head;
        head = head->nextNode;
        delete t;
        t = NULL;
    }

	T& front(void) { 
        return head->data;
    }

	bool empty(void) const {
        if (head == NULL) {
            return true;
        }

        return false;
    }
 
	void remove(const T& value) {
        Node *t = head;
        Node *first = head;
        Node *curr = head;


        if (head == NULL) {
            return;
        }

        // Check to see if value is the 1st node
        while (head != NULL && head->data == value) { 
            head = head->nextNode;
            delete first;
            first = head;
        }

        if (head == NULL) {
            return;
        }

        // Check to see if value is any node in the middle
        // Check to see if value occurs more than once
        for (t = head; t != NULL && t->nextNode != NULL; ) {
            if (t->nextNode->data == value) {
                curr = t->nextNode;

        // Check to see if value is the last node
                if (t->nextNode->nextNode != NULL) { 
                    t->nextNode = t->nextNode->nextNode;
                } else {
                    t->nextNode = t->nextNode->nextNode;
                    delete curr;
                    curr = NULL;
                    continue;
                } 

                delete curr;
                curr = NULL;

            } else {
                t = t->nextNode;
            }
        }
    }

	void clear(void) { 

        if (head == NULL) {
            return;
        }        

        Node *t = NULL;

        while (head->nextNode != NULL) {
            t = head;
            head = head->nextNode;
            t->nextNode = NULL;
            delete t;
        }

        delete head;
        head = NULL;
    }

	void reverse(void) {
        Node *prev = NULL;
        Node *curr = head;
        Node *next = head;

        while (curr != NULL) {
            next = next->nextNode;
            curr->nextNode = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }

	size_t size(void) const { 
        Node *t = head;
        size_t listSize = 0;

        while (t->nextNode != NULL) {
            listSize++;
            t = t->nextNode;
        }

        listSize++;

        return listSize;
    }

    string toString() const { 
        
        if (head == NULL) {
            return " ";
        }
        
        Node *t = head;
        stringstream out;
        size_t listSize;


        out << t->data << " ";


        // Only executes if it's not at the end of the list
        while (t->nextNode != NULL) {
            t = t->nextNode;
            out << t->data << " ";
        } 

        return out.str();
    }

    friend std::ostream& operator<< (std::ostream& os, const LinkedList &ll) {
        os << ll.toString();
        return os;
    }

	Iterator begin(void) {
		return LinkedList<T>::Iterator(head);
	}

	Iterator end(void) {
		return LinkedList<T>::Iterator(NULL);
	}

	Iterator find(Iterator first, Iterator last, const T& value) {
        for (Iterator iter = first; iter != last; ++iter) {
            if (*iter == value) {
                return iter;
            }
        }

        return last;
	}

	Iterator insert(Iterator position, const T& value) {
        Node *n = new Node(value, position.iNode);
        
        Node *temp = NULL;
        for (temp = head; temp != NULL && temp->nextNode != NULL; ) {
            if (head == position.iNode) {
                head = n;
                position.iNode = n;
                return position;
            }

            if (temp->nextNode == position.iNode) {
                temp->nextNode = n;
                position.iNode = n;
                return position;
            }
            temp = temp->nextNode;
        }

        return position;
    }

	Iterator insert_after(Iterator position, const T& value) {
        Node *t = new Node(value, position.iNode->nextNode);

        position.iNode->nextNode = t;

        return (++position);
	}

	Iterator erase(Iterator position) {
        // remove(position.iNode->data);
        Node *t = head;
        Node *first = head;
        Node *curr = head;

        if (head == NULL) {return position;}

        // Check to see if value is the 1st node
        while (head != NULL && head->data == position.iNode->data) { 
            head = head->nextNode;
            delete first;
            first = head;

            position.iNode = head;
            return position;     
        }

        if (head == NULL) {return position;}

        // Check to see if value is any node in the middle
        for (t = head; t != NULL && t->nextNode != NULL; ) {
            if (t->nextNode->data == position.iNode->data) {
                curr = t->nextNode;
                 
                if (t->nextNode->nextNode != NULL) { 
                    t->nextNode = t->nextNode->nextNode;
                } else {
                    t->nextNode = t->nextNode->nextNode;
                    delete curr;
                    curr = NULL;
                    
                    position.iNode = t;
                    return position;
                } 


                delete curr;
                curr = NULL;

                position.iNode = t;
                return position;
            
            } else {
                t = t->nextNode;
            }
        } 

        return position;
	}

	void replace(Iterator first, Iterator last, const T& old_value, const T& new_value) {
		Node* t = NULL;

        for (t = head; t != NULL; ) { 
            if (t->data == old_value) {
                t->data = new_value;
            }
            t = t->nextNode;
        }

	} 

};