#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool cyclic(int a, int b);



int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            // printf("Ranks[%d] is: %d\n", rank, i);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        preferences[i][i] = 0; // pref of a cand vs themselves = 0
        for(int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            //printf("preferences [%d (i)][%d (j)] is: %d\n", ranks[i], ranks[j],preferences[ranks[i]][ranks[j]] );
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair movedPairs[MAX * (MAX - 1) / 2];
    int i_th_diff_score, j_th_diff_score;

    for(int i = 0; i < candidate_count; i++)
    {
         //victory score of the i'th pair
        i_th_diff_score = preferences[pairs[i].winner][pairs[i].loser];

        for(int j = i + 1; j < candidate_count; j++)
        {
            //victory score of the j'th pair
            j_th_diff_score = preferences[pairs[j].winner][pairs[j].loser];


            if(i_th_diff_score < j_th_diff_score)
            {
                //put smaller to movedPairs
                movedPairs[i].winner = pairs[i].winner;
                movedPairs[i].loser = pairs[i].loser;

                //put bigger in smaller's place within pairs
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                //put back smaller in pairs after bigger
                pairs[j].winner = movedPairs[i].winner;
                pairs[j].loser = movedPairs[i].loser;
            }

        }

    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        // ask the bool noCycle(int a, int b) whether locking this pair
        // wouldn't create a cycle
        // if it wouldn't, go ahead and lock this pair
        if (noCycle(pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    bool wins;
    int winner;

    for (int i = 0; i < candidate_count; i++)
    {
        wins = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                wins = false;
            }
        }

        if (wins == true)
        {
            winner = i;
        }
    }

    printf("%s\n", candidates[winner]);

    return;
}

//  a (who's the winner) = charl ; b (who's the loser) = alice

bool noCycle(int a, int b)
{
    if (a == b)
    {
        return false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // if there was a pair with the curent winner being it loser 
        // and the pair was locked before
        // and a certain "i" being its winner
        if (locked[i][a] == true)
        {
            // check if the winner "i" of that previously
            // locked pair is the same as the current pair's loser
            if (cyclic(i, b) == false)
            {
                // if so, there's a cycle. Don't lock & move on
                return false;
            }
        }
    }
    // else if the current winner was not a loser before,
    // tell void lock_pairs(void) function that there will be no cycle
    // and that it can go ahead and lock this pair
    return true;
}