# include<bits/stdc++.h>

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

    void delete_node(int pos) //Function for deleting an element present at position pos
    {
        if (len < pos) cout<<"Warning : There aren't enough element in the list. "<<endl;
        else 
        {
            node *prev = head;
            node *succeed = head->next;
            for(int k = 1; k < pos; k++)
            {
                prev = prev->next;
                succeed = prev->next;
            }
            prev->next = succeed->next;
            len--;
            cout<<"Node is deleted successfully at position "<<pos<<endl;
        }
    }

    void find_kth(int k) // Function for Finding the kth element of the list
    {
      
      if(len < k) cout<<"Warning : There aren't enough element in the list. "<<endl;

      else 
      {
        node *temp = head;
        for (int l = 0; l < k;l++)
        {
            temp = temp->next;
        }
        cout<<"The element at position "<<k<<" of the list is thus "<<temp->value<<endl;
      }
    }

    void find_k(int k) // Function for finding the element of value k in the list and printing the position of the element 
    {                  // Note that we are only returning the first instance found of the given element
        bool found = false;
        node *current = head;
        int pos = 0;
        for(int iter = 1; iter < len;iter++)
        {
            current = current->next;
            if (current->value == k)
            {
                found = true;
                pos = iter;
                break;  
            }
        }
        if (!found) cout<<"Element not found in the list."<<endl;
        else cout<<"The element "<<k<<" is at position "<<pos<<endl;
    }

};

int main()
{
  linked_list mylist;
  mylist.insert_node(5, 1);
  mylist.insert_node(6,1);
  mylist.insert_node(8,2);
  mylist.print_list();
  mylist.find_kth(2);
  mylist.delete_node(1);
  mylist.find_k(8);
  mylist.print_list();

  return 0;
}