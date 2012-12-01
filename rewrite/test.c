/**
 * @file
 * @author  Joshua Ferguson <jwfergus@asu.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * Copyright Joshua W. Ferguson 2012
 *
 * @section DESCRIPTION
 *
 * Initial implementation of MEL command server
 */



#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;


vector< vector<string> > getAppIPList(const char *filename)
{
	vector< vector<string> > listOfIPs;
	string line;
	ifstream myfile (filename);
	if (myfile.is_open())
	{
		int appID = 0;
		while ( myfile.good() && !myfile.eof() )
		{	int nodeID = 0;
			listOfIPs.push_back (vector< string> (0) );
			getline (myfile,line);
			istringstream lineAsStringStream( line );
			while (!lineAsStringStream.eof())
			{
				string field;
				getline( lineAsStringStream, field, ' ' ); 
				listOfIPs[appID].push_back (field);
				nodeID++;
			}
			appID++;
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 
	listOfIPs.pop_back();
	
	/**
	*
	*	print the list of application IPs  
	*
	**/
	cout << "\n*****Printing App List*****\n" << endl;
	
	for (vector< vector<string> >::size_type i = 0; i < listOfIPs.size(); i++)
	{
		cout << "Application " << i << " IPs:"<< endl;
		for (vector<string>::size_type j = 0; j < listOfIPs[i].size(); j++)
		{
			cout << listOfIPs[i][j] << "; ";
		}
		cout << "\n" << endl;
	}
	
	return listOfIPs;

}

int main(int argc , char *argv[])
{
	vector< vector<string> > ApplicationList = getAppIPList("test.txt");
	
	return 0;
}
