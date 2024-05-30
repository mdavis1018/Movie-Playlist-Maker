#ifndef QUEUE_CPP
#define QUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Templated linked list
// Note: Because the linked list is a templated class,
//       there is only ONE file (Queue.cpp)

// Templated node class
template <class T>
class Node
{
public:
   Node(const T &data);         // Constructor
   T &GetData();                // Gets data from node
   void SetData(const T &data); // Sets data in node
   Node<T> *GetNext();          // Gets next pointer
   void SetNext(Node<T> *next); // Sets next pointer
private:
   T m_data;
   Node<T> *m_next;
};

// Overloaded constructor for Node
template <class T>
Node<T>::Node(const T &data)
{
   m_data = data;
   m_next = NULL;
}

// Returns the data from a Node
template <class T>
T &Node<T>::GetData()
{
   return m_data;
}

// Sets the data in a Node
template <class T>
void Node<T>::SetData(const T &data)
{
   m_data = data;
}

// Gets the pointer to the next Node
template <class T>
Node<T> *Node<T>::GetNext()
{
   return m_next;
}

// Sets the next Node
template <class T>
void Node<T>::SetNext(Node<T> *next)
{
   m_next = next;
}

template <class T>
class Queue
{
public:
   // Name: Queue() Queue from a linked list - Default Constructor
   // Desc: Used to build a new linked queue (as a linked list)
   // Preconditions: None
   // Postconditions: Creates a new queue where m_head and m_tail
   //                 point to nullptr and m_size = 0
   Queue();
   // Name: ~Queue() - Destructor
   // Desc: Used to destruct a Queue
   // Preconditions: There is a Queue
   // Postconditions: Queue is deallocated (including dynamically allocated nodes)
   //                 Can just call Clear()
   ~Queue();
   // Name: Queue (Copy Constructor)
   // Preconditions: Creates a copy of existing Queue in separate memory
   //                address (deep copy)
   //                Requires one already existing Queue
   // Postconditions: Copy of existing Queue
   Queue(const Queue &);
   // Name: operator= (Overloaded Assignment Operator)
   // Preconditions: When two Queue objects exist, sets one to equal another
   //                Requires two Queue objects
   // Postconditions: When completed, you have two Queues in
   //                 separate memory addresses with the same
   //                 number of nodes with the same values in each node
   Queue<T> &operator=(Queue &);
   // Name: PushBack
   // Preconditions: Takes in data. Creates new node.
   //                Requires a Queue
   // Postconditions: Adds a new node to the end of the Queue.
   void PushBack(const T &);
   // Name: PopFront
   // Preconditions: Queue with at least one node.
   // Postconditions: Removes first node in the queue and
   //                 returns the data in the first node
   T PopFront();
   // Name: Display
   // Preconditions: Outputs the queue.
   // Postconditions: Displays the data in each node of queue
   // Required (used only for queue testing)
   void Display();
   // Name: Front
   // Preconditions: Requires a Queue with at least one node
   // Postconditions: Returns whatever data is pointed at by m_head -
   //                 Does NOT remove node
   T Front();
   // Name: IsEmpty
   // Preconditions: Requires a queue
   // Postconditions: Returns if the queue is empty.
   bool IsEmpty();
   // Name: GetSize
   // Preconditions: Requires a queue
   // Postconditions: Returns m_size
   int GetSize();
   // Name: Find()
   // Preconditions: Requires a queue
   // Postconditions: Iterates and if it finds the thing, returns index, else -1
   int Find(T);
   // Name: Clear
   // Preconditions: Requires a queue
   // Postconditions: Deallocates and removes all nodes in a queue. No memory leaks
   void Clear();
   // Name: At
   // Precondition: Existing Queue
   // Postcondition: Returns object from Queue at a specific location
   // Desc: Iterates to node x and returns data from Queue
   T &At(int x);
   // Name: Swap(int)
   // Preconditions: Requires a queue
   // Postconditions: Swaps the nodes at the index with the node prior to it.
   // Example: Swap(1) would swap the node 0 with node 1 so
   //          that node 1 would now be m_head
   // Desc: Swaps two nodes by updating the pointers (not just the value)
   // Hint: Think about the special cases! Implement before Sort
   void Swap(int);
   // Name: Sort()
   // Preconditions: Requires a queue with a minimum of 2 nodes
   //                (otherwise notifies user)
   // Postconditions: Sorts the Queue (may use overloaded < or >).
   // Desc: This is used to sort anything in the Queue assuming the
   //       < or > is overloaded
   //        Uses bubble sort and Swap function above.
   //        Ensure working with queue_test before rest of project.
   // Note: Allowed to use the break command in just this function if necessary
   void Sort();

private:
   Node<T> *m_head; // Node pointer for the head
   Node<T> *m_tail; // Node pointer for the tail
   int m_size;      // Number of nodes in queue
};

