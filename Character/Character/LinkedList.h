//
//  LinkedList.hpp
//  Character
//
//  Created by Khang Tran on 2/2/18.
//  Copyright © 2018 Khang Tran. All rights reserved.
//

# ifndef LIST_H_
# define LIST_H_
# include <cstddef> //for NULL
# include <assert.h>
# include <iostream>
using namespace std;

template <class listdata> //list stores generic listdata, not any specific C++ type
class List {
private:
    struct Node {
        listdata data;
        Node* linknext;
        Node * linkprevious;
        
        // this is constructor of the node, it is defined right in the node definition itself
        Node(listdata newData){
            data = newData;
            linknext = NULL;   /** when first created, linknext of each node always point to NULL*/
            linkprevious = NULL;
        }
    };
    
    Node* start;
    Node* stop;
    Node* iterator;
    int size;
    
    void reversePrint(Node* node) const;
    //Helper function for the public reversePrint() function.
    //Recursively prints the data in a List in reverse.
    
    bool isSorted(Node* node) const;
    //Helper function for the public isSorted() function.
    //Recursively determines whether a list is sorted in ascending order.
    
    int binarySearch(int low, int high, listdata data) const;
    //Recursively search the list by dividing the search space in half
    //Returns the index of the element, if it is found in the List
    //Returns -1 if the element is not in the List
    //Post: The iterator location has not been changed
    
public:
    
    /**Constructors and Destructors*/
    
    List();
    //Default constructor; initializes and empty list
    //Postcondition: There is now an instance of class List.
    //               The size of the list is now zero
    //               Both of start and stop, point to NULL
    
    List(const List &list);
    // copy constructor
    
    ~List();
    //Destructor. Free memory allocated to the list
    //Postcondition: Memory must be deallocated
    
    /*************************************************************************/
    /**Accessors*/
    
    listdata getStart() const;
    //Returns the first data in the list
    //Precondition: The list instance is not empty. That is, size != 0
    
    listdata getStop() const;
    //Returns the last data in the list
    //Precondition: The list instance is not empty. That is, size != 0
    
    bool isEmpty() const;
    //Determines whether a list is empty.
    
    int getSize() const;
    //Returns the size of the list
    
    bool isSorted() const;
    //Wrapper function that calls the isSorted helper function to determine whether
    //a list is sorted in ascending order.
    //We will consider that a list is trivially sorted if it is empty.
    //Therefore, no precondition is needed for this function
    
    int linearSearch(listdata Data) const;
    //Searchs the list, element by element, from the start of the List to the end of the List
    //Returns the index of the element, if it is found in the List
    //Calls the above indexing functions in its implementation
    //Returns -1 if the element is not in the List
    //Pre: length != 0
    //Post: The iterator location has not been changed
    
    int linearSearch(string data) const;
    
    int binarySearch(listdata data) const;
    //Returns the index where data is located in the List
    //Calls the private helper function binarySearch to perform the search
    //Pre: length != 0
    //Pre: List is sorted (must test on a sorted list)
    //Post: The iterator location has not been changed
    
    // ITERATOR ACCESS FUNCTIONS
    bool offEnd() const;
    //Determine whether iterator is pointing to NULL
    
    listdata getIterator() const;
    // Return the element currently pointed at the iterator
    // Precondition: iterator is not offEnd(). That is, not pointing to NULL
    
    int getIndex() const;
    //Indicates the index of the Node where the iterator is currently pointing
    //Nodes are numbered starting at 1 through the size of the list
    //Pre: size != 0
    //Pre: !offEnd()
    
    /*************************************************************************/
    /**Manipulation Procedures*/
    
    void removeStop();
    //Removes the value of the last data in the list
    //Precondition: size != 0
    //Postcondition: size decreases by 1
    
    void removeStart();
    //Removes the value of the first data in the list
    //Precondition: size != 0
    //Postcondition: size decreases by 1
    
    void insertStop (listdata data);
    //Inserts a new data at the end of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: size increases by 1
    
    void insertStart(listdata data);
    //Inserts a new data at the start of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: size increases by 1
    
    
    //     ITERATOR MANIPULATOR FUNCTIONS
    void pointIterator();
    // point iterator to the start of the list
    // Preconsition: Assume that this function is designed to point at a non-NULL node,
    //                 I will enforce !isEmpty()
    
    void advanceIterator();
    // moves the iterator up by one node towards stop
    // Precondition: currently not offEnd()
    
    void reverseIterator();
    // moves the iterator down by one node towards start
    // Precondition: currently not offEnd()
    
    void insertIterator(listdata data);
    // inserts an element after the node currently pointed to by the iterator
    // Precondition: iterator is not offEnd() (not pointing to NULL)
    // Postcondition: size++
    //                stop must be adjusted if the inserted node is also the last one in the list
    
    void removeIterator();
    // removes the element currently pointed to by the iterator. Iterator then points to NULL.
    // Precondition: !offEnd()
    // Postcondition: size--
    //                offEnd()
    //                start and stop must be adjusted
    
