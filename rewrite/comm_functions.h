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
 
 void getLocalIP(char* ip);
 void sendMessage(char* message, char* ip, int port);
 void receiveMessage(char* message, int messageSize, char*ip, int port);