//**********Implement Queue Class Here***********
//**********All Functions Are Required Even If Not Used for Project**************
//**********No references to anything from Movie here*****************

// Default Constructor
template <class T>
Queue<T>::Queue() : m_head(nullptr), m_tail(nullptr), m_size(0)
{
   // Initially, the head and tail are set to nullptr indicating an empty queue,
   // and the size is set to 0.
}

// Destructor
template <class T>
Queue<T>::~Queue()
{
   Clear(); // Calls the Clear method to delete all nodes and free memory.
}

// Copy Constructor
template <class T>
Queue<T>::Queue(const Queue &copy) : m_head(nullptr), m_tail(nullptr), m_size(0)
{
   // Start with an empty queue

   Node<T> *current = copy.m_head; // Start from the head of the queue to be copied
   while (current != nullptr)
   {
      PushBack(current->GetData()); // Copy each element to the new queue
      current = current->GetNext(); // Move to the next node in the original queue
   }
}

// Overloaded Assignment Operator
template <class T>
Queue<T> &Queue<T>::operator=(Queue<T> &other)
{
   if (this != &other)
   {                                   // Check for self-assignment
      Clear();                         // Clear the existing content of this queue
      Node<T> *current = other.m_head; // Start with the head of the other queue
      while (current != nullptr)
      {
         PushBack(current->GetData()); // Copy each element to this queue
         current = current->GetNext(); // Move to the next node
      }
   }
   return *this; // Return a reference to this instance
}

// PushBack
template <class T>
void Queue<T>::PushBack(const T &data)
{
   Node<T> *newNode = new Node<T>(data); // Create a new node with the given data.
   if (m_tail == nullptr)
   {
      // If the queue is currently empty, set both head and tail to the new node.
      m_head = m_tail = newNode;
   }
   else
   {
      // Otherwise, append the new node to the end of the queue and update the tail pointer.
      m_tail->SetNext(newNode);
      m_tail = newNode;
   }
   m_size++; // Increment the size of the queue.
}

// PopFront
template <class T>
T Queue<T>::PopFront()
{
   if (IsEmpty())
   {
      // If the queue is empty, print a message and exit the function.
      cout << "Empty" << endl;
      return T(); // Return default-initialized object of type T.
   }
   Node<T> *temp = m_head;     // Temporary pointer to the head node.
   T data = m_head->GetData(); // Retrieve data from the head node.
   m_head = m_head->GetNext(); // Move the head pointer to the next node.
   delete temp;                // Delete the old head node.
   if (m_head == nullptr)
   {
      // If the list is now empty, set the tail to nullptr as well.
      m_tail = nullptr;
   }
   m_size--;    // Decrement the size of the queue.
   return data; // Return the data of the removed node.
}

// Display
template <class T>
void Queue<T>::Display()
{
   Node<T> *current = m_head; // Start from the head of the queue.
   while (current != nullptr)
   {
      // Print the data of each node followed by a space.
      cout << current->GetData() << " ";
      current = current->GetNext(); // Move to the next node.
   }
   cout << endl; // Print a newline after all elements.
}

// Front
template <class T>
T Queue<T>::Front()
{
   if (IsEmpty())
   {
      // If the queue is empty, print an error message and return default-initialized object.
      cout << "Error: Queue is empty." << endl;
      return T();
   }
   return m_head->GetData(); // Return the data of the head node.
}

// Is empty function
template <class T>
bool Queue<T>::IsEmpty()
{
   // Returns true if the head pointer is null, indicating the queue is empty
   return m_head == nullptr;
}

