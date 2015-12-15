

#include"Variables.h"

////////////////////////////////////////////////////////////////////////
typedef struct queuenode{

	int p1, p2, chtype, type_up_tonext, chMin_score;

	queuenode* next;
}queue;
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
queue **q = NULL;

/////////////////////////////////////////////////////////////////////////
void insertQueue(int p1, int p2, int type_total, int next_type, int next_lower, int next_upper){


	int inserted = 0;

	int position = next_upper - Cell[0][0].Min_score;
	queue *p = NULL, *prev = NULL, *newnode = NULL;
	if ((position) >= 0){
		newnode = new queue;
		newnode->p1 = p1;
		newnode->p2 = p2;
		newnode->type_up_tonext = type_total;
		newnode->chMin_score = next_lower;
		newnode->chtype = next_type;

		if (maxPointer == -1)
		{
			q[position] = newnode;
			newnode->next = NULL;

			maxPointer = position;
		}
		else{


			if (q[position] == NULL){

				q[position] = newnode;
				newnode->next = NULL;
				if (position > maxPointer)
					maxPointer = position;
			}
			else{
				p = q[position];
				prev = NULL;
				while (p != NULL)
				{

					if (p->chMin_score <= Cell[p1][p2].Min_score)
					{
						if (prev == NULL){
							q[position] = newnode;
							newnode->next = p;
						}
						else{
							prev->next = newnode;
							newnode->next = p;
						}
						inserted = 1;
						break;
					}
					else{

						prev = p;
						p = p->next;
					}
				}

				if (inserted == 0)
				{
					// insert at the end
					prev->next = newnode;
					newnode->next = NULL;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////
void init_queue()
{

	int Capacity = Cell[0][0].Max_score - Cell[0][0].Min_score + 1;
	q = new queue*[Capacity];

	for (int i = 0; i<Capacity; i++)
		q[i] = NULL;

}
////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void deleteQueue(){
	queue * temp;
	if (maxPointer == -1)
		return;
	else
	{
		temp = q[maxPointer];
		q[maxPointer] = temp->next;
		delete temp;
		while (q[maxPointer] == NULL)  // this row is empty , point next row
			maxPointer--;
	}
}
