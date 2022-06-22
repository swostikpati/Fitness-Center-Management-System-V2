// Name: Swostik Pati
// Fitness Management System - Version 2.0
// Date: 13/03/21

// Importing dependencies
#include <iostream>
#include <string>
#include <ctime> //to get system time - to randomize srand() seed
#include <fstream>
#include <exception>
using namespace std;

// The following exception class was implemented initially - it worked perfectly on windows(g++ compiler), but crashed on mac
// So I decided to replace it with exit(1) at the required places.
//  class StackEmpty : public exception
//  {
//  public:
//      virtual const char *what() const throw()
//      {
//          return "Stack is Empty";
//      }
//  };

bool aL, mL; // stores whether admin is logged in or member

// The following lines of code help in friending template classes - reference - stackoverflow (as I encountered an error)
template <class T>
class Node;
template <class T>
class MyLinkedList;
template <class T>
class LinkedStack;

// Template Class Node
template <typename T>
class Node
{
private:
    T elem;        // data element
    Node<T> *next; // Link (pointer) to the next Node

public:
    // Friend classes and functions - important to friend so many functions as they are required to access elem and next
    friend class MyLinkedList<T>;
    friend class LinkedStack<T>;
    friend int login(string username, string password);
    friend void deleteFitnessClass(int class_id);
    friend void updateClassDetails(int class_id);
    friend void bookAClass(int class_id);
    friend void viewClassesWithVacancies();
    friend void cancelBooking(int class_id);
    friend void changeClassCapacity(int class_id, int new_cap);
    friend void viewMemberList();
    friend void viewBookingList();
    friend void splitClass(int class_id, int cap);
    friend void quitProgram();
    friend int main();
    friend bool uniqueAdmin(int aID);
    friend bool uniqueMember(int mID);

    Node() {}     // default constructor
    Node(T elem); // non-default constructor
};

// Non-default constructor definition
template <typename T>
Node<T>::Node(T elem) : elem(elem), next(NULL) {}

// Template class MyLinkedList - generates a linked list by using objects from the Node class
template <typename T>
class MyLinkedList
{
private:
    Node<T> *head; // pointer to the head of list
public:
    MyLinkedList();          // default constructor
    ~MyLinkedList();         // destructor to clean up all nodes
    bool empty() const;      // checks if list is empty
    void addFront(T elem);   // adds a new Node at the front of the list
    void removeFront();      // removes front Node from the list
    int countElem(T elem);   // counts the frequency of an element in the list
    int getIndexOf(T elem);  // returns first index of an element in the list, -1 if the element is not present
    void display() const;    // displays the linked list
    T front();               // returns the element at the front of the linked list
    void removeElem(T elem); // removes a specific element

    // Friend classes and functions - important to friend so many functions as they are required to access head
    friend class LinkedStack<T>;
    friend int login(string username, string password);
    friend void deleteFitnessClass(int class_id);
    friend void updateClassDetails(int class_id);
    friend void bookAClass(int class_id);
    friend void viewClassesWithVacancies();
    friend void cancelBooking(int class_id);
    friend void changeClassCapacity(int class_id, int new_cap);
    friend void viewMemberList();
    friend void viewBookingList();
    friend void splitClass(int class_id, int cap);
    friend void quitProgram();
    friend int main();
    friend bool uniqueAdmin(int aID);
    friend bool uniqueMember(int mID);
};

// default constructor definition
template <typename T>
MyLinkedList<T>::MyLinkedList()
{
    this->head = NULL; // pointing the head node to NULL
}

//====================================
// destructor to clean up all nodes
template <typename T>
MyLinkedList<T>::~MyLinkedList()
{
    while (head != NULL)
    {
        removeFront(); // calling the removeFront function repeatedly to clean up the nodes
    }
    delete head; // finally deleting the head node
}

// front function definition
template <typename T>
T MyLinkedList<T>::front()
{
    return head->elem; // returning the element that head is pointing to
}

// Checks if the list is empty or not
template <typename T>
bool MyLinkedList<T>::empty() const
{
    if (head == NULL)
    {
        return true; // if head is pointing to NULL (initial state), then the program returns true
    }
    return false; // list is not empty
}

// adds a node at the front of the list
template <typename T>
void MyLinkedList<T>::addFront(T elem)
{
    Node<T> *n = new Node<T>(elem); // creates a new node
    n->elem = elem;                 // stores the element in the node
    n->next = head;                 // points the head of the node to the current head
    head = n;                       // assigns the new node as the head
}

// remove the first node from the list
template <typename T>
void MyLinkedList<T>::removeFront()
{
    Node<T> *o = head; // creates a new node and stores the head
    head = o->next;    // makes the head point to the next element
    delete o;          // deletes the previous head stored in the new node
}

// count frequency of an element in the list
template <typename T>
int MyLinkedList<T>::countElem(T elem)
{
    Node<T> *curr = head;
    int count = 0;
    while (curr != NULL) // traverse through the list to find the element
    {
        if (curr->elem == elem)
        {
            count++;
        } // whenever the element in the node is equal to the key element, the count is increased by 1
        curr = curr->next;
    }
    return count;
}