// GetSize
template <class T>
int Queue<T>::GetSize()
{
   return m_size; // returns number of nodes
}

// Clear
template <class T>
void Queue<T>::Clear()
{
   // Continuously remove elements from the front of the queue until it is empty.
   while (!IsEmpty())
   {
      PopFront(); // Each PopFront call removes the head node and deallocates its memory.
   }
}

// At
template <class T>
T &Queue<T>::At(int x)
{
   // Check if the index is out of range to prevent accessing nodes that don't exist.
   if (x < 0 || x >= m_size)
   {
      cout << "Index out of range." << endl;
   }
   Node<T> *current = m_head;  // Start traversing from the head of the queue.
   for (int i = 0; i < x; i++) // Navigate to the node at the specified index.
   {
      current = current->GetNext(); // Move to the next node in the list.

      // checks to catch any error in list structure
      if (current == nullptr)
      {
         cout << "Unexpected null pointer in At function." << endl;
      }
   }
   return current->GetData(); // Return a reference to the data stored at the node found at index x.
}

template <class T>
void Queue<T>::Swap(int index)
{
   Node<T> *target = m_head; // points to start of list
   Node<T> *prev1 = m_head;  // helper pointer to manage node just before targer
   Node<T> *prev2 = m_head;  // two nodes before target helper
   int count = 0;            // used to track the position in the list

   if (index == 0)
   {
      cout << "Error: Cannot swap first node" << endl;
      return;
   }

   // Special case for swapping the head with the next node
   if (index == 1)
   {
      // if head and next node aren't empty
      if (m_head != nullptr && m_head->GetNext() != nullptr)
      {
         Node<T> *second = m_head->GetNext(); // node pointing to the second node
         m_head->SetNext(second->GetNext());  // point m_head's pointer to third node
         second->SetNext(m_head);             // point second to m_head
         m_head = second;                     // make second the new head
      }
      return;
   }

   // special handling when the last node needs to be swapped
   if (index == m_size - 1)
   {
      while (target != m_tail)
      {
         prev2 = prev1;              // two nodes behind target
         prev1 = target;             // one node behind target
         target = target->GetNext(); // next node after target
      }
      // rearrange nodes
      target->SetNext(prev1);  // point last node to second to last
      prev2->SetNext(target);  // point the third last to last
      prev1->SetNext(nullptr); // make the second last now the last
      m_tail = prev1;          // update tail
      return;
   }

   // Navigate to the correct position for swapping
   while (count != index)
   {
      // move through list using same method as above
      prev2 = prev1;
      prev1 = target;
      target = target->GetNext();
      count++;
   }

   // Swap the nodes by rearranging their pointers
   prev1->SetNext(target->GetNext());
   target->SetNext(prev1);
   prev2->SetNext(target);
}

// Sort
template <class T>
void Queue<T>::Sort()
{
   // check to ensure atleast two nodes
   if (m_size < 2)
   {
      cout << "Error: Cannot sort less than 2 nodes" << endl;
      return; // exit function no sorting necessary
   }

   bool swapped; // bool flag to check if a swap has occured
   do
   {
      swapped = false; // initialize swapped to false

      // loop through queue from second element to last
      for (int i = 1; i < m_size; i++)
      {
         Node<T> *prev = m_head; // start with the head node

         // node jsut before the one to potentially swap
         for (int j = 0; j < i - 1; j++)
         {
            prev = prev->GetNext();
         }

         Node<T> *current = prev->GetNext(); // node at i

         // if the previus node is greater than the current node they must be swapped
         if (prev->GetData() > current->GetData())
         {
            Swap(i);
            swapped = true; // indicate a swap has occured
         }
      }
   } while (swapped); // continue sorting until no swaps are needed (list sorted)
}

// find function
template <class T>
int Queue<T>::Find(T value)
{
   Node<T> *current = m_head; // Start with the head of the queue.
   int index = 0;

   // Loop through each node in the queue until end
   while (current != nullptr)
   {
      // If the data in the current node matches the value being searched,
      if (current->GetData() == value)
      {
         return index; // return the index of that node.
      }
      current = current->GetNext(); // Move to the next node in the queue.
      index++;                      // Increment the index for each node visited.
   }
   return -1; // Not found
}

#endif
