#include <cstring>
#include <iostream>
#include <limits.h>
#include<bits/stdc++.h>
#include "dynprog.h"

using namespace std;



/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char* X, char* Y, char** P, int** H, int n, int m){
	int p1, p2, p3;
	for(int i=0;i<=n;i++)
	{
		H[i][0] = P[i][0] = 0;
	}
	for(int j=0;j<=m;j++)
	{
		H[0][j] = P[0][j] = 0;
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			if(X[i-1]==Y[j-1]){
				p1= H[i-1][j-1] + 2;
			}
			else{
				p1= H[i-1][j-1] - 1;
			}
			p2 = H[i-1][j] - 1;
			p3 = H[i][j-1] - 1;
			H[i][j] =std::max(p1,std::max(p2, p3));
			if(H[i][j] == p1){
				P[i][j] = '\\';
			}
			else if(H[i][j] == p2){
				P[i][j] = '|';
			}
			else{
				P[i][j] = '-';
			}
		}
	}

}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char* X, char* Y, char** P, int** H, int n, int m){
  int p1, p2, p3,q;
  if(n > 0 && m > 0) {
  if(X[n-1]==Y[m-1]){
    p1 = memoized_SW_AUX(X, Y, P, H, n-1, m-1) + 2;
  }
  else{
     p1 = memoized_SW_AUX(X, Y, P, H, n-1, m-1) - 1;

  }

  p2 = memoized_SW_AUX(X, Y, P, H, n-1, m) - 1;
  p3 = memoized_SW_AUX(X, Y, P, H, n, m-1) - 1;
  q = std::max(p1,std::max(p2, p3));
  if(q == p1){
    P[n][m] = '\\';
  }
  else if(q == p2){
    P[n][m] = '|';
  }
  else{
    P[n][m] = '-';
  }
  H[n][m] = q;


}
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW_AUX(char* X, char* Y, char** P, int** H, int n, int m){
  if(H[n][m] == INT_MIN) {
      	 memoized_SW(X, Y, P, H, n, m);
        }

        return H[n][m];

}

/*
 * Print X'
 */
void print_Seq_Align_X(char* X, char** P, int n, int m){
	if(n> 0 && m > 0) {
	if(P[n][m] =='\\'){
		print_Seq_Align_X(X, P, n-1, m-1);
		std::cout<< X[n-1];

	}
	else{
		if(P[n][m] == '-'){
			print_Seq_Align_X(X, P, n, m-1);
			std::cout<< '-';
		}

	else{
		print_Seq_Align_X(X, P, n-1, m);
		std::cout<< X[n-1];

	}
}
}

}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int n, int m){
	if(n> 0 && m > 0) {
	if(P[n][m] =='\\'){
		print_Seq_Align_Y(Y, P, n-1, m-1);
		std::cout<< Y[m-1];

	}
	else{
		if(P[n][m] == '|'){
			print_Seq_Align_Y(Y, P, n-1, m);
			std::cout<< '-';
		}

	else{
		print_Seq_Align_Y(Y, P, n, m-1);
		std::cout<< Y[m-1];

	}
}
}
}