// returns the index of a given element
template <typename T>
int MyLinkedList<T>::getIndexOf(T elem)
{
    int index = 0; // initial index
    Node<T> *curr = head;
    while (curr != NULL) // traverse through the list until the element is found
    {
        if (curr->elem == elem)
        {
            return index; // whenever the element in the node is equal to the key element, the index is returned
        }
        index++; // index gets incremented as we move through the list
        curr = curr->next;
    }
    return -1; //-1 is returned if the element is not found
}

// display all nodes of the linked list
template <typename T>
void MyLinkedList<T>::display() const
{
    Node<T> *curr = head;
    cout << "HEAD -> ";
    while (curr != NULL) // traverse through the list printing each element
    {
        cout << curr->elem << " -> "; // the element is printed with a arrow
        curr = curr->next;
    }
    cout << "NULL";
}

// remove a specific element from the list
template <typename T>
void MyLinkedList<T>::removeElem(T elem)
{
    int index = getIndexOf(elem); // first index of the element is found
    if (index != -1)              // made sure that element exists in the list
    {
        Node<T> *curr = head;
        for (int i = 0; i < index - 1; i++) // traverse through the array till the element before the desired element
        {
            curr = curr->next;
        }
        Node<T> *temp = curr->next; // store the node of the element to be deleted
        curr->next = temp->next;    // make the previous node of the node to be deleted point to the next node
        delete temp;                // the node is deleted
    }
}

// Template class for Stack
template <typename T>
class LinkedStack
{
private:
    int n;             // number of elements in stack
    MyLinkedList<T> S; // Linked List based implementation

public:
    LinkedStack();              // default constructor
    int size() const;           // returns size of the stack
    bool empty() const;         // returns true if stack is empty
    T top();                    // returns the top element in the stack
    void push(const T &elem);   // pushes a element at the top of the stack
    void pop();                 // pops out the topmost element from the stack
    void remove(const T &elem); // removes a specific element from the stack
};

// Default constructor definition
template <typename T>
LinkedStack<T>::LinkedStack() : n(0) {}

template <typename T>
int LinkedStack<T>::size() const
{
    return n; // returns size of the stack
}

template <typename T>
bool LinkedStack<T>::empty() const
{
    return n == 0; // returns true if stack is empty
}

template <typename T>
T LinkedStack<T>::top()
{
    if (empty()) // to handle the case where stack might be empty
    {
        cout << "Stack Empty" << endl;
        exit(1); // exits with code 1
    }
    return S.front(); // returns the top element in the stack
}

template <typename T>
void LinkedStack<T>::push(const T &elem)
{
    n++;              // increses the current size of the stack
    S.addFront(elem); // adds the element to the front of the linked list based stack
}

template <typename T>
void LinkedStack<T>::pop()
{
    if (empty()) // to handle the exception where stack might be empty
    {
        cout << "Stack is empty" << endl;
        exit(1); // exits with code 1
    }
    n--;             // decreases the current size of stack
    S.removeFront(); // removes the front of the linked-list based stack
}

// removes a specific element from the stack
template <typename T>
void LinkedStack<T>::remove(const T &elem)
{
    bool flag = true;
    T *arr = new T[n - 1]; // a new array is created to store the members of the stack that are popped out while removing the specific element
    int index = 0;
    while (!(this->empty()))
    {
        if (elem == this->top()) // keeps checking the top of the stack with the element given
        {
            this->pop();  // pops the element when found
            flag = false; // flag turns false - meaning the element was found in the stack
            break;
        }
        arr[index] = this->top(); // keeps storing the popped out elements from the stack so they can be pushed later
        this->pop();
        index++;
    }
    for (int i = index - 1; i >= 0; i--) // pushed the popped out elements from the array into the stack in order
    {
        this->push(arr[i]);
    }
    if (flag) // if flag is true - the element is not present in the stack
    {
        cout << "Member not registered in the Fitness class" << endl;
    }
}

// Class definition for Parent class
class Person
{
protected:
    string firstN;
    string lastN;
    string userN;
    string pswd;

public:
    Person() {}
    Person(string fN, string lN, string uN, string p) : firstN(fN), lastN(lN), userN(uN), pswd(p) {}
};

// Admin Class
class Admin : public Person // Inheriting from Person class
{
private:
    int adminID;

public:
    Admin() : Person(){};                                                                              // Default constructor
    Admin(int id) : adminID(id), Person("admin", "admin", "admin1", "admin1") {}                       // 1st Admin constructor
    Admin(int id, string fn, string ln, string un, string pd) : adminID(id), Person(fn, ln, un, pd) {} // Non-Default constructor

    // getters and setters function prototypes
    string getAdminUsername();

    string getAdminPass();

    string getAdminFN();

    string getAdminLN();

    int getAdminID();
};

// Member class declaration
class Member : public Person
{
private:
    int memberID;

public:
    Member() : Person() {} // Default constructor

    Member(int id, string fn, string ln, string un, string pd) : memberID(id), Person(fn, ln, un, pd) {} // Non-default constructor

