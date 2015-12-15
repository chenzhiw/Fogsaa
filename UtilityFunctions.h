#include "PriorityQueue.h"
#include<algorithm>
#include<sys/time.h>
/////////////////////////////////////////////////////////////////////////////

void createMatrix()
{
	m = S1.size();
	n = S2.size();

	Cell = new node*[m + 1];

	for (int i = 0; i <= m; i++){

		Cell[i] = new node[n + 1];

	}

}
//////////////////////////////////////////////////////////////////////////////
void calculateElapsedtime(){
			gettimeofday(&end, NULL);

    	seconds  = end.tv_sec  - start.tv_sec;
    	useconds = end.tv_usec - start.tv_usec;

 	   mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
}

//////////////////////////////////////////////////////////////////////////////
void calculateScore(int Prs, int P1, int P2, int *Min, int *Max)
{

	int x1 = m - P1;
	int x2 = n - P2;

	if (x1 <= x2){

		*Min = Prs + x1*Mst + (x2 - x1)*Gap;
		*Max = Prs + x1*Mt + (x2 - x1)*Gap;

	}
	else{

		*Min = Prs + x2*Mst + (x1 - x2)*Gap;
		*Max = Prs + x2*Mt + (x1 - x2)*Gap;
	}


}
//////////////////////////////////////////////////////////////////////////////////
void sort()
{
	int i, j;
	ch[0] = 1;
	ch[1] = 2;
	ch[2] = 4;
	for (i = 0; i<2; i++)
	{
		for (j = 0; j<2 - i; j++)
		{
			if ((a[j]<a[j + 1]) || ((a[j] == a[j + 1]) && (b[j]<b[j + 1])))
			{
				//swap
				
				swap(a[j],a[j+1]);

				swap(ch[j],ch[j+1]);

			
				swap(b[j],b[j+1]);
			}

		}
	}
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void constructAligned(int x, int y){

	cout<<"\nSize of the 1st Seq : "<<m<<endl;
	cout<<"Size of the 2nd Seq : "<<n<<endl;
	cout<<"Elapsed time : "<<mtime<<" milliseconds\n";
	
	if(!(x==0&&y==0)&&approximate==0){
		while (!(x == 0 && y == 0))//where Cell[0][0] is the root node
		{
			if (Cell[x][y].type == 1){
				//match/mismatch
				optimal1 = S1[--x] + optimal1;
				optimal2 = S2[--y] + optimal2;

			}
			else if (Cell[x][y].type == 2){
				//a gap in Seq1
				optimal1 = '-' + optimal1;
				optimal2 = S2[--y] + optimal2;

			}
			else if (Cell[x][y].type == 4){
				//a gap in Seq2
				optimal1 = S1[--x] + optimal1;
				optimal2 = '-' + optimal2;

			}
			else if (Cell[x][y].type == -1)
				return; //this case won't happen but lets' be cautious for now,it will only happen at (0,0) which we won't already get to
		}

	
	cout << "\nOptimal ALignment\n";
	cout << optimal1 << endl << optimal2<<endl;
	cout << "Total no. of nodes expanded : " << expanded << endl;
	}
	else if(approximate==1||(x==0&&y==0)){

		cout << "\nApproximate alignment\nThe two Sequences have less than 30"<<'%'<<" Similarity\n";
		optimal1 = S1;
		optimal2 = S2;
		while (optimal1.size() < optimal2.size())
			optimal1 += '-';
	
		while (optimal2.size() < optimal1.size())
			optimal2 += '-';

		cout << optimal1 << endl << optimal2 << endl;
	}
	
}
//////////////////////////////////////////////////////////////////////////////////
bool checkThreshold(int p1, int p2, int new_upper){
	int cpl;
	if (p1 > p2)
		cpl = p1;
	else
		cpl = p2;
	if (((cpl > 70 * l / 100) && (optimalScore < Threshold)) || (new_upper < Threshold)||(optimalx==0&&optimaly==0)){

	
		return true;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////////
void setThreshold()
{
	l = max(m, n);
	s = min(m, n);

	int th = l * 30 / 100;

	Threshold = th*Mt + (s - th)*Mst + (l - s)*Gap;

}
