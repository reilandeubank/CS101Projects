#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <vector>

using namespace std;
string key;
int tableSize;

class Person {
    public:
    string id, first, last, email, phone, city, state, postalCode, personKey;
    Person *next;
    Person() {                  //default constructor
        id = first = last = email = phone = city = state = postalCode = personKey = "";
    }
    Person(string id, string first, string last, string email, string phone, string city, string state, string postalCode) {
        this->id = id;
        this->first = first;
        this->last = last;
        this->email = email;
        this->phone = phone;
        this->city = city;
        this->state = state;
        this->postalCode = postalCode;
        if (key == "Id") {
            personKey = id;
        }
        else if (key == "FirstName") {
            personKey = first;
        }
        else if (key == "LastName") {
            personKey = last;
        }
        else if (key == "Email") {
            personKey = email;
        }
        else if (key == "Phone") {
            personKey = phone;
        }
        else if (key == "City") {
            personKey = city;
        }
        else if (key == "State") {
            personKey = state;
        }
        else if (key == "PostalCode") {
            personKey = postalCode;
        }
    }
    void printPerson(ostream &os) {
        os << id << "," << first << "," << last << "," << email << "," << phone << "," << city << ",";
        os << state << "," << postalCode << endl;
    }
    
};

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class HashTable {
    public:
    vector< vector<Person*> > v;
    HashTable() {
        v.resize(tableSize);
        //***** NOT COMPLETE IN ANY CAPACITY ******
    }

    void add(string id, string first, string last, string email, string phone, string city, string state, string postalCode) {
        Person *p = new Person(id, first, last, email, phone, city, state, postalCode);
        int hashVal = djb2(p->personKey) % tableSize;
        //cout << "adding person named  " << first << " and hashVal " << hashVal << endl;
        bool added = false;
        int j = 0;
        Person *cur;

        for (int i = 0; i < tableSize; ++i) {
            if (i >= (int)v.size()) {
                break;
            }
            else{
                v.at(i).resize(3000);
            }
        }

        for (int i = 0; i < tableSize; ++i) {
            if (i >= (int)v.size()) {
                break;
            }
            else{
                int size = v.at(i).size();
                if (v.at(i).at(size/2) != nullptr) {
                    v.at(i).resize(size*2);
                }
            }
        }

        while (!added) {
            if (first == "") {
                added = true;
                break;
            }
            cur = v.at((int)(hashVal + pow(j, 2))%tableSize).at(0);
            if (cur == nullptr) {
                v.at((int)(hashVal + pow(j, 2))%tableSize).at(0) = p;
                added = true;
                //cout << "person vector was empty, adding " << p->first << " to front of  " << p->personKey << endl;
                break;
            }
            else if (cur->personKey == p->personKey) {
                bool go = true;
                int z = 0;
                while (go) {
                    if (v.at((int)(hashVal + pow(j, 2))%tableSize).at(z) == nullptr) {
                        go = false;
                        break;
                    }
                    else {
                        z++;
                    }
                }
                v.at((int)(hashVal + pow(j, 2))%tableSize).at(z) = p;
                added = true;
                //cout << "person vector was populated, adding " << p->first << " to back of  " << p->personKey << endl;
                break;
            }
            else {
                //cout << "not found initially, iterating" << endl;
                ++j;
            }
        }
    }

    void print(ostream &os) {
        for (int i = 0; i < tableSize; i++) {
            //cout << "looking in index " << i << " of overall vector" << endl;
            if (i < v.size()) {
                if (v.at(i).at(0) != nullptr) {
                    bool go = true;
                    int z = 0;
                    while (go) {
                        if (v.at(i).at(z) == nullptr) {
                            go = false;
                            break;
                        }
                        else {
                            z++;
                        }
                    }
                    os << i << ": " << v.at(i).at(0)->personKey << " (" << z << ")," << endl;
                }
            }
        }
    }

    void lookup(ostream &os, string lookupKey) {
        int hashVal = djb2(lookupKey) % tableSize;
        //cout << "adding person named  " << first << " and hashVal " << hashVal << endl;
        bool found = false;
        int j = 0;
        Person *cur;

        while (!found) {
            cur = v.at((int)(hashVal + pow(j, 2))%tableSize).at(0);
            if (cur == nullptr) {
                os << "No results" << endl;
                found = true;
                break;
            }
            else if (cur->personKey == lookupKey) {
                bool go = true;
                int z = 0;
                while (go) {
                    if (v.at((int)(hashVal + pow(j, 2))%tableSize).at(z) == nullptr) {
                        go = false;
                        break;
                    }
                    else {
                        z++;
                    }
                }
                //cout << "lookup match found for " << lookupKey << endl;
                os << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                for (int i = 0; i < z; i++) {
                    v.at((int)(hashVal + pow(j, 2))%tableSize).at(i)->printPerson(cout);
                }
                found = true;
                break;
            }
            else {
                //cout << "lookup match not found for " << lookupKey << ", iterating" << endl;
                ++j;
            }
        }
    }

};

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    tableSize = stoi(argv[2]);
    key = argv[3];
    HashTable *h = new HashTable();

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    string personArr[8];
    string tokenArr[8];
    int numArr[8];
   
    string line, token;

    for (int i = 0; i < 8; ++i) {
        file >> tokenArr[i];
    }

    for (int i = 0; i < 8; ++i) {
        if (tokenArr[i] == "Id") {
            numArr[i] = 0;
        }
        else if (tokenArr[i] == "FirstName") {
            numArr[i] = 1;
        }
        else if (tokenArr[i] == "LastName") {
            numArr[i] = 2;
        }
        else if (tokenArr[i] == "Email") {
            numArr[i] = 3;
        }
        else if (tokenArr[i] == "Phone") {
            numArr[i] = 4;
        }
        else if (tokenArr[i] == "City") {
            numArr[i] = 5;
        }
        else if (tokenArr[i] == "State") {
            numArr[i] = 6;
        }
        else if (tokenArr[i] == "PostalCode") {
            numArr[i] = 7;
        }
    }

    int x;
    while (getline(file, line)) {
        istringstream iss(line);
        x = 0;
        while (getline(iss, token, '\t')) {
            personArr[numArr[x]] = token;
            x++;
        }
        //cout << "adding person with name " << personArr[1] << endl;
        h->add(personArr[0], personArr[1], personArr[2], personArr[3], personArr[4], personArr[5], personArr[6], personArr[7]);
    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            h->print(cout);
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            h->lookup(cout, val);
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
