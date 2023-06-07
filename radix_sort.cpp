#include<bits/stdc++.h>

// Here we will try to build a radix sort algorithm, which uses linked lists to store the numbers in the same bucket
using namespace std;
class node
{
    public :
    int value; // defining a variable for holding the value 
    node* next; // defining a pointer for holding the pointer to the next element

    node() // constructor for initializing the header node 
    {
        value = 0;
        next = NULL;
    }

    node(int v) // constructor for initializing rest of the nodes
    {
        value = v;
        next = NULL;
    }

};

class linked_list
{

    public :
    node *head; // Variable with the value of the address of the header node
    long long len; // Variable giving the value of the current length of the list 

    linked_list() // Constructor for initializing the linked list
    {
        head = new node;
        len = 1;
    }
    
    ~linked_list() // Destructor for deallocating the dynamic memory used
     {
        // Iterate through the list and deallocate memory for each node
        node* current = head;
        while (current != nullptr) {
            node* next = current->next;
            delete current;
            current = next;
        }
     }

    void insert_node(int val, int pos) // Function for inserting a node at position pos and storing integer value val
    {   
        if (len < pos) cout<<"Warning : There aren't enough element in the list. "<<endl;
        else 
        {   
            if (pos == -1)  pos = len;
            node *prev = head;
            node *add = new node(val);
            node *succeed = head->next;
            for(int i = 0;i < pos-1; i++) 
            {
                prev = prev->next;
                succeed = prev->next;
            }
            prev->next = add;
            add->next = succeed;
            len++;
            cout<<"Node is added successfully at position "<<pos<<" with value "<<val<<endl;
        }
    }

    void print_list() // Function for printing the complete list
    {
        node *temp = head;
      for (int j = 1; j < len; j++)
      {
        temp = temp->next;
        cout<<temp->value<<" ";
      }
      cout<<endl;
    }

};

void radixSort(int* array_, int size, int digits, int bucket_size)
{   
     int list[size] = {0};
     for(int i = 0; i <size; i++)
     {
         list[i] = *(array_+i);
     }
  for (int i = 0; i < digits;i++) 
  {
    linked_list bucket[bucket_size];
    for (int j = 0; j < size; j++)
    {
        int qu = list[j], mod = 0;
       for(int iter = 0; iter <= i; iter++)
       {
         mod = qu % bucket_size;
         qu /= bucket_size;
       }
       bucket[mod].insert_node(list[j], -1); // giving position as -1 will add it to the end of the list
    }
    int cnt = 0;
    for (int k = 0; k < bucket_size; k++)
    {
        node* current = bucket[k].head->next;
        while(current !=    NULL)
        {
            list[cnt] = current->value;
            current = current->next;
            cnt++;
        }
    }
  }
  for(int i = 0; i <size; i++)
     {
        *(array_+i) = list[i];
     }
} 

int main()
{
 int array[] = {0,1,512,343,64,125,216,27,8,729};
 radixSort(array, 10, 3, 10);
 for (size_t i = 0; i < 10; i++)
 {
   cout<<array[i]<<" ";
 }
 
return 0;
}