    void advanceToIndex(int index);
    //Moves the iterator to the node whose index number is specified in the parameter
    //Nodes are numbered starting at 1 through the size of the List
    //Pre: size != 0
    //Pre: index <= size
    
    /*************************************************************************/
    /**Additional List Operations*/
    
    void print() const;
    //Prints to the console the value of each data in the list sequentially
    //and separated by a blank space
    //Prints nothing if the list is empty
    //Prints a empty newline character if it's empty..
    
    void reversePrint() const;
    //Wrapper function that calls the reverse helper function to print a list in reverse
    //prints nothing if the List is empty
    
    void printNumberedList() const;
    // Print out the list in numbering format
    // each node's data are printed on a separated file
    
    
    bool operator==(const List& list);
    // Overloading to == comparison to compare 2 lists
};


/*************************************************************************/
/**Constructors and Destructors*/
template <class listdata>
List<listdata>::List()
{
    start = NULL;
    stop = NULL;
    iterator = NULL;
    size = 0;
}
template <class listdata>
List<listdata>::List(const List &list)
{
    if(list.start == NULL) start = stop = iterator = NULL; // If copy from an empty list
    else
    {
        start = new Node(list.start->data); //calling Node constructor
        Node* temp = list.start; //set a temporary node pointer to point at the first of the original list
        iterator = start; //set iterator to point to first node of the new list
        
        while(temp->linknext != NULL)
        {
            temp = temp->linknext; //advance up to the next node in the original list
            iterator->linknext = new Node(temp->data); //using node constructor to create new node w/ copy of data
            iterator->linknext->linkprevious = iterator; // adjust the link previous of newly created node
            iterator = iterator->linknext; //advance to this new node
        }
        stop = iterator;
        iterator = NULL;
    }
    size = list.size;
}


template <class listdata>
List<listdata>::~List()
{
    Node* b = start;
    Node* a = NULL; //a stands for "after" (i.e. after b)
    while (b != NULL)
    {
        a = b->linknext; //move a to node after b
        delete b; //remove b (you know it is not NULL from if)
        b = a; //b "catches up" with a (both point to same place in list)
    }
}

/*************************************************************************/
/**Accessors*/
template <class listdata>
listdata List<listdata>::getStart() const   //access function, return the data value of the first node
{
    assert(!isEmpty());      // enforce the precondition
    return start->data;      // Note to self: To access member of structure through a pointer, use arrow operator
}

template <class listdata>
listdata List<listdata>::getStop() const
{
    assert(!isEmpty());    // enforce the precondition
    return stop->data;
}

template <class listdata>
bool List<listdata>::isEmpty() const    // if size = 0, return true. otherwise, return false
{
    return size == 0;
}

template <class listdata>
int List<listdata>::getSize() const
{
    return size;
}

template <class listdata>
bool List<listdata>::isSorted() const          // PUBLIC
{
    return (isSorted(start));
}


template <class listdata>
bool List<listdata>::isSorted(Node* node) const // PRIVATE
{
    // Base Case: if start == NULL or if the node is at the end, return true
    if (node == NULL || node->linknext == NULL) return true;
    else  // Recursive step
    {
        if (node->data > node->linknext->data) return false;
        return(isSorted(node->linknext));   /*Important that we return here*/
    }
}

template <class listdata>
bool List<listdata>::offEnd() const
{
    return iterator == NULL;
}

template <class listdata>
listdata List<listdata>::getIterator() const
{
    assert(!offEnd());                // enforce precondition
    return iterator->data;
}

template <class listdata>
int List<listdata>::getIndex() const
{
    assert(!offEnd());
    int i = 1;
    Node* temp = iterator;
    while (temp->linkprevious != NULL)
    {
        temp = temp->linkprevious;
        i++;
    }
    return i;
}

template <class listdata>
int List<listdata>::linearSearch(listdata data) const
{
    assert(!isEmpty());
    Node* temp = start;
    int index = 1;
    while (temp != NULL)
    {
        if (temp->data == data) return index;
        index++;
        temp = temp->linknext;
    }
    return -1;
}

template <class listdata>
int List<listdata>::linearSearch(string data) const
{
    //assert(!isEmpty());
    Node* temp = start;
    int index = 1;
    while (temp != NULL)
    {
        if (temp->data->name() == data) return index;
        index++;
        temp = temp->linknext;
    }
    return -1;
}

template <class listdata>
int List<listdata>::binarySearch(listdata data) const
{
    assert(!isEmpty());
    assert(isSorted());
    return binarySearch(1, size, data);
}

template <class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data) const
{
    if ( low > high) return -1;
    int mid = low + (high -low)/2;
    Node* temp = start;
    for (int i = 1; i < mid; i++) temp = temp->linknext;
    if (temp->data == data) return mid;
    else if (data < temp->data) return(binarySearch(low, mid-1, data));
    else return(binarySearch(mid+1, high, data));
}

/*************************************************************************/
/**Manipulation Procedures*/
template <class listdata>
void List<listdata>::insertStart(listdata data)
{
    Node* N = new Node(data);
    if (size == 0)
    {
        start = N;
        stop = N;
    }
    else
    {
        N->linknext = start;
        start->linkprevious = N;     // step added for doubly linked list
        start = N;
    }
    size++;
}

