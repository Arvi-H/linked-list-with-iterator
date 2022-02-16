#include "LinkedListInterface.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void validList(const LinkedList<string> &myList, string item1) {
    if (myList.empty()) {
        throw item1;
    }
}

int main(int argc, char* argv[]) {

    // File I/O
    ifstream in(argv[1]);
    ofstream out(argv[2]); 

    // Linked List Object
    LinkedList<string> myList;
    LinkedList<string> myListCopy;

    // Iterator Object
    LinkedList<string>::Iterator iter = myList.begin();
    LinkedList<string>::Iterator pos;

    // Process input strings
    for (string line; getline(in, line);) {
        string item1, item2, item3;
        if (line.size() == 0) continue;

        istringstream s(line);
        s >> item1;

        try {
            out << item1;

            if (item1 == "Insert") {
                while (s >> item2) {
                    out << " " << item2;
                    myList.push_front(item2);
                }
                out << endl;

            } else if (item1 == "PrintList") {
                validList(myList, item1);

                out << " " << myList.toString() << endl;

            } else if (item1 == "Clear") {
                validList(myList, item1);
                
                out << " OK" << endl;
                myList.clear();

            } else if (item1 == "Empty") {
                if (!myList.empty()) {
                    out << " false" << endl;
                } else {
                    out << " true" << endl;
                }
                
            } else if (item1 == "Size") {
                if (myList.empty()) {
                    out << " 0 " << endl;
                } else {
                    out <<  " " << myList.size() << endl;
                }

            } else if (item1 == "Delete") {
                validList(myList, item1);
                
                out << " OK" << endl;
                myList.pop_front();
            
            } else if (item1 == "First") {
                validList(myList, item1);

                out << " " << (myList.front()).c_str() << endl;

            } else if (item1 == "Remove") {
                while (s >> item2) {
                    myList.remove(item2);
                    out << " " << item2 << endl;
                }

            } else if (item1 == "Reverse") {
                validList(myList, item1);
                myList.reverse();
                out << " OK" << endl;
                
            } else if (item1 == "Copy") {
                out << " OK" << endl;
                myListCopy = myList;

            } else if (item1 == "PrintCopy") {
                validList(myListCopy, item1);
                out << " " << myListCopy << endl;

            } else if (item1 == "Iterate") {
                validList(myList, item1);

                out << endl;
                for (iter = myList.begin(); iter != myList.end(); ++iter) {
                    out << " [" <<*iter << "] " << endl;
                }

            } else if (item1 == "Find") {
                if (s >> item2) {
                    pos = myList.find(myList.begin(), myList.end(), item2);
                }

                if (pos != myList.end()) {
                    out << " " << item2 << " OK" << endl;
                } else {
                    out << " " << item2 << " Not Found" << endl;
                }
                
            } else if (item1 == "InsertAfter") {
                if (s >> item2) {
                    if (s >> item3) {
                        pos = myList.find(myList.begin(), myList.end(), item3);
                    
                        if (pos != myList.end()) {
                            myList.insert_after(pos, item2);
                            out << " " << item2 << " " << item3 << " OK" << endl;
                        } else {
                            out << " " << item2 << " " << item3 << " Not Found" << endl;
                        }
                    }
                }

            } else if (item1 == "InsertBefore") {
                if (s >> item2) {
                    if (s >> item3) {
                        pos = myList.find(myList.begin(), myList.end(), item3);
                    
                        if (pos != myList.end()) {
                            myList.insert(pos, item2);
                            out << " " << item2 << " " << item3 << " OK" << endl;
                        } else {
                            out << " " << item2 << " " << item3 << " Not Found" << endl;
                        }
                    }
                }
               
            } else if (item1 == "Erase") {
                if (s >> item2) {
                    pos = myList.find(myList.begin(), myList.end(), item2);
                    if (pos != myList.end()) {
                        myList.erase(pos);
                        out << " " << item2 << " OK" << endl;
                    } else {
                        out << " " << item2 << " Not Found" << endl;
                    }
                }
            } else if (item1 == "Replace") {
                if (s >> item2) {
                    if (s >> item3) {
                        myList.replace(myList.begin(), myList.end(), item2, item3);
                        out << " " << item2 << " " << item3 << " OK" << endl; 
                    }
                }
               
            } else {
                out << endl;
            } 
        } catch (string item1) {
            out << " Empty!" << endl;
        }

    }
}
