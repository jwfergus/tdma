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
 #ifndef COMM_FUNCTIONS_H
 #define COMM_FUNCTIONS_H

 void getLocalIP(char* ip);
 void sendMessage(char* message, char* ip, int port);
 char *receiveMessage(char* ip, int port);
 void countMessagesReceived(char* ip, int port, unsigned int countNeeded);

 #endif
