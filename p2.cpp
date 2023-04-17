#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cmath>
using namespace std;

ifstream inFS;
ifstream sortFS;
ofstream outFS;
string dataType;
string strData;
int intData;
int sortNum;

class Item {
public:
    string strItem;
    int intItem;
    Item *next;

    Item() {
        strItem = "";
        intItem = -1;
    }
    void setStr(string newStr) {
        strItem = newStr;
    }
    void setInt(int newInt) {
        intItem = newInt;
    }
    void print(ostream &os) {
        if (strItem != "") {
            os << strItem;
        }
        else if (intItem != -1) {
            os << intItem;
        }
    }
};

ostream &operator<<(ostream &os, Item &ptr) {
    ptr.print(os);
    return os;
}

class ItemList {
    private:
        
    public:
    Item *head;
        ItemList() {
            head = nullptr;
        }
        void printList(ostream &os) {
            Item *cur = head;
            //os << setw(10) << right;
            while (cur != nullptr) {
                os << setw(10) << right << *cur << endl;
                cur = cur->next;
            }
        }
        void Merge(ItemList &list, Item *beg, Item *head2) {
            ItemList tempList;
            Item *sortPlace;
            Item *cur1 = beg;
            Item *cur2 = head2;
            if ((cur1 <= cur2) && (cur1 != nullptr)) {
                tempList.head = cur1;  // if i ever decide to come back to this, use appendInt and appendStr
                cur1 = cur1->next;
            }
            else if ((cur1 > cur2) && (cur1 != nullptr)) {
                tempList.head = cur2;
                cur2 = cur2->next;
            }
            sortPlace = tempList.head;
            while (!(cur1 == nullptr && cur2 == nullptr)) {
                if ((cur1 <= cur2) && (cur1 != nullptr)) {
                    sortPlace->next = cur1;
                    cur1 = cur1->next;
                    sortPlace = sortPlace->next;
                }
                else if ((cur1 > cur2) && (cur1 != nullptr)) {
                    sortPlace->next = cur2;
                    cur2 = cur2->next;
                    sortPlace = sortPlace->next;
                }
                else if (cur1 != nullptr && cur2 == nullptr) {
                    sortPlace->next = cur1;
                    cur1 = cur1->next;
                    sortPlace = sortPlace->next;
                }
                else if (cur1 == nullptr && cur2 != nullptr) {
                    sortPlace->next = cur2;
                    cur2 = cur2->next;
                    sortPlace = sortPlace->next;
                }
            }
            outFS << "printing temp" << endl;
            tempList.printList(outFS);
            outFS << "done printing temp" << endl;
        }
        void Sort(ItemList &list) {
            if(head == nullptr||head->next == nullptr) {
                return;
            }
            Item *mid = head;
            Item *tail = head->next;
            while(mid->next != NULL && (tail!=NULL && tail->next!=NULL)) {            //finding middle value
                mid = mid->next;
                tail = tail->next->next;
            }

            Item *head2 = mid->next;
            mid->next = nullptr;

            //cout << list.head->intItem << endl << list.head->next->intItem << endl;

            Item *h1;
            Item *h2;

            MergeSort(list, head, mid);
            //cout << list.head->intItem << endl << list.head->next->intItem << endl;
            //cout << head2->intItem << endl << head2->next->intItem << endl;
            MergeSort(list, head2, tail);
            Merge(list, h1, h2);
        }
        void MergeSort(ItemList &list, Item *beg, Item *end) {
            if(list.head == nullptr||list.head->next == nullptr) {
                //cout << "list is length 0 or 1" << endl;
                return;
            }

            Item *mid = list.head;
            Item *tail = head->next;
            while(mid->next != nullptr && (tail != nullptr && tail->next != nullptr)) {            //finding middle value
                mid = mid->next;
                tail = tail->next->next;
            }

            Item *head2 = mid->next;
            mid->next = nullptr;

            //MergeSort(list, beg, mid);
            //MergeSort(list, head2, tail);
            //Merge(list, beg, head2);
        }
        void appendInt(int num) {
            Item *n = new Item;
            n->setInt(num);
            if (head == nullptr) {
                head = n;
                return;
            }
            else {
                Item *cur = head;
                while (cur->next != nullptr) {
                    cur = cur->next;
                }
                cur->next = n;
            }
            }
        void appendStr(string str) {
            Item *n = new Item;
            n->setStr(str);
            if (head == nullptr) {
                head = n;
                return;
            }
            else {
                Item *cur = head;
                while (cur->next != nullptr) {
                    cur = cur->next;
                }
                cur->next = n;
            }
    }
};