template <class listdata>
void List<listdata>::insertStop(listdata data)
{
    Node* N = new Node(data);
    if (size == 0)
    {
        start = N;
        stop = N;
    }
    else
    {
        stop->linknext = N;
        N->linkprevious = stop;
        stop = N;
    }
    size++;
}

template <class listdata>
void List<listdata>::removeStart()
{    /*
      if (size == 0)
      {
      cout << "removeStart : List is empty, no data to remove." << endl;
      return;   // since this is a void function, just a return will do
      }
      */
    if (iterator == start) iterator = NULL;  // To redirect iterator if it is pointing to start
    assert(!isEmpty());
    if (size == 1)
    {
        delete start;    // ******** alternatively, can we delete stop???? What about the pointer N pointing to the node itself?
        start = stop = NULL;
        size = 0;
    }
    else
    {
        Node*temp = start;
        start = start->linknext;
        start->linkprevious = NULL;    // add in this step since we are moving on to doubly linked list
        delete temp;
        size--;
    }
}

template <class listdata>
void List<listdata>::removeStop()
{
    assert(!isEmpty());
    if (iterator == stop) iterator = NULL;
    if (size == 1)
    {
        delete stop;          // free memory from the heap
        start = stop = NULL;  // Before this step, start is point to a freed memory (dangling pointer)
        size = 0;
    }
    else
    {
        Node* temp = stop;
        stop = stop->linkprevious;
        stop->linknext = NULL;
        delete temp;
        size--;
    }
}

template <class listdata>
void List<listdata>::pointIterator()
{
    assert(!isEmpty());
    iterator = start;
}


template <class listdata>
void List<listdata>::advanceIterator()
{
    assert(!offEnd());
    iterator = iterator->linknext;
}

template <class listdata>
void List<listdata>::reverseIterator()
{
    assert(!offEnd());
    iterator = iterator->linkprevious;
    //if (offEnd()) cout << "Iterator is now pointing at NULL" << endl;
}

template <class listdata>
void List<listdata>::insertIterator(listdata data)
{
    assert(!offEnd());          // enforce the precondition
    if (iterator == stop) insertStop(data);
    else
    {
        Node* N = new Node(data);
        N->linknext = iterator->linknext;
        iterator->linknext->linkprevious = N;
        N->linkprevious = iterator;
        iterator->linknext = N;
        size++;                // enforce the postcondition: size decreases by 1
        
    }
}

template <class listdata>
void List<listdata>::removeIterator()
{
    assert(!offEnd());
    if (iterator == start) removeStart();     // size-- and iterator = NULL is enforced inside
    else if (iterator == stop) removeStop();  // size-- and iterator = NULL is enforced inside
    else
    {
        iterator->linknext->linkprevious = iterator->linkprevious;
        iterator->linkprevious->linknext = iterator->linknext;
        //delete iterator;       // release memory of the node from the heap
        iterator = NULL;       // redirect iterator to NULL
        size--;                // enforcing postcondition
    }
}

template <class listdata>
void List<listdata>::advanceToIndex(int index)
{
    assert(size != 0);
    assert(0 < index);     // I think this is necessary
    assert(index <= size);
    pointIterator();
    for (int i = 0; i < index - 1; i++) advanceIterator();
    /*
     // This function would be more efficient if we enforce precondition: !offEnd()
     // We shall de it this way
     int numNodeAway = index - getIndex();
     if (numNodeAway > 0)
     {
     for (int i = 0; i < numNodeAway; i++) advanceIterator();
     }
     else if (numNodeAway < 0)
     {
     numNodeAway *= -1;
     for (int i = 0; i < numNodeAway; i++) reverseIterator();
     }
     return;
     */
}

/*************************************************************************/
/**Additional List Operations*/
template <class listdata>
void List<listdata>::print() const
{
    Node* temp = start;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->linknext;
    }
    cout << endl;
}

template <class listdata>
void List<listdata>::printNumberedList() const
{
    Node* temp = start;
    int lineIndex = 0;
    while(temp != NULL)
    {
        lineIndex++;
        cout << lineIndex << ": " << temp->data->name() << endl;
        temp = temp->linknext;
    }
    cout << endl;
}

template <class listdata>
void List<listdata>::reversePrint() const             // PUBLIC
{
    reversePrint(stop);
}

template <class listdata>
void List<listdata>::reversePrint(Node* node) const    // PRIVATE
{
    Node* temp = node;
    if (temp == NULL)
    {
        cout << " " << endl;         // base case
        return;
    }
    else
    {
        cout << temp->data << " ";
        reversePrint(temp->linkprevious);   // recursive steps
    }
}


template <class listdata>
bool List<listdata>::operator==(const List& list)
{
    if(size != list.size) return false;
    Node* temp1 = start;
    Node* temp2 = list.start;
    while(temp1 != NULL)
    {
        if(temp1->data != temp2->data) return false;
        temp1 = temp1->linknext;
        temp2 = temp2->linknext;
    }
    return true;
}



#endif /* LIST_H_ */