    // getters and setters
    string getMemberUsername();

    string getMemberPass();

    int getMemberID();

    string getMemberFN();

    string getmemberLN();
};

// Fitness Class
class FitnessClass
{
private:
    int classID;
    string classN;
    string classDate;
    string classTime;
    int maxCap;
    int currCap;
    int roomN;
    LinkedStack<int> memberStack;

public:
    // Declaring classes and functions as Friends
    friend class Admin;
    friend class Member;
    friend void viewBookingList();
    friend void splitClass(int class_id, int cap);
    friend void quitProgram();
    friend int main();

    FitnessClass() {} // Default constructor

    FitnessClass(int id, string cn, string cd, string ct, int cap, int rno) : classID(id), classN(cn), classDate(cd), classTime(ct), maxCap(cap), roomN(rno), currCap(0) {}

    // Important Function Declarations
    void addMemberToClass(int mID); // registers a member in a class

    void removeMemberFromClass(int mID); // removes a member from a class

    void printClassInfo(); // prints the class info

    // getters and setters prototypes
    int getClassID();

    void setClassName(string cn);

    void setClassCap(int cap);

    void setClassRoom(int rno);

    void setClassTime(string ct);

    void setClassDate(string cd);

    int getCurrCap();

    int getMaxCap();

    string getClassName();

    string getClassDate();

    string getClassTime();

    int getClassRno();
};

// overloading the == operator to compare between to FitnessClass objects - used later
bool operator==(FitnessClass f1, FitnessClass f2)
{
    return f1.getClassID() == f2.getClassID();
}

// Global Variables
MyLinkedList<Admin> adminList;          // Linked list containing details of all admins
MyLinkedList<Member> memberList;        // Linked list containing details of all members
MyLinkedList<FitnessClass> fitnessList; // Linked list containing details of all fitness classes

// Funtion declarations - each function is properly defined later
FitnessClass addFitnessClass();

void deleteFitnessClass(int class_id);

void updateClassDetails(int class_id);

void bookAClass(int class_id);

void viewClassesWithVacancies();

void cancelBooking(int class_id);

void changeClassCapacity(int class_id, int new_cap);

void quitProgram();

void viewMemberList();

void viewBookingList();

void splitClass(int class_id, int cap);

int mID; // global variable to store the member ID of the currently logged in member
int login(string username, string password);

void executeAdmin();

void executeMember();

bool checkAdmin();

bool checkMember();

void mainMenu();

// Takes the password and username of an Admin as input for a login and calls the login functiomn to verify credentials
bool checkAdmin()
{
    string u, p;
    cout << "Please enter your username:" << endl;
    cin >> u;
    cout << "Please enter your password:" << endl;
    cin >> p;
    int temp = login(u, p);
    return (temp == 1); // 1 corresponds to Admin
}

// Takes the password and username of and Admin as input for a login and calls the login functiomn to verify credentials
bool checkMember()
{
    string u, p;
    cout << "Please enter your username:" << endl;
    cin >> u;
    cout << "Please enter your password:" << endl;
    cin >> p;
    int temp = login(u, p);
    return (temp == 2); // 2 corresponds to member
}

// Main Menu - to ask the user whether they wish to login as an Admin or Member
void mainMenu()
{
    string s;
    cout << "Welcome to the Fitness management System!" << endl;
    while (true)
    {
        cout << "Please enter category of account before logging in: [admin/member]" << endl;
        cin >> s;

        if (s == "admin")
        {
            if (checkAdmin()) // checks admin Credentials
            {
                cout << "You have logged in successfully!" << endl;
                aL = true; // flag used to identify if admin is logged in or not
                break;
            }
            else
            {
                cout << "Wrong Credentials! Try again." << endl;
            }
        }
        else if (s == "member") // checks member credentials
        {
            if (checkMember())
            {
                cout << "You have logged in successfully!" << endl;
                mL = true; // flag used to identify if member is logged in or not

                break;
            }
            else
            {
                cout << "Wrong Credentials! Try again." << endl;
            }
        }
        // if the user enters something other than "admin" or "member"
        else
        {
            cout << "ERROR! Please enter a valid input." << endl;
        }
    }
}
Admin registerAdmin(string firstname, string lastname);
Member registerMember(string fn, string ln);