ostream &operator<<(ostream &os, ItemList &list) {
    list.printList(os);
    return os;
};

bool compareLessInt(int a, int b) {
    if ((sortFS >> sortNum)) {
        int digA = (int(a / pow(10, sortNum)) % 10);
        int digB = (int(b / pow(10, sortNum)) % 10);
        if (digA < digB) {
            return true;
        }
        else {
            return compareLessInt(a, b);
        }
    }
    else {
        return false;
    }
    
}

bool compareLessStr(string a, string b) {
    if ((sortFS >> sortNum)) {
        char chA = '\0';
        char chB = '\0';
        if (sortNum < int(a.length())) {
            chA = a.at(sortNum);
        }
        if (sortNum < int(b.length())) {
            chB = b.at(sortNum);
        }
        if (chA < chB) {
            return true;
        }
        else {
            return compareLessStr(a, b);
        }
    }
    else {
        return false;
    }
}

bool operator==(const Item &lhs, const Item &rhs) {
    bool isEqual = true;
    if (dataType == "i") {
        while (sortFS >> sortNum) {
            int digLHS = (int(lhs.intItem / pow(10, sortNum)) % 10);
            int digRHS = (int(rhs.intItem / pow(10, sortNum)) % 10);
            if (digLHS != digRHS) { 
                isEqual = false ;
            }
        }
    }
    else if (dataType == "s") {
        while (sortFS >> sortNum) {
            char chLHS = '\0';
            char chRHS = '\0';
            if (sortNum < int(lhs.strItem.length())) {
                chLHS = lhs.strItem.at(sortNum);
            }
            if (sortNum < int(rhs.strItem.length())) {
                chRHS = rhs.strItem.at(sortNum);
            }
            if (chLHS != chRHS) { 
                isEqual = false ;
            }
        }
    }
    return isEqual;
}

bool operator<(const Item &lhs, const Item &rhs) {
    bool isLess = true;
    if (dataType == "i") {
        isLess = compareLessInt(lhs.intItem, rhs.intItem);
    }
    else if (dataType == "s") {
        isLess = compareLessStr(lhs.strItem, rhs.strItem);
    }
    return isLess;

}
        
bool operator<=(const Item &lhs, const Item &rhs) {
    return ((lhs.intItem < rhs.intItem) || (lhs.intItem == rhs.intItem));
}

bool operator>(const Item &lhs, const Item &rhs) {
    return rhs.intItem < lhs.intItem;
}

int main(int argc, char** argv) {
    dataType = argv[1];
    sortFS.open(argv[2]);
    inFS.open(argv[3]);
    outFS.open(argv[4]);
    ItemList list1;
    
    
    if (argc != 5) {
        cout << "Usage: ./a.out i|s sort_filename input_filename output_filename" << endl;
        return 1;
    }

    if (dataType != "i" && dataType != "s") {
        cout << "Invalid datatype \"" << dataType << "\" (must be \"i\" or \"s\")" << endl;
        return 1;
    }

    if (!outFS.is_open()) {
        cout << "Unable to open output file" << endl;
        return 1;
    }

    if (!inFS.is_open()) {
        cout << "Unable to open input file" << endl;
        return 1;
    }
    if (!sortFS.is_open()) {
        cout << "Unable to open sort file" << endl;
        return 1;
    }
    
    if (dataType == "i") {
        while(inFS >> intData) {
            list1.appendInt(intData);
        }
    }
    else if (dataType == "s") {
        while(inFS >> strData) {
            list1.appendStr(strData);
        }
    }

    list1.Sort(list1);
    list1.printList(outFS);
    
    sortFS.close();
    inFS.close();
    outFS.close();
    return 0;
}
