/*here we will define all the data structures and global variables we will need for our algorithm*/


#include<iostream>
#include<string>

using namespace std;
///////////////////////////////////////////////////////////////////////////
struct node{

	int present_score, Min_score, Max_score, type, written;
	/*we have 3 types of children and a root(=> -1)*/
	//child1=> at which a match/mismatch occured =>1
	//child2=> a gap was inserted  in S1	=>2
	//child3=> a gap was inserted in S2	=>4
	/******************************/
};


/////////////////////////////////////////////////////////////////////

int maxPointer = -1;//the pointer to the node with maximum Score on top of the priority queue
int approximate = 0;
int expanded = 0; //number of nodes expanded
int Threshold = 0;
int optimalx = 0, optimaly = 0;
int a[3], b[3], ch[3];
//these 3 arrays will be used as temporary storage for the min & max score of the 3 children
//of the current node being processed and its type in order to help us decide which node we
//should expand

node** Cell = NULL;//pointer to the 2D matrix that will be created
int m = 0, n = 0, l, s;//m=size of S1,n=size of S2
//l=>the length of the larger seq  and s=>the length of the smaller sequence 

///////////////////////////////////////////
//Defining our scoring scheme//
int Mst = -1, Mt = 1, Gap = -1;
//Mst=>Mismatch=-1
//Mt=>Match=1
//Gap=>-1
/////////////////////////////////////////

int optimalScore;

string S1, S2, optimal1 = "", optimal2 = "";
//S1=>Sequence1
//S2=>Sequence2
//optimal1=>optimal seq1
//optimal2=>optimal seq2
