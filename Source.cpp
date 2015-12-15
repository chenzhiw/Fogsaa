/*
* Source.cpp
*
*  Created on: Dec 5, 2015
*      Author: Hanaa Mohamed
*/




#include"Align.h"

//////////////////////////////////////////////////////////////////////////////
int main(){
	/*
	* reading the two sequences that should be aligned
	* */

	cin >> S1 >> S2;

	/*
	* call the function that aligns the two sequences
	* */

	Align();
	cout << "\nOptimal ALignment\n";
	cout << optimal1 << endl << optimal2<<endl;
	cout << "Total no. of nodes expanded : " << expanded << endl;
}
