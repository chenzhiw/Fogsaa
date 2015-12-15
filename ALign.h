#include "UtilityFunctions.h"
///////////////////////////////////////////////////////////////////////////////////
void Align(){
	int type_total = 1, new_type, new_score, np1, np2, new_lower, new_upper, next_lower, next_upper;
	int p, present, cpl;

	/* create the 2D matrix*/
	createMatrix();
	int P1 = 0, P2 = 0;


	/*Now with some initializations to the first cell of the matrix*/
	Cell[0][0].present_score = 0;
	Cell[0][0].type = -1;
	calculateScore(Cell[0][0].present_score, P1, P2, &(Cell[0][0].Min_score), &(Cell[0][0].Max_score));

	/*Setting optimal score to be the lowest possible score if all symbols just mismatched*/
	optimalScore = Cell[0][0].Min_score;


	/*Set the threshold of 30% similarity*/
	setThreshold();

	/*setting the capacity of the queue and initializing it*/
	init_queue();
	int branchend = 0;//a variable used to indicate whether the branch was totally expanded-->1 or not-->0

	gettimeofday(&start, NULL);

	//here we go
	if (m != 0 && n != 0){


		do{


			branchend = 1;
			while ((P1 <= m - 1) || (P2 <= n - 1)){

				present = Cell[P1][P2].present_score;

				if ((type_total == 1) || (type_total == 2) || (type_total == 4)){

					if (P1 <= m - 1 && P2 <= n - 1){
						if (S1[P1] == S2[P2])
							p = Mt;
						else
							p = Mst;
						//childtype1
						calculateScore(present + p, P1 + 1, P2 + 1, &a[0], &b[0]);
						//childtype2
						calculateScore(present + Gap, P1, P2 + 1, &a[1], &b[1]);
						//childtype3
						calculateScore(present + Gap, P1 + 1, P2, &a[2], &b[2]);

						sort();

						if (ch[0] == 1){
							// child would be of type 1
							new_type = 1;
							np1 = P1 + 1;
							np2 = P2 + 1;
							new_score = present + p;
						}
						else if (ch[0] == 2){
							//child would be of type 2
							new_type = 2;
							np1 = P1;
							np2 = P2 + 1;
							new_score = present + Gap;
						}
						else{
							new_type = 4;
							np1 = P1 + 1;
							np2 = P2;
							new_score = present + Gap;
						}

						insertQueue(P1, P2, new_type + ch[1], ch[1], a[1], b[1]);
					}

					else if (P1 <= m - 1){
						//only childtype3= 4 is possible
						new_type = 4;
						np1 = P1 + 1;
						np2 = P2;
						new_score = present + Gap;

					}
					else{
						new_type = 2;
						np1 = P1;
						np2 = P2 + 1;
						new_score = present + Gap;
					}
				}

				else if ((type_total == 3) || (type_total == 5) || (type_total == 6)){
					//this is the 2nd child

					if (new_type == 1)
					{
						//2nd child is of childtype1
						np1 = P1 + 1;
						np2 = P2 + 1;

						if (S1[P1] == S2[P2])
							p = Mt;
						else
							p = Mst;
						new_score = present + p;
						if (7 - type_total == 2)
							calculateScore(present + Gap, P1, P2 + 1, &next_lower, &next_upper);
						else if (7 - type_total == 4)
							calculateScore(present + Gap, P1 + 1, P2, &next_lower, &next_upper);

						insertQueue(P1, P2, 7, 7 - type_total, next_lower, next_upper);
					}

					else if (new_type == 2)
					{
						//2nd child is of type2

						np1 = P1;
						np2 = P2 + 1;
						new_score = present + Gap;
						if (7 - type_total == 1){
							if (S1[P1] == S2[P2])
								p = Mt;
							else
								p = Mst;
							calculateScore(present + p, P1 + 1, P2 + 1, &next_lower, &next_upper);
						}
						else if (7 - type_total == 4)
							calculateScore(present + Gap, P1 + 1, P2, &next_lower, &next_upper);
						insertQueue(P1, P2, 7, 7 - type_total, next_lower, next_upper);
					}
					else{
						//2nd child is of type=4
						np1 = P1 + 1;
						np2 = P2;
						new_score = present + Gap;

						if (7 - type_total == 1){
							if (S1[P1] == S2[P2])
								p = Mt;
							else
								p = Mst;
							calculateScore(present + p, P1 + 1, P2 + 1, &next_lower, &next_upper);
						}
						else if (7 - type_total == 2)
							calculateScore(present + Gap, P1, P2 + 1, &next_lower, &next_upper);
						insertQueue(P1, P2, 7, 7 - type_total, next_lower, next_upper);


					}



				}

				else if (type_total == 7){
					//this is the 3rd child
					if (new_type == 1){
						np1 = P1 + 1;
						np2 = P2 + 1;

						if (S1[P1] == S2[P2])
							p = Mt;
						else
							p = Mst;
						new_score = present + p;

					}
					else if (new_type == 2){
						np1 = P1;
						np2 = P2 + 1;
						new_score = present + Gap;

					}
					else{
						np1 = P1 + 1;
						np2 = P2;
						new_score = present + Gap;
					}
					//no node to be inserted in the queue

				}

				if (Cell[np1][np2].type <= 4 && Cell[np1][np2].present_score >= new_score &&Cell[np1][np2].written == 1)
				{//skip the path is the already expanded node is better
					branchend = 0;


					break;

				}
				else {
					//set the cell

					calculateScore(new_score, np1, np2, &new_lower, &new_upper);
					Cell[np1][np2].present_score = new_score;
					Cell[np1][np2].Min_score = new_lower;
					Cell[np1][np2].Max_score = new_upper;
					Cell[np1][np2].type = new_type;
					Cell[np1][np2].written = 1;

				}

				P1 = np1;
				P2 = np2;
				type_total = 1;

				if (Cell[np1][np2].Max_score < optimalScore){
					//prune the current branch
					branchend = 0;
					break;
				}
				expanded++;

			}
			//end while

			if (Cell[P1][P2].present_score > optimalScore && branchend == 1)
			{
				optimalScore = Cell[P1][P2].present_score;
				/*set the current path as the optimal path*/
				optimalx = P1;
				optimaly = P2;

			}


			/*pop the topmost node on the priority queue (with the biggest Max_Score */
			if (maxPointer != -1)
			{
				P1 = q[maxPointer]->p1;
				P2 = q[maxPointer]->p2;

				type_total = q[maxPointer]->type_up_tonext;
				new_lower = q[maxPointer]->chMin_score;
				new_upper = maxPointer + Cell[0][0].Min_score;
				new_type = q[maxPointer]->chtype;
				deleteQueue();
			}
			//check if the two sequences have below 30% similarity
			//if yes,terminate with approximate alignment & score
		if(checkThreshold(P1, P2, new_upper))
		{
			approximate=1;
			break;
		}
			
		} while (optimalScore<new_upper);
		//while the max_score of the top most node on the queue is higher than the optimalScore so far
	
		calculateElapsedtime();
		constructAligned(optimalx, optimaly);


	}
}
/////////////////////////////////////////////////////////////////////////////
