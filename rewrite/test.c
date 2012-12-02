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


int main(int argc , char *argv[])
{
	FILE *fp;
	int status;
	char path[100];


	fp = popen("ifconfig | grep 'inet addr:192.' | awk '{split($2,a,\":\");print a[2]}'", "r");
	if (fp == NULL)
	    /* Handle error */;


	while (fgets(path, 100, fp) != NULL)
	    printf("%s", path);


	status = pclose(fp);
	
	return 0;
}
