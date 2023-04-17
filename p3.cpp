#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Person::Person()
{
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight)
{
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

void Person::printPerson(ostream &os) 
{
    os << this->first << " " << this->last << ": height=" << this->height << ", weight=" << this->weight;
}

ostream &operator<<(ostream &os, Person &ptr) {
    ptr.printPerson(os);
    return os;
}

PersonList::PersonList()
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize()
{
    return size;
}

void PersonList::printByHeight(ostream &os)
{
    Person *cur = headHeightList;
    while (cur != nullptr) {
        os << *cur << endl;
        cur = cur->nextHeight;
    }
}

void PersonList::printByWeight(ostream &os)
{
    Person *cur = headWeightList;
    while (cur != nullptr) {
        os << *cur << endl;
        cur = cur->nextWeight;
    }
}

bool PersonList::exists(string first, string last)
{
    if (headHeightList == nullptr && headWeightList == nullptr) {
        return false;
    }
    bool doesExist = false;
    Person *cur = headHeightList;
    while (cur != nullptr) {
        if (cur->first == first && cur->last == last) {
            return doesExist = true;
        }
        cur = cur->nextHeight;
    }
    return doesExist;
}

bool PersonList::insertWeightHere(Person *insertion, Person*current) {
    if (insertion->weight < current ->weight) {
        return true;
    }
    else if (insertion->weight == current->weight) {
        if (insertion->height > current->height) {
            return true;
        }
        else if (insertion->height < current->height) {
            return false;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool PersonList::insertHeightHere(Person *insertion, Person*current) {
    if (insertion->height > current->height) {
        return true;
    }
    else if (insertion->height == current->height) {
        if (insertion->weight < current->weight) {
            return true;
        }
        else if (insertion->weight > current->weight) {
            return false;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

int PersonList::getHeight(string first, string last) {
    int foundHeight = -1;
    Person *cur = headHeightList;
    while (cur != nullptr) {
        if (cur->first == first && cur->last == last) {
            foundHeight = cur->height;
            break;
        }
        cur = cur->nextHeight;
    }
    return foundHeight;
}

int PersonList::getWeight(string first, string last) {
    int foundWeight = -1;
    Person *cur = headWeightList;
    while (cur != nullptr) {
        if (cur->first == first && cur->last == last) {
            foundWeight = cur->weight;
            break;
        }
        cur = cur->nextWeight;
    }
    return foundWeight;
}

bool PersonList::add(string first, string last, int height, int weight) 
{
    //cout << "adding " << first << " " << last << " with height " << height << " and weight " << weight << endl;
    //cout << "printing in add ******" << endl;
    //this->printByHeight(cout);
    //cout << "printing in add ******" << endl;
    
    bool wBool = false;
    bool hBool = false;

    if (this->exists(first, last))
    {
        //cout << first << " already exists numb nuts" << endl;
        return false;
    }

    size++;

    Person *p = new Person(first, last, height, weight);

    if (headWeightList == nullptr && headHeightList == nullptr) {           //both lists are empty
        //std::cout << "the list is empty, inserting " << first <<  " now" << endl;
        headWeightList = p;
        headHeightList = p;
        wBool = true;
        hBool = true;
        //cout << boolalpha << "wBool is " << wBool << " and hBool is " << hBool << "for " << first <<  endl;
        return true;
    }
    
    if (insertWeightHere(p, headWeightList)) {
        p->nextWeight = headWeightList;
        headWeightList = p;
        wBool = true;
    }
    if (insertHeightHere(p, headHeightList)) {
        p->nextHeight = headHeightList;
        headHeightList = p;
        hBool = true;
    }

    //cout << "printing before wbool ******" << endl;
    //this->printByWeight(cout);
    //cout << "printing before wbool ******" << endl;
    

    if (!wBool) {
        Person *prev = headWeightList;
        Person *cur = headWeightList->nextWeight;
        //std::cout << first << " is about to enter the while loop for weight" << endl;
        while (cur != nullptr) {
            if(insertWeightHere(p,cur)) {
                break;
            }
            prev = prev->nextWeight;
            cur = cur->nextWeight;
        }
        prev->nextWeight = p;
        p->nextWeight = cur;
        wBool = true;
        
    }

    //cout << "printing before hbool ******" << endl;
    //this->printByHeight(cout);
    //cout << "printing before hbool ******" << endl;
    if (!hBool) {
        Person *prev = headHeightList;
        Person *cur = headHeightList->nextHeight;
        //std::cout << first << " is about to enter the while loop for height" << endl;
        while (cur != nullptr) {
            if(insertHeightHere(p,cur)) {
                break;
            }
            //cout << "prev is " << prev->first << " and cur is " << cur->first << endl;
            prev = prev->nextHeight;
            cur = cur->nextHeight;
        }
        prev->nextHeight = p;
        p->nextHeight = cur;
        hBool = true;

        //if (p->nextHeight != nullptr){
        //    cout << "the inserted node is " << p->first << " and the next is " << p->nextHeight->first << endl;
        //}

        
    }
    //cout << boolalpha << "wBool is " << wBool << " and hBool is " << hBool << "for " << first <<  endl;
	return wBool && hBool;
}

bool PersonList::remove(string first, string last)
{
    bool foundW = false;
    bool foundH = false;
    //cout << "in remove" << endl;

    if (!(this->exists(first, last))) {
        //cout << first << " doesn't exist" << endl;
        return foundW && foundH;
    }
    if (headWeightList->first == first && headWeightList->last == last) {
        Person *next = headWeightList->nextWeight;
        headWeightList = next;
        foundW = true;
    }
    else {
        Person *prev = headWeightList;
        Person *cur = headWeightList->nextWeight;
        while (cur->first != first && cur->last != last) {
            prev = cur;
            cur = cur->nextWeight;
        }
        prev->nextWeight = cur->nextWeight;
        foundW = true;
    }
    if (headHeightList->first == first && headHeightList->last == last) {
        Person *next = headHeightList->nextHeight;
        headHeightList = next;
        foundH = true;
    }
    else {
        Person *prev = headHeightList;
        Person *cur = headHeightList->nextHeight;
        while (cur->first != first && cur->last != last) {
            prev = cur;
            cur = cur->nextHeight;
        }
        prev->nextHeight = cur->nextHeight;
        foundH = true;
    }
    //cout << "printing in remove ******" << endl;
    //this->printByHeight(cout);
    //cout << "printing in remove ******" << endl;
    
    size--;
    return foundW && foundH;
}

bool PersonList::updateName(string first, string last, string newFirst, string newLast)
{
    bool found = false;
    Person *cur = headHeightList;
    while (cur != nullptr) {
        if (cur->first == first && cur->last == last) {
            cur->first = newFirst;
            cur->last = newLast;
            found = true;
            break;
        }
        cur = cur->nextHeight;
    }
    cur = headWeightList;
    while (cur != nullptr) {
        if (cur->first == first && cur->last == last) {
            cur->first = newFirst;
            cur->last = newLast;
            found = true;
            break;
        }
        cur = cur->nextWeight;
    }
    return found;
    /*bool returnVal = false;
    int w = this->getWeight(first, last);
    int h = this->getHeight(first, last);

    returnVal = (this->remove(first, last) && this->add(newFirst, newLast, h, w));

    //cout << "name updated for " << newFirst << endl;

    return returnVal;*/
}

bool PersonList::updateHeight(string first, string last, int height)
{
    bool returnVal = false;
    int tempW = this->getWeight(first, last);

    //cout << "about to update " << first << "'s height from " << this->getHeight(first, last) << " to " << height << endl;

    returnVal = (this->remove(first, last) && this->add(first, last, height, tempW));

    //cout << "height updated for " << first << endl;

    return returnVal;
}

bool PersonList::updateWeight(string first, string last, int weight)
{
    bool returnVal = false;
    int tempH = this->getHeight(first, last);

    returnVal = (this->remove(first, last) && this->add(first, last, tempH, weight));
    //cout << "weight updated for " << first << endl;

    return returnVal;
}

PersonList::~PersonList()
{
    Person *cur = headWeightList->nextWeight;
    Person *prev = headWeightList;
    while (cur != nullptr) {
        delete prev;
        prev = cur;
        cur = cur->nextWeight;
    }

    cur = headHeightList->nextHeight;
    prev = headHeightList;
    while (cur != nullptr) {
        delete prev;
        prev = cur;
        cur = cur->nextHeight;
    }
    delete cur;
}

PersonList::PersonList(const PersonList &src)
{
    headWeightList = nullptr;
    headHeightList = nullptr;
    Person *cur = src.headWeightList;
    while (cur != nullptr) {
        this->add(cur->first, cur->last, cur->height, cur->weight);
        cur = cur->nextWeight;
    }
}

const PersonList &PersonList::operator=(const PersonList &src)
{
    if (this != &src) {
        if (headWeightList != nullptr && headHeightList != nullptr) {
            headWeightList = nullptr;
            headHeightList = nullptr;
        }
        Person *cur = src.headWeightList;
        while (cur != nullptr) {
            this->add(cur->first, cur->last, cur->height, cur->weight);
            cur = cur->nextWeight;
        }
    }
    return *this;
}
