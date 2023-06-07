#include <bits/stdc++.h>

// We will make a multidimensional linked llist to strore the statistics of a cricket world cup.
// One dimension will contain  the number of runs scored by the batsman in all the matches he faced. Note that this may not be a fixed number as he may have been dropped
// Second dimension will contain the runs scored by each batsman in the match.

using namespace std;

struct Score
{
   int run;
   string name;
   int MatchID;
   Score* nextBatsman;
   Score* nextMatch;

   Score(int runs, int match, string batsman_name) // This constructor is used to initialize any general node of the multilist
   {
       run = runs;
       MatchID = match;
       name = batsman_name;
       nextBatsman = NULL;
       nextMatch = NULL;
   }

   Score(int match)   // This constructor is used to initialize the header node which will contain the match name
   {
      run = -1;
      MatchID = match;
      name = "";
       nextBatsman = NULL;
       nextMatch = NULL;
   }

   Score(string batsman_name) // This constructor is used to initialize the header node which will contain the name of the batsman
   {
     run = -1;
     MatchID = -1;
     name = batsman_name;
      nextBatsman = NULL;
       nextMatch = NULL;
   }

};

class World_Cup
{
    private:
    Score* batsman_header[10];
    Score* match_header[10];

    public:
    
    World_Cup(int* matches, string* batsman_names)
    {
          for (int i = 0;i < 10; i++)
          {
            batsman_header[i] = new Score(*(batsman_names+i));
            match_header[i] = new Score(*(matches+i));
          }
    }

    int insertNode(int run_scored, int matchID, string batsman)
{
    Score* header1 = nullptr;
    Score* header2 = nullptr;

    // Find the corresponding batsman and match headers
    for (int j = 0; j < 10; j++)
    {
        if (batsman_header[j]->name == batsman) header1 = batsman_header[j];
        if (match_header[j]->MatchID == matchID) header2 = match_header[j];
    }

    // If either header is not found, return an error code
    if (header1 == nullptr || header2 == nullptr) {
        return -1; // or use an appropriate error code
    }

    // Create a new node
    Score* newNode = new Score(run_scored, matchID, batsman);

    // Insert the new node in the batsman linked list
    Score* prev_match_Node = header1;
    Score* current_match_Node = header1->nextMatch;

    while (current_match_Node != nullptr && current_match_Node->MatchID < matchID) {
        prev_match_Node = current_match_Node ;
        current_match_Node = current_match_Node ->nextMatch;
    }
    prev_match_Node->nextMatch = newNode;
    newNode->nextMatch = current_match_Node ;

    // Insert the new node in the match linked list
    Score* previousBatsmanNode = header2;
    Score* currentBatsmanNode = header2->nextBatsman;
    while (currentBatsmanNode != nullptr && currentBatsmanNode->name.compare(batsman) < 0) {
        previousBatsmanNode = currentBatsmanNode;
        currentBatsmanNode = currentBatsmanNode->nextBatsman;
    }
    previousBatsmanNode->nextBatsman = newNode;
    newNode->nextBatsman = currentBatsmanNode;

    return 0; // or use a success status code
}

 void print()
 {
    for(int i = 0; i < 10; i++)
    {
        Score* head = batsman_header[i]->nextMatch;
        while( head != NULL)
        {
            cout<<head->name<<" "<<head->MatchID<<" "<<head->run<<endl;
            head = head->nextMatch;
        }

    }
 }
};

int main()
{
    int matches[] = {3,6,8,10,15,18,22,25,27,30};
    string batsman[] = {"Dhoni","Gabbar","Gill","Hitman","Iyer","Jaddu","Kishan","Kohli","Pant","SKY"};

    World_Cup twenty_eighteen(matches, batsman);
    
    twenty_eighteen.insertNode(102, 9, "SKY");
    twenty_eighteen.insertNode(102, 10, "SKY");
    twenty_eighteen.insertNode(82, 15, "Kohli");
    twenty_eighteen.print();
    
    
    return 0;
}