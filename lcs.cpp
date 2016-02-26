#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
int comments = 0;

vector<string> createStringVector() //creates list of strings, with every 2 being a pair
{
	vector<string> tokens;
	char split = ' ';
	string num;
	getline( cin, num );
	int testNum = atoi( num.c_str() );
	if( comments == 1 ) cout<<"Number of test: "<<num<<endl; 

	for( int n = 0 ; n < testNum ; n++ )
	{
		string line, word;
		getline( cin, line ); //reads entire line from cin into line
		istringstream line2(line);	//changes line into sstream for next split
		int i = 0;
		if( cin.eof() == 1 ) 
		{
			if( comments == 1 ) cout<<"end"<<endl; 
			break;
		}
		while( i < 2 )
		{
			getline( line2, word, split );	//splits line into separate words
			tokens.push_back(word);
			if( comments == 1 ) cout<<word<<endl;
			if( comments == 1 ) cout<<strlen(word.c_str())<<endl;
			if( comments == 1 ) cout<<"loop inside"<<endl;
			i++;
		}
		if( comments == 1 ) cout<<"loop: "<<n+1<<endl;
	}
	return tokens;
}

//LCS PART 1

struct CandB
{
	int C[1000][1000];
	char B[1000][1000];
};

struct CandB LCSpair( string a, string b )
{


	if( comments == 2 ) printf( "strings: %s, %s \n", a.c_str(), b.c_str() );
	int aLength, bLength, i, j;
	struct CandB cb;
	aLength = a.length();
	bLength = b.length();

	if( comments == 2 ) printf( "Lengths: %d, %d \n", aLength, bLength );
	for( i = 0 ; i <= aLength ; i++ ) cb.C[i][0] = 0;
	for( i = 0 ; i <= bLength ; i++ ) cb.C[0][i] = 0;

	if( comments == 2 ) printf( "  " );
	if( comments == 2 ) for( j = 0 ; j <= bLength ; j++ ) printf( "%c", b[j] );
	if( comments == 2 ) printf( "\n" );
	for( i = 1 ; i <= aLength ; i++ )
	{
	

		if( comments == 2 ) printf ( "%c ", a[i-1] );
		for( j = 1 ; j <= bLength ; j++ )
		{
			//printf( "left vs up: %d, %d \n", cb.C[i-1][ j], cb.C[i-1][ j] );
			if( a[i-1] == b[j-1] )
			{
				if( comments == 2 ) printf( "D" );
				cb.C[i][j] = cb.C[i-1][j-1] + 1;
				//if( comments == 2 ) printf( "%d\n", cb.C[i][j]);		
				cb.B[i][j] = 'D';
			}
			else if( cb.C[i-1][ j] >= cb.C[i][ j-1] )
			{
				if( comments == 2 ) printf( "U" );	
				cb.C[i][j] = cb.C[i-1][j];
				//if( comments == 2 ) printf( "%d\n", cb.C[i][j]);		
				cb.B[i][j] = 'U';
			}
			else if( cb.C[i-1][ j] < cb.C[i][ j-1] )
			{
				if( comments == 2 ) printf( "L" );	
				cb.C[i][j] = cb.C[i][j-1];
				//if( comments == 2 ) printf( "%d\n", cb.C[i][j]);		
				cb.B[i][j] = 'L';
			}

			if( comments == 2 && j%bLength == 0 ) printf("\n");
		}

	}
	if( comments == 2 ) printf( "Before Print\n" );
	for( i = 1 ; i <= aLength; i++ )
	{
		for( j = 1 ; j <= bLength; j++ )
		{
			if( comments == 2) printf("%d",cb.C[i][j]);
			if( comments == 2 && j%bLength == 0 ) printf("\n");
		} 

	} 

	return cb;
}


int printLCS( int c[1000][1000], char b[1000][1000], string a, int i, int j )
{	
	int len = c[i][j];
	printf( "%d " , len);
	char word[1000];
	strcpy( word,  a.c_str() );
	if( comments == 2 ) printf( "word: %s\n", word );
	if( comments == 2 ) printf( "length: %d; \ni,j: %d, %d\n", c[i][j], i, j );
	string commonString;
	//for( int k = 0 ; k < len ; k ++ )
	while( i > 0 and j > 0 )
	{
		if( comments == 2 ) printf( "b[%d][%d] \n", i, j );
		if( b[i][j] == 'D')
		{
			if( comments == 2 )printf( "word[i]: %c \n", word[i-1] );
			commonString = word[i-1] + commonString;

			i--;
			j--;
		}
		else if( b[i][j] == 'U' )
		{
			if( comments == 2 )printf( "U\n", a[i] );
			i--;
		}
		else if( b[i][j] == 'L' )
		{
			if( comments == 2 )printf( "L\n", a[i] );
			j--;
		}
	}
	printf( "%s\n", commonString.c_str() );
}

//prints out length then longest common string
void LCS( vector<string> list )
{
	if( comments == 2 ) printf( "In LCS\n");
	if( comments == 2 ) printf( "length of list: %d\n", list.size() );
	int n = list.size()/2;
	if( comments == 2 ) printf( "n size: %d\n", n);
	int k = 0;	
	for( int i = 0 ; i < n ; i++ )
	{
		struct CandB cb = LCSpair( list[k], list[k+1] );
		if( comments == 2 ) printf( "list k, k+1, and lengths: %s, %s, %d, %d\n", list[k].c_str(), list[k+1].c_str(), list[k].length(), list[k+1].length() );
		if( comments == 2 ) printf( "Common string: \n" );		
		printLCS( cb.C, cb.B, list[k], list[k].length(), list[k+1].length() );
		if( comments == 2 ) printf( "\n" );		
		k=k+2;
	}
}




//vector of struct
void allLCS( vector<string> list ){
}



int main( int argc, char *argv[] )
{	
	int all = 0;
	if( comments == 1) printf( "%d\n", argc );
	//if( argc == 2 && strcmp( argv[1], "-all" ) == 0 ) { all = 1; if( comments == 1 ) printf("-all called\n");}
	//if( strcmp( argv[1], "-all" ) == 0 ) { all = 1; if( comments == 1 ) printf("-all called\n");}
	vector<string> stringList = createStringVector();
	if( all == 0 && argc == 1 )
	{
		LCS( stringList );		
	}	
	else if( argc == 2 && strcmp( argv[1], "-all" ) == 0 )
	{
		if( comments == 1 ) printf( "Calling part 2 function\n" );
		allLCS( stringList );
	}
	else
	{
		printf( "Incorrect input\n" );
		exit(0);
	}
	return 0;
}
