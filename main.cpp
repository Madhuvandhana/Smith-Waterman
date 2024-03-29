#include <cstdio>
#include <cstdlib>

#include "dynprog.h"
#include "timer.h"
#include "random_generator.h"
#include <string>
#include<bits/stdc++.h>

int main(int argc, char* argv[])
{
	random_generator rg;
	timer t;
	int n, m, algo;
	int** H;
	char** P;		// possible values: 'l' for left, 'u' for up and 'd' for diagonal up left

	/*
	 * read the main arguments
	 */
	if (argc > 1)
	{
		n = atoi(argv[1]);
		n = (n < 1) ? 1 : n;
	}
	else
	{
		cout << "hw4: [n] [m] [algorithm]" << endl;
		cout << "[n]             	size of first string" << endl;
		cout << "[m]      			size of second string" << endl;
		cout << "[algorithm] 	    0: bottom-up SW" << endl;
		cout << " 			    	1: top-down SW" << endl;
		cout << endl;
		return 0;
	}
	if (argc > 2)
	{
		m = atoi(argv[2]);
		m = (m < 1) ? 1 : m;
	}
	else
		m=n;
	if (argc > 3)
		algo = atoi(argv[3]);
	else
		algo = 0;

	char* X;
	char* Y;

	//values used for question #4.
	// n=m=10;


	// string s = "caacbdacca";
	// n = s.size();
	// X = new char[s.size()+1];
	// s.copy(X, s.size()+1);
	// X[s.size()] = '\0';
	//
	// string s1 = "bccbcdccba";
	//
	// Y = new char[s1.size()+1];
	// m = s1.size();
	// s1.copy(Y, s1.size()+1);
	// Y[s1.size()] = '\0';


	random_generator::seed();

	X = rg.random_string_m(n, 4);
	Y = rg.random_string_m(m, 4);

	H = new int*[n+1];
	P = new char*[n+1];
	for(int i=0;i<=n;i++)
	{
		H[i] = new int[m+1];
		P[i] = new char[m+1];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++){
			H[i][j] = INT_MIN;
		}
	}

	if(algo==0)
		SW_bottomUp(X, Y, P, H, n, m);
	else if(algo==1)
		memoized_SW(X, Y, P, H, n, m);

	cout << endl;

	cout << "\nX = ";
	for(int i=0;i<n;i++)
		cout << X[i];

	cout << "\nX'= ";
	print_Seq_Align_X(X,P,n,m);

	cout << "\nY'= ";
	print_Seq_Align_Y(Y,P,n,m);

	cout << "\nY = ";
	for(int j=0;j<m;j++)
		cout << Y[j];

	cout << "\n-----------------";

	cout <<"\nM(n,m) = " << H[n][m] << endl;

	return 0;
}
