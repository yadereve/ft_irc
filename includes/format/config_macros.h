#ifndef CONFIG_MACROS_H
#define CONFIG_MACROS_H

/******************************************
 *                                        *
 *                  ENUM                  *
 *                                        *
 ******************************************/

enum commands
{
	CAP = 1,
	HELP,
	PING,
	QUIT,
	PASS,
	NICK,
	USER,
	WHOIS,
	JOIN,
	MODE,
	TOPIC,
	PART,
	PRIVMSG,
	INVITE,
	KICK,
};

enum success
{
	PASSWORD_SUCCESS = 100,
	NICKNAME_SUCCESS,
	USERNAME_SUCCESS,
	PONG,
	// debug messages
	CHANNEL_CREATED,
	JOINED_CHANNEL,
	CHANNEL_OP,
	LEAVE_CHANNEL,
};

enum errors
{
	ERR_NO_SUCH_NICK = 401,
	ERR_NO_SUCH_CHANNEL = 403,
	ERR_CANNOT_SEND_TO_CHAN = 404,
	ERR_TOO_MANY_CHANNELS = 405,
	ERR_UNKNOWN_COMMAND = 421,
	ERR_NO_NICKNAME_GIVEN = 431,
	ERR_ERRONEUS_NICKNAME = 432,
	ERR_NICKNAME_IN_USE = 433,
	ERR_USER_NOT_IN_CHANNEL = 441,
	ERR_NOT_ON_CHANNEL = 442,
	ERR_USER_ON_CHANNEL = 443,
	ERR_NEED_MORE_PARAMS = 461,
	ERR_ALREADY_REGISTERED = 462,
	ERR_NOT_AUTHENTICATED = 463,
	ERR_PASSWD_MIS_MATCH = 464,
	ERR_INVALID_PASSWORD = 465,
	ERR_CHANNEL_IS_FULL = 471,
	ERR_UNKNOWN_MODE = 472,
	ERR_INVITE_ONLY_CHAN = 473,
	ERR_BAD_CHANNEL_KEY = 475,
	ERR_BAD_CHAN_MASK = 476,
	ERR_CHAN_OP_PRIV_NEEDED = 482,
	ERR_NO_OPER_HOST = 491,
	ERR_USERS_DONT_MATCH = 502,

	ERR_USER_ALREADY_INVITED = 900,
	ERR_INVALID_INPUT = 901,
	ERR_EMPTY_INPUT = 902,
	ERR_ERRONEUS_USER = 903,
	ERR_ERRONEUS_REAL_NAME = 904,
};

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
