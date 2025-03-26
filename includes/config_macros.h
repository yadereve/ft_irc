#ifndef CONFIG_MACROS_H
#define CONFIG_MACROS_H

/******************************************
 *                                        *
 *                 MACROS                 *
 *                                        *
 ******************************************/

/* COMMANDS */

#define CAP 1
#define HELP 2
#define OPER 3
#define PING 4
#define QUIT 5
#define PASS 6
#define NICK 7
#define USER 8
#define WHOIS 9
#define JOIN 10
#define MODE 11
#define TOPIC 12
#define PART 13
#define PRIVMSG 14
#define INVITE 15
#define KICK 16

/* ERRORS */
#define OK 0;
#define ERROR_1 1;
#define ERROR_2 2;
#define ERROR_3 3;
#define ERROR_4 4;
#define ERROR_5 5;

/******************************************
 *                                        *
 *                INCLUDES                *
 *                                        *
 ******************************************/

#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <climits>
#include <cctype>
#include <iostream>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <vector>

#endif
