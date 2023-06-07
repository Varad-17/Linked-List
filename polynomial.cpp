// We will now make an implementation for polynomials using Linked Lists

#include <bits/stdc++.h>

using namespace std;

struct node // This is the node of the list. Each node contains the power of the variable(exp) and the coefficient of the power term.
{
    int exp;
    int coeff;
    node *next;
    node *previous;

    node(int e, int c)
    {
        exp = e;
        coeff = c;
        next = NULL;
        previous = NULL;
    }

    node()
    {
        exp = 0;
        coeff = 0;
        next = NULL;
        previous = NULL;
    }
};

class polynomial
{
private:
    node *head;

public:
    int degree;

    polynomial() // Constructor for intializing the linked list
    {
        degree = 0;
        head = new node();
    }

    ~polynomial() // Destructor for deallocating the dynamic memory
    {
        // Iterate through the list and deallocate memory for each node
        node *current = head;
        while (current != nullptr)
        {
            node *next = current->next;
            delete current;
            current = next;
        }
    }

    // We will assume that the polynomial is written in the form where terms are arranged such that the lower order terms are at the start of the list
    // i.e ascending order of the powers

    void insert_node(int power, int coefficient) // Function for adding any new term in the polynomial of degree power
    {
        node* current;
        node* back;
        node* forward;
        current = head;
        int  check = (current->next != NULL) ? (current->next)->exp : 0;
        while (check < power && current->next != NULL)
        {
            current = current->next;
            check = (current->next != NULL) ? (current->next)->exp : 0;
        }
        back = current;
        forward = current->next;
        node *new_node;
        new_node = new node(power, coefficient);
        new_node->next = forward;
        new_node->previous = back;
        back->next = new_node;
        if(forward != NULL) forward->previous = new_node;

        degree = (forward != NULL) ? degree : power;
    }

    void print_poly() // Function for printing the complete Polynomial
    {
        node *temp = head;
        cout << "Our polynomial is" << endl;
        while (temp->next != NULL)
        {
            temp = temp->next;
            cout << temp->coeff << "x^" << temp->exp << "+ ";
        }
        cout << endl;
    }

    void delete_node(int power) // Function for deleting any term in the polynomial of degree power
    {
        bool del = false;
        node *current = head;
        node *back;
        node *forward;
        while (current->next != NULL && del == false)
        {
            current = current->next;
            back = current->previous;
            forward = current->next;
            if (current->exp == power)
            {
                del = true;
                back->next = forward;
                if (forward != NULL)
                    forward->previous = back;
                delete current;
                degree = (forward != NULL) ? degree : back->exp;
            }
        }

        if (!del)
            cout << "The term cannot be found in the polynomial." << endl;
        else
            cout << "The term has been deleted successfully."<< endl;
    }

    void find_coefficient(int power) // Function for finding the coefficent of the given power
    {
        bool found = false;
        node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
            if (current->exp == power)
            {
                found = true;
                cout << "The coefficient of the term of power "<<power<<" is " << current->coeff << endl;
                break;
            }
        }
        if (!found)
            cout << "The term could not be found." << endl;
    }

    polynomial& operator = (const polynomial& obj2)
    {
       if (this != &obj2)
    {
        this->~polynomial();
        // Create a new linked list for the current object
        head = new node();
        degree = 0;

        // Copy the nodes from obj2 to the current object
        node* copy = obj2.head->next;
        while (copy != nullptr)
        {
            insert_node(copy->exp, copy->coeff);
            copy = copy->next;
        }
    }
    return *this;
    }

    friend polynomial operator +(const polynomial& obj1, const polynomial& obj2);


};

polynomial operator+(const polynomial& obj1, const polynomial& obj2)
{
    polynomial result;

    node* node1 = obj1.head->next;
    node* node2 = obj2.head->next;

    while(node1 != NULL || node2 != NULL)
    {
        int pow_1 = (node1 != NULL) ? node1->exp : -1;
        int pow_2 = (node2 != NULL) ? node2->exp : -1;
        if(pow_1 != -1 && pow_2 != -1)
        {
            if(pow_1 == pow_2)
            {
                if(node1->coeff+node2->coeff) result.insert_node(pow_1, node1->coeff+node2->coeff);
                node1 = node1->next;
                node2 = node2->next;
            }

            else
            {
                if(pow_1 < pow_2) 
                {
                    result.insert_node(pow_1,node1->coeff);
                    node1 = node1->next;
                }

                else
                {
                    result.insert_node(pow_2,node2->coeff);
                    node2 = node2->next;
                }
            }
        }

        else
        {
            if(pow_1 == -1 && pow_2 != -1)
            {
                result.insert_node(pow_2, node2->coeff);
                node2 = node2->next;
            }

            else if (pow_1 != -1 && pow_2 == -1)
            {
                  result.insert_node(pow_1,node1->coeff);
                  node1 = node1->next;
            }
        }
    }

    return result;
}

int main()
{
    polynomial poly1,poly2, operation;
    poly1.insert_node(67, 56);
    poly2.insert_node(42,53);
    poly1.insert_node(4,5);
    poly2.insert_node(4,-5);
    poly1.insert_node(3,7);
    poly2.insert_node(2,5);
    poly1.delete_node(65);
    poly1.delete_node(67);
    poly1.print_poly();
    poly2.print_poly();
    cout<<poly1.degree<<"  "<<poly2.degree<<endl;
    operation = (poly1 + poly2);
    operation.print_poly();
    cout<<operation.degree<<endl;
}