int main()
{
    // Creating first admin - this part of the code is commented as it wasn't asked in the second assignment but makes it very easy to test the code
    // Admin adm(1);
    // adminList.addFront(adm);
    // cout << "Okay" << endl;

    // Initializing variables
    mL = false;
    aL = false;

    // Opening files in input mode
    ifstream classFile;
    classFile.open("FitnessClasses.txt", ios::in);
    if (classFile.fail())
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    ifstream adminFile;
    adminFile.open("Admins.txt", ios::in);
    if (adminFile.fail())
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    ifstream memberFile;
    memberFile.open("Members.txt", ios::in);
    if (memberFile.fail())
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }

    // Taking data from the Admin csv file and dumping it in the Admin Linked List
    string adminStr = "";
    string tempStrA;
    int count(0);
    int fileIDA;
    string fileFNA, fileLNA, fileUNA, filePA;
    while (!adminFile.eof())
    {
        adminFile >> tempStrA;
        for (int i = 0; i < tempStrA.length(); i++)
        {
            if (tempStrA[i] == ',')
            {
                switch (count)
                {
                case 0:
                {
                    fileIDA = stoi(adminStr); // reference geeks for geeks - converting string to integer

                    count++;
                    break;
                }
                case 1:
                {
                    fileFNA = adminStr;
                    count++;
                    break;
                }
                case 2:
                {
                    fileLNA = adminStr;
                    count++;
                    break;
                }
                case 3:
                {
                    fileUNA = adminStr;
                    count++;
                    break;
                }

                default:
                    break;
                }

                adminStr = "";
                continue;
            }

            adminStr += tempStrA[i];
        }
        filePA = adminStr;
        Admin tempA(fileIDA, fileFNA, fileLNA, fileUNA, filePA);
        adminList.addFront(tempA);
        adminStr = "";
        count = 0;
    }
    adminFile.close();

    // Taking data from the Member csv file and dumping it in the Member Linked List
    string memberStr = "";
    string tempStrM;
    count = 0;
    int fileIDM;
    string fileFNM, fileLNM, fileUNM, filePM;
    while (!memberFile.eof())
    {
        memberFile >> tempStrM;
        for (int i = 0; i < tempStrM.length(); i++)
        {
            if (tempStrM[i] == ',')
            {
                switch (count)
                {
                case 0:
                {
                    fileIDM = stoi(memberStr); // reference geeks for geeks - converting string to integer

                    count++;
                    break;
                }
                case 1:
                {
                    fileFNM = memberStr;
                    count++;
                    break;
                }
                case 2:
                {
                    fileLNM = memberStr;
                    count++;
                    break;
                }
                case 3:
                {
                    fileUNM = memberStr;
                    count++;
                    break;
                }

                default:
                    break;
                }

                memberStr = "";
                continue;
            }

            memberStr += tempStrM[i];
        }
        filePM = memberStr;
        Member tempM(fileIDM, fileFNM, fileLNM, fileUNM, filePM);
        memberList.addFront(tempM);
        memberStr = "";
        count = 0;
    }
    memberFile.close();

    // Taking data from the FitnessClasses csv file and dumping it in the fitness class Linked List
    string fitnessStr = "";
    string tempStrF;
    count = 0;
    int fileIDF, fileMF, fileRF;
    string fileCNF, fileDF, fileTF;
    while (!classFile.eof())
    {
        classFile >> tempStrF;
        for (int i = 0; i < tempStrF.length(); i++)
        {
            if (tempStrF[i] == ',')
            {
                switch (count)
                {
                case 0:
                {
                    fileIDF = stoi(fitnessStr); // reference geeks for geeks - converting string to integer
                    count++;
                    fitnessStr = "";
                    break;
                }
                case 1:
                {
                    fileCNF = fitnessStr;
                    count++;
                    fitnessStr = "";
                    break;
                }
                case 2:
                {
                    fileDF = fitnessStr;
                    count++;
                    fitnessStr = "";
                    break;
                }
                case 3:
                {
                    fileTF = fitnessStr;
                    count++;
                    fitnessStr = "";
                    break;
                }
                case 4:
                {
                    fileMF = stoi(fitnessStr);
                    count++;
                    fitnessStr = "";
                    break;
                }
                case 5:
                {
                    fileRF = stoi(fitnessStr);
                    count++;
                    fitnessStr = "";
                    break;
                }
                case 6:
                {
                    fitnessStr += tempStrF[i];
                    break;
                }
                default:
                {
                    break;
                }
                }

                continue;
            }

            fitnessStr += tempStrF[i];
        }

        FitnessClass tempF(fileIDF, fileCNF, fileDF, fileTF, fileMF, fileRF);
        fitnessList.addFront(tempF);

        // dumping data into the Member Stack inside each fitness class
        string t = "";
        Node<FitnessClass> *temp = fitnessList.head;
        for (int i = 1; i < fitnessStr.length(); i++)
        {

            if (fitnessStr[i] == ',' or fitnessStr[i] == ']')
            {
                int m = stoi(t);
                temp->elem.memberStack.push(m);
                t = "";
                continue;
            }
            t += fitnessStr[i];
        }

        fitnessStr = "";
        count = 0;
    }
    classFile.close();

    // Calling the MainMenu function
    mainMenu();
    while (aL or mL)
    {
        if (aL)
        {
            executeAdmin(); // executes the admin part
        }
        if (mL)
        {
            executeMember(); // executes the member part
        }
    }

    return 0;
}

// Login functions takes in username and password, compares it with the data avaiable, and verifies credentials
int login(string username, string password)
{
    int num = 0;
    Node<Admin> *temp = adminList.head;
    while (temp != NULL)
    {

        if (temp->elem.getAdminUsername() == username && temp->elem.getAdminPass() == password)
        {
            num = 1;
        }
        temp = temp->next;
    }
    Node<Member> *tempM = memberList.head;
    while (tempM != NULL)
    {
        if (tempM->elem.getMemberUsername() == username && tempM->elem.getMemberPass() == password)
        {
            mID = tempM->elem.getMemberID();
            num = 2;
        }
        tempM = tempM->next;
    }
    return num;
}

