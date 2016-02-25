#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
int comments = 2;

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

void LCSpair( string a, string b )
{
	if( comments == 2 ) printf( "strings: %s, %s \n", a.c_str(), b.c_str() );
	int aLength, bLength, i, j;
	aLength = a.length();
	bLength = b.length();
	if( comments == 2 ) printf( "Lengths: %d, %d \n", aLength, bLength );
	int c[aLength+1][bLength+1];
	for( i = 0 ; i <= aLength ; i++ ) c[i][0] = 0;
	for( i = 0 ; i <= bLength ; i++ ) c[0][i] = 0;
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
		LCSpair( list[k], list[k+1] );
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
