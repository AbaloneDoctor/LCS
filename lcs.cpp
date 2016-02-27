#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;
int comments = 3;

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
	for( i = 0 ; i <= aLength; i++ )
	{
		for( j = 0 ; j <= bLength; j++ )
		{
			if( comments == 2) printf("%d",cb.C[i][j]);
			if( comments == 2 && (j+1)%(bLength+1) == 0 ) printf("\n");
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
		if( comments == 2 ) printf( "D: b[%d][%d] \n", i, j );
		if( b[i][j] == 'D')
		{
			if( comments == 2 )printf( " word[i]: %c \n", word[i-1] );
			commonString = word[i-1] + commonString;

			i--;
			j--;
		}
		else if( b[i][j] == 'U' )
		{
			if( comments == 2 )printf( "U:\n", a[i] );
			i--;
		}
		else if( b[i][j] == 'L' )
		{
			if( comments == 2 )printf( "L:\n", a[i] );
			j--;
		}
	}
	printf( "%s\n", commonString.c_str() );
	return 0;
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
		k = k+2;
	}
}

struct stackEntry
{
	int i, j;
	int flag;
	char letter;

};

void printMatrix( char b[1000][1000] )
{

	if( comments == 2 ) printf( "Before Print\n" );
	for( int i = 0 ; i <= 11; i++ )
	{
		for( int j = 0 ; j <= 8; j++ )
		{
			printf("%c",b[i][j]);
			if(j%11 == 0)printf("\n");
		} 

	} 

}
void printAllLCS( int c[1000][1000], char b[1000][1000], string s1, string s2, int i, int j )
{
	if( comments == 3 ) printf("inside print allLCS \n");
	stack <stackEntry> substring;
	stack <stackEntry> buffer;
	/*stackEntry A;	
	A.i = 0;
	A.j = 0;
	A.letter = 'a';
	substring.push(A);
	printf( "c is: %c\n", substring.top().letter );
	*/
	int len = c[i][j];
	printf( "len: %d\n", len );
	char word[1000];
	strcpy( word,  s1.c_str() );
	string commonString;
	//while( i>0 && j>0 );
	/*	
	stackEntry Ai;
	Ai.i = i;
	Ai.j = j;
	Ai.letter = word[i];
	if( b[i][j] == 'D'  ) Ai.flag = 1;
	substring.push(Ai);
	*/
	stackEntry dummy;
	dummy.i=5;
	dummy.j=5;
	substring.push(dummy);
	//while( substring.size() != 0 )
	int y = 0;
	printMatrix(b);
	do
	{
		stackEntry A;
		A.i = i;
		A.j = j;
		/*
		stackEntry A;
		A.i = i;
		A.j = j;
		A.letter = word[i];
		*/
		if( comments == 3 ) printf( "c[%d][%d], val: %d\n", i,j,c[i][j] );
		if( comments == 3 && substring.size()>0 ) printf( "s1, s2: %c, %c\n", s1[i], s2[j] );
		//if( comments == 3 ) printf( "strlen s1: %d \n", strlen(s1.c_str()) );		
//printing of code
		if( substring.top().i == i && substring.top().j == j )
		{ 
			if( comments == 3 ) printf( "Current on visited node\n" );
			printf("top of stack: %c\n", substring.top().letter );
			//means this has been visited and you had just popped back to this
			//check U and L
			//if U and L are smaller, move back down previous
			//else i-- or j--
			if( c[i-1][j] >= c[i][j] && b[i-1][j]!='x') 
			{
				if( comments == 3 ) printf( "Go UP\n" );
				i--;
				//b[i][j] = 'x';
			}
			else if( c[i][j-1] > c[i][j] && b[i][j-1]!='x')
			{
				if( comments == 3 ) printf( "Go LEFT\n" );
				j--;
				//b[i][j] = 'x';
			}
			else 
			{

				if( comments == 3 ) printf( "All x'ed, going back one spot\n" );	
				substring.pop();
				i = substring.top().i;
				j = substring.top().j;
				printf("top i,j: %d, %d\n", i, j);

			}


		}		
				
		else if( c[i][j] == 0 )
		{

			if( comments == 3 ) printf( "End of path\n" );
			b[i][j] = 'x';
			printMatrix(b);
			printf("\n");
			printf("Currently at: %d, %d\n", i, j );
			//move back to previous spot
			//substring.push(A);
			stackEntry buff;			
			buff = substring.top();
			i = buff.i;
			j = buff.j;
			printf("Moved back to: %d, %d\n", i, j );

			
			
			//substring.push(A);
			
		/*
			printf("(");
			
			
			for( int k = 0 ; k < len ; k++ )
			//while( substring.size() > 0 )
			{
				stackEntry B;	
				//printf("segcheck1\n");			
				B = substring.top();
				//printf("segcheck2\n");			

				substring.pop();
				if( comments == 3 ) printf( "B.letter: %c\n", B.letter );
				if( B.flag == 1) printf( "<%d,%d>", B.i, B.j );			
				buffer.push(B);
				printf( "," );
				
			}
			
			printf(")\n");
			
		*/
		}
		//else if( b[i][j] == 'D'  )//&& c[i][j] != 0)
		else if ( s1[i-1] == s2[j-1] || b[i][j] == 'D')
		{
			printf("inside D: i,j; s1,s2 ; letter: %d, %d, %c, %c, %c\n", i,j,s1[i-1], s2[j-1], b[i][j]);
			A.flag = 1;
			b[i][j] = 'x';
			printMatrix(b);
			printf("\n");
			//if( comments == 3 )printf( " word[i]: %c \n", word[i-1] );
			if( comments == 3 && b[i-1][j] != 'x' )printf( "D:\n", s1[i] );
			commonString = word[i-1] + commonString;
		//	i--;	//switched to after
		//	j--;
			A.letter = word[i];
			if( comments == 3 ) printf("letter: %c, i,j: %d,%d\n", word[i], i, j);
			substring.push(A);
			i--;
			j--;
		
		}
		else if( b[i][j] == 'U'  )//&& c[i][j] != 0)
		{
			b[i][j] = 'x';
			printMatrix(b);
			printf("\n");
			if( comments == 3 && b[i-1][j] != 'x' )printf( "U:\n", s1[i] );
			//i--;
			A.letter = word[i];
			if( comments == 3 ) printf("letter: %c, i,j: %d,%d\n", word[i], i, j);
			substring.push(A);
			i--;
		}
		else if( b[i][j] == 'L'  )//&& c[i][j] != 0)
		{
			b[i][j] = 'x';
			printMatrix(b);
			printf("\n");
			if( comments == 3 && b[i-1][j] != 'x' )printf( "L:\n", s1[i] );
			//j--;
			A.letter = word[i];
			if( comments == 3 ) printf("letter: %c, i,j: %d,%d\n", word[i], i, j);
			substring.push(A);
			j--;
		}
		if( comments == 3 ) printf( "stack size: %i\n" , substring.size());
		//A.letter = word[i];
		//if( comments == 3 && c[i][j] != 0  ) printf("pushing\n");
		//if( c[i][j] != 0 )substring.push(A);
		//if( comments == 3 ) printf( "stack top letter: %c\n" , substring.top().letter );
		
	y++;
	} while ( substring.size()>1 );
	//while( substring.size() != 0 );
	//while( i>0 && j>0 ); 	//maybe change this to OR? so it'll continue iterating
	//while( i>0 || j>0 );
	printMatrix(b);
}


/*
char* allLCSR( int c[1000][1000], string a, string b, i, j )
{
	if ( i == 0 || j == 0 )
		return {""};
}
*/

//vector of struct
void allLCS( vector<string> list )
{
	int n = list.size()/2;
	int k = 0;
	for( int i = 0; i < n ; i++ )
	{
		struct CandB cb = LCSpair( list[k], list[k+1] );
		if( comments == 3 ) printf( "words: %s, %s \n", list[k].c_str(), list[k+1].c_str() );
		printAllLCS( cb.C, cb.B, list[k], list[k+1],list[k].length(), list[k+1].length()  );
		//allLCSR
		k = k+2;
	}
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
		if( comments == 3 || comments == 2 ) printf( "Calling part -all function\n" );
		allLCS( stringList );
	}
	else
	{
		printf( "Incorrect input\n" );
		exit(0);
	}
	return 0;
}