// checks if the admin ID generated is unique
bool uniqueAdmin(int aID)
{
    Node<Admin> *temp = adminList.head;
    while (temp != NULL)
    {

        if (temp->elem.getAdminID() == aID)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// checks if the member ID generated is unique
bool uniqueMember(int mID)
{
    Node<Member> *temp = memberList.head;
    while (temp != NULL)
    {

        if (temp->elem.getMemberID() == mID)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// registers a new Admin given a first name and last name
Admin registerAdmin(string fn, string ln)
{
    srand(time(0)); // randomizes the seed

    int aID; // admin ID
    bool unique = true;
    // checks if the admin ID is unique or not
    do
    {
        aID = rand() % 9000 + 1000; // generates random 4 digit admin ID

        unique = uniqueAdmin(aID);

    } while (unique);

    string uName = "";
    for (int i = 0; i < fn.length(); i++)
    {
        uName += tolower(fn[i]);
    }
    uName += to_string(aID);

    int randNo = rand() % 9000 + 1000;
    string pwd = "";
    for (int i = 0; i < ln.length(); i++)
    {
        pwd += tolower(ln[i]);
    }
    pwd += to_string(randNo);
    Admin newAdmin(aID, fn, ln, uName, pwd); // creates the new admin object

    // Displays the information of the newly created admin to the user
    cout << "The admin is registered successfully! \nThe credentials are as follows:" << endl;
    cout << "Admin ID, Username, Password: " << aID << ", " << uName << ", " << pwd << endl;

    return newAdmin; // returns the admin object
}

//registers a new member
Member registerMember(string fn, string ln)
{
    srand(time(0)); // randomizes seed
    int mID;
    // checks if member ID is unique or not
    bool unique = true;
    do
    {
        mID = rand() % 9000 + 1000; //generated random 4 digit member ID
        unique = uniqueMember(mID);

    } while (unique);

    string uName = "";
    for (int i = 0; i < fn.length(); i++)
    {
        uName += tolower(fn[i]);
    }
    uName += to_string(mID);

    int randNo = rand() % 9000 + 1000;
    string pwd = "";
    for (int i = 0; i < ln.length(); i++)
    {
        pwd += tolower(ln[i]);
    }
    pwd += to_string(randNo);
    Member newMember(mID, fn, ln, uName, pwd); //generates new member object
    cout << "The member is registered successfully! \nThe credentials are as follows:" << endl;
    cout << "Member ID, Username, Password: " << mID << ", " << uName << ", " << pwd << endl;
    return newMember; //returns member object
}

// logout function
void logout()
{
    aL = false; //turns both of them to false and calls the mainMenu function  again
    mL = false;
    mainMenu();
}

//provides the Admin with the options available
void executeAdmin()
{
    bool run = true;
    int n;
    cout << "The list of available operations for Admins:" << endl;
    cout << " 1) Register a new Admin \n 2) Register a new member \n 3) View the list of members \n 4) Add a fitness class \n 5) Delete a fitness class \n 6) Update the details of a fitness class \n 7) Update the capacity of a fitness class \n 8) Split a fitness class into two classes \n 9) View the classes with vacancies \n 10) Logout \n 11) Quit" << endl;
    do
    {
        cout << "Enter the number of the required action: [1-11]" << endl;
        cin >> n;
        switch (n)
        {
        case 1:
        {
            string fn, ln;
            cout << "Please provide the first name of the admin" << endl;
            cin >> fn;
            cout << "Please provide the last name of the admin" << endl;
            cin >> ln;
            Admin tempA = registerAdmin(fn, ln);
            adminList.addFront(tempA);

            break;
        }
        case 2:
        {
            string fn, ln;
            cout << "Please provide the first name of the member" << endl;
            cin >> fn;
            cout << "Please provide the last name of the member" << endl;
            cin >> ln;
            Member tempM = registerMember(fn, ln);
            memberList.addFront(tempM);

            break;
        }
        case 3:
        {
            viewMemberList();
            break;
        }
        case 4:
        {
            FitnessClass tempC = addFitnessClass();
            fitnessList.addFront(tempC);
            break;
        }
        case 5:

        {
            int id;
            cout << "Please provide the Class ID: " << endl;
            cin >> id;
            deleteFitnessClass(id);
            break;
        }
        case 6:
        {
            int id;
            cout << "Please provide the Class ID: " << endl;
            cin >> id;
            updateClassDetails(id);
            break;
        }

        case 7:
        {
            int id, n;
            cout << "Please provide the Class ID: " << endl;
            cin >> id;
            do
            {
                cout << "Enter the new class capacity [range of 5 - 15]" << endl;
                cin >> n;
            } while (!(n >= 5 and n <= 15));
            changeClassCapacity(id, n);
            break;
        }
        case 8:
        {
            int id, cap;
            char s;
            cout << "Please provide the Class ID: " << endl;
            cin >> id;

            while (true)
            {
                cout << "Do you want to a new class capacity?[Y/N]" << endl;
                cin >> s;
                if (s == 'Y' or s == 'y')
                {
                    cout << "Please provide new class capacity: " << endl;
                    cin >> cap;
                    splitClass(id, cap);
                    break;
                }
                else if (s == 'N' or s == 'n')
                {
                    splitClass(id, 10);
                    break;
                }

                cout << "Error! Please provide a valid input" << endl;
            }

            break;
        }
        case 9:
        {
            viewClassesWithVacancies();
            break;
        }
        case 10:
        {
            run = false;
            logout();
            break;
        }
        case 11:
        {
            quitProgram();
            break;
        }
        default:
        {
            cout << "ERROR! Please select a valid option" << endl;
            break;
        }
        }
    } while (run);
}

//provides the member with options available
void executeMember()
{
    bool runM = true;
    char n;
    cout << "The list of available operations for Members:" << endl;
    cout << " 1) Book a Fitness Class \n 2) Display Classes with vacancies \n 3) Cancel booking \n 4) View Booking List \n 5) Logout \n 6) Quit" << endl;
    do
    {
        cout << "Enter the number of the required action: [1-6]" << endl;
        cin >> n;
        switch (n)
        {
        case '1':
        {
            int id;
            cout << "Please provide the Class ID of the class you want to book:" << endl;
            cin >> id;
            bookAClass(id);
            break;
        }
        case '2':
        {
            viewClassesWithVacancies();
            break;
        }
        case '3':
        {
            int id;
            cout << "Please provide the Class ID of the class you want to cancel:" << endl;
            cin >> id;
            cancelBooking(id);
            break;
        }
        case '4':
        {
            viewBookingList();
            break;
        }
        case '5':
        {
            runM = false;
            logout();
            break;
        }
        case '6':
        {
            quitProgram();
            break;
        }
        default:
        {
            cout << "ERROR! Please select a valid option" << endl;
            break;
        }
        }

    } while (runM);
}

// getters and setters
string Admin::getAdminUsername()
{
    return userN;
}

string Admin::getAdminPass()
{
    return pswd;
}

string Admin::getAdminFN()
{
    return firstN;
}

string Admin::getAdminLN()
{
    return lastN;
}

int Admin::getAdminID()
{
    return adminID;
}

// Getters and setters definitions
string Member::getMemberUsername()
{
    return userN;
}

string Member::getMemberPass()
{
    return pswd;
}

int Member::getMemberID()
{
    return memberID;
}

string Member::getMemberFN()
{
    return firstN;
}

string Member::getmemberLN()
{
    return lastN;
}

// To print details of a Fitness Class
void FitnessClass::printClassInfo()
{
    cout << "Class Details" << endl;
    cout << "Class ID: " << classID << endl;
    cout << "Class Name: " << classN << endl;
    cout << "Class Date: " << classDate << endl;
    cout << "Class Time: " << classTime << endl;
    cout << "Room Number: " << roomN << endl;
}

//adds member to class - stack
void FitnessClass::addMemberToClass(int mID)
{
    memberStack.push(mID);
    currCap++;
}

//removes member from class
void FitnessClass::removeMemberFromClass(int mID)
{
    memberStack.remove(mID);
    currCap--;
}

// Defining getters and setters
int FitnessClass::getClassID()
{
    return classID;
}

void FitnessClass::setClassName(string cn)
{
    classN = cn;
}

void FitnessClass::setClassCap(int cap)
{
    maxCap = cap;
}

void FitnessClass::setClassRoom(int rno)
{
    roomN = rno;
}

void FitnessClass::setClassTime(string ct)
{
    classTime = ct;
}

void FitnessClass::setClassDate(string cd)
{
    classDate = cd;
}

int FitnessClass::getCurrCap()
{
    return currCap;
}

int FitnessClass::getMaxCap()
{
    return maxCap;
}

string FitnessClass::getClassName()
{
    return classN;
}

string FitnessClass::getClassDate()
{
    return classDate;
}

string FitnessClass::getClassTime()
{
    return classTime;
}

int FitnessClass::getClassRno()
{
    return roomN;
}

//creates a new fitness class
FitnessClass addFitnessClass()
{
    int id, cap, rno;
    string cn, cd, ct;
    cout << "Please provide the following:" << endl;
    cout << "Class ID:" << endl;
    cin >> id;
    cout << "Class Name:" << endl;
    cin >> cn;
    cout << "Class Date:" << endl;
    cin >> cd;
    cout << "Class Time:" << endl;
    cin >> ct;
    cout << "Maximum Capacity:" << endl;
    cin >> cap;
    cout << "Room Number:" << endl;
    cin >> rno;
    FitnessClass newFitnessClass(id, cn, cd, ct, cap, rno);
    cout << "Fitness Class Added Successfully!" << endl;
    return newFitnessClass;
}

// Deletes Fitness Class
void deleteFitnessClass(int class_id)
{
    Node<FitnessClass> *temp = fitnessList.head;
    // cout<<temp->elem.getAdminUsername()<<endl;
    while (temp != NULL)
    {

        if (temp->elem.getClassID() == class_id)
        {

            fitnessList.removeElem(temp->elem);
            cout << "Class Deleted!" << endl;
            return;
        }

        temp = temp->next;
    }
    cout << "Class not Found" << endl;
}

// Updates class details
void updateClassDetails(int class_id)
{
    Node<FitnessClass> *temp = fitnessList.head;
    while (temp != NULL)
    {

        if (temp->elem.getClassID() == class_id)
        {

            cout << "What do you want to update?" << endl;
            cout << "1. Class Name \n2. Class Capacity \n3. Class Room Number \n4. Class Date \n5. Class Time" << endl;
            cout << "Enter the number of the required action: [1-5]" << endl;
            char o;
            cin >> o;

            switch (o)
            {
            case '1':
            {
                string cn;
                cout << "Enter the new class name:" << endl;
                cin >> cn;
                temp->elem.setClassName(cn);
                cout << "Name Updated!" << endl;
                break;
            }
            case '2':
            {
                int cap;
                cout << "Enter the new class capacity:" << endl;
                cin >> cap;
                temp->elem.setClassCap(cap);
                cout << "Capacity Updated!" << endl;
                break;
            }
            case '3':
            {
                int rno;
                cout << "Enter the new class room number" << endl;
                cin >> rno;
                temp->elem.setClassRoom(rno);
                cout << "Room number updated!" << endl;
                break;
            }
            case '4':
            {
                string cd;
                cout << "Enter the new class date" << endl;
                cin >> cd;
                temp->elem.setClassDate(cd);
                cout << "Class date updated!" << endl;
                break;
            }
            case '5':
            {
                string ct;
                cout << "Enter the new class time" << endl;
                cin >> ct;
                temp->elem.setClassTime(ct);
                cout << "Class time updated!" << endl;
                break;
            }
            default:
                cout << "Invalid Selection!" << endl;
                break;
            }
            return;
        }

        temp = temp->next;
    }
    cout << "Class not Found" << endl;
}

// Books a class
void bookAClass(int class_id)
{
    Node<FitnessClass> *temp = fitnessList.head;
    while (temp != NULL)
    {

        if (temp->elem.getClassID() == class_id)
        {

            if (temp->elem.getCurrCap() < temp->elem.getMaxCap()) // checks if there is space in class
            {
                // cout << "Current Capacity: " << temp->elem.getCurrCap() << " Maximum Capacity: " << temp->elem.getMaxCap() << endl;
                temp->elem.addMemberToClass(mID);
                cout << "Class Booked" << endl;
                // cout << "Current Capacity: " << temp->elem.getCurrCap() << " Maximum Capacity: " << temp->elem.getMaxCap() << endl;
            }
            else
            {
                cout << "Class Full" << endl;
            }
            return;
        }

        temp = temp->next;
    }

    cout << "Class Not Found" << endl;
}

// Prints details about classes with vacancies
void viewClassesWithVacancies()
{
    bool flag = true;
    Node<FitnessClass> *temp = fitnessList.head;
    while (temp != NULL)
    {
        if (!fitnessList.empty())
        {

            if (temp->elem.getCurrCap() < temp->elem.getMaxCap()) // Checks if there is space in the calss
            {
                flag = false;
                temp->elem.printClassInfo();
            }
        }
        temp = temp->next;
    }

    // check if there are any vacant classes or not
    if (flag)
    {
        cout << "No vacant classes found" << endl;
    }
}

// Cancels booking of member
void cancelBooking(int class_id)
{
    Node<FitnessClass> *temp = fitnessList.head;
    while (temp != NULL)
    {

        if (temp->elem.getClassID() == class_id)
        {

            temp->elem.removeMemberFromClass(mID);
            cout << "Booking cancelled" << endl;
            return;
        }

        temp = temp->next;
    }
    cout << "Class not Found" << endl;
}

//changes class capacity
void changeClassCapacity(int class_id, int new_cap)
{
    Node<FitnessClass> *temp = fitnessList.head;
    while (temp != NULL)
    {

        if (temp->elem.getClassID() == class_id)
        {
            if (temp->elem.getCurrCap() == temp->elem.getMaxCap()) //removes extra members
            {
                for (int i = 0; i < new_cap - (temp->elem.getMaxCap()); i++)
                {
                    fitnessList.removeFront();
                }
            }

            temp->elem.setClassCap(new_cap); //sets the new class capacity
            cout << "Class Capacity Updated" << endl;
            return;
        }

        temp = temp->next;
    }
    cout << "Class not Found" << endl;
}

//admin can view the member list
void viewMemberList()
{
    int i(1);
    Node<Member> *temp = memberList.head;
    //displays the details of every member avaiable
    while (temp != NULL)
    {

        cout << "Details of Member " + to_string(i) << ": " << endl;
        cout << "Member ID:" << temp->elem.getMemberID() << endl;
        cout << "First Name:" << temp->elem.getMemberFN() << endl;
        cout << "Last Name:" << temp->elem.getmemberLN() << endl;
        cout << endl;

        temp = temp->next;
        i++;
    }
    if (i == 1)
    {
        cout << "No members registered" << endl;
    }
}

//shows the member the classes they have booked
void viewBookingList()
{
    int index(0);
    bool flag = true;
    Node<FitnessClass> *temp = fitnessList.head;

    cout << "The booking list is: " << endl;
    while (temp != NULL)
    {
        int n = temp->elem.memberStack.size();
        int arr[n]; //stores the randomly popped elements in a array
        while (!(temp->elem.memberStack.empty()))
        {
            int curr = temp->elem.memberStack.top();
            if (mID == curr)
            {
                cout << "Class ID: " << temp->elem.getClassName() << endl;
                cout << "Date: " << temp->elem.getClassDate() << endl;
                cout << "Time: " << temp->elem.getClassTime() << endl;
                cout << "Room Number: " << temp->elem.getClassRno() << endl;
                cout << endl;

                flag = false;
                for (int i = index - 1; i >= 0; i++)
                {
                    temp->elem.memberStack.push(arr[i]); //pushed the elements back into the stack
                }

                break;
            }
            arr[index] = curr;
            index++;
            temp->elem.memberStack.pop();
        }

        temp = temp->next;
    }
    if (flag)
    {
        cout << "Member has no bookings" << endl;
    }
}

//splits the class into two classes 
void splitClass(int class_id, int cap)
{
    Node<FitnessClass> *temp = fitnessList.head;
    while (temp != NULL)
    {
        FitnessClass currClass = temp->elem;
        if (currClass.getClassID() == class_id)
        {
            int nID;
            do
            {
                cout << "Please provide a new Class Id" << endl;
                cin >> nID;
            } while (nID == currClass.getClassID());
            char d;
            string nD = currClass.getClassDate();
            string nT = currClass.getClassTime();
            while (true)
            {
                cout << "Do you want to set a new date and time?[Y/N]" << endl;
                cin >> d;
                if (d == 'Y' or d == 'y')
                {
                    cout << "Plese enter new class date:" << endl;
                    cin >> nD;
                    cout << "Please enter new class time:" << endl;
                    cin >> nT;
                    break;
                }
                if (d == 'N' or d == 'n')
                {
                    break;
                }
                cout << "ERROR! Please enter a valid input." << endl;
            }
            FitnessClass newFitnessClass(nID, currClass.getClassName(), nD, nT, cap, currClass.getClassRno());
            int oCap = currClass.getCurrCap();
            int t = oCap - cap;
            //moves extra members from one class to the other 
            if (t > 0)
            {
                int arr[t];
                for (int i = 0; i < t; i++)
                {
                    arr[i] = currClass.memberStack.top();
                }
                for (int i = 0; i < t; i++)
                {
                    newFitnessClass.memberStack.push(arr[i]);
                    if (i == cap)
                    {
                        break;
                    }
                }
            }

            changeClassCapacity(class_id, cap);

            fitnessList.addFront(newFitnessClass);

            cout << "Class successfully split" << endl;
            return;
        }

        temp = temp->next;
    }
    cout << "Class not Found" << endl;
}

//quits the program and saves information in files
void quitProgram()
{
    ofstream classFile;
    classFile.open("FitnessClasses.txt", ios::out);
    if (classFile.fail())
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    ofstream adminFile;
    adminFile.open("Admins.txt", ios::out);
    if (adminFile.fail())
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    ofstream memberFile;
    memberFile.open("Members.txt", ios::out);
    if (memberFile.fail())
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }

    Node<FitnessClass> *tempF = fitnessList.head;
    while (tempF != NULL)
    {
        classFile << tempF->elem.getClassID() << "," << tempF->elem.getClassName() << "," << tempF->elem.getClassDate() << "," << tempF->elem.getClassTime() << "," << tempF->elem.getMaxCap() << "," << tempF->elem.getClassRno() << ",";
        classFile << "[";
        while (!(tempF->elem.memberStack.empty()))
        {
            classFile << tempF->elem.memberStack.top();
            tempF->elem.memberStack.pop();
            if (!(tempF->elem.memberStack.empty()))
            {
                classFile << ",";
            }
        }
        classFile << "]" << endl;

        tempF = tempF->next;
    }

    Node<Admin> *tempA = adminList.head;
    while (tempA != NULL)
    {
        adminFile << tempA->elem.getAdminID() << "," << tempA->elem.getAdminFN() << "," << tempA->elem.getAdminLN() << "," << tempA->elem.getAdminUsername() << "," << tempA->elem.getAdminPass() << endl;

        tempA = tempA->next;
    }

    Node<Member> *tempM = memberList.head;
    while (tempM != NULL)
    {
        memberFile << tempM->elem.getMemberID() << "," << tempM->elem.getMemberFN() << "," << tempM->elem.getmemberLN() << "," << tempM->elem.getMemberUsername() << "," << tempM->elem.getMemberPass() << endl;
        tempM = tempM->next;
    }
    
    //closes all files
    adminFile.close();
    memberFile.close();
    classFile.close();
    cout << "Thank you. Exited" << endl;
    exit(0);
}