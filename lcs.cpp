#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
int comments = 1;

vector<string> createStringVector()
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




int main( int argc, char *argv[] )
{	
	vector<string> stringList = createStringVector();	
	return 0;
}
