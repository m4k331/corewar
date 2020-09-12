/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_messages.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:23:42 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:23:45 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_MESSAGES_H
# define VM_MESSAGES_H

# define MSG_PLAYER_PRESENTATION0 "Player %d, weighting %d bytes ,"
# define MSG_PLAYER_PRESENTATION1 " \"%s\" (\"%s\")!\n"
# define ERR_ADDR "Error: can't connect to %s:%s\n"
# define CODE_ERR_ADDR 1000
# define ERR_COMMAND "Error: no such command %s\n"
# define CODE_ERR_COMMAND 999
# define ERR_MANY_ARGS "Error: command has too many args:\n\t\t\t\"%s\"\n"
# define CODE_ERR_MANY_ARGS 1
# define ERR_NOT_ENOUGH_ARGS0 "Error: need more args for command:\n\t\t%s\n"
# define ERR_NOT_ENOUGH_ARGS1 "Enter \"help\" for help message\n"
# define CODE_ERR_NOT_ENOUGH_ARGS 2
# define ERR_ALRDY_CNTD "Error: the server is already connected to %s:%s\n"
# define CD_ERR_ALRDY_CNTD 3
# define MSG_HELP0 "List of commands:\n"
# define MSG_HELP1 "\t\thelp (h)\t\t\t- show this help message\n"
# define MSG_HELP2 "\t\thelp_log (hl)\t\t\t- show log levels\n"
# define MSG_HELP3 "\t\tconnect <address> <port>\t- connect to server\n"
# define MSG_HELP4 "\t\treconnect <address> <port>\t- disconnect from current "
# define MSG_HELP5 "server and connect to another one\n"
# define MSG_HELP6 "\t\tdisconnect\t\t\t- disconnect from current server\n"
# define MSG_HELP7 "\t\tstop (exit)\t\t\t- stop and exit server\n"
# define MSG_HELP8 "\t\twklog <idworker> <loglevel>\t- stop and exit server\n"
# define CODE_MSG_HELP 0
# define ERR_YET_NO_WORKERS "Error: has no workers yet, needed to connect\n"
# define CODE_ERR_YET_NO_WORKERS 5
# define ERR_NO_SUCH_WORKER0 "Error: no worker with id %{rb}d."
# define ERR_NO_SUCH_WORKER1 "Enter number from 1 to %d\n"
# define CODE_ERR_NO_SUCH_WORKER 6
# define MSG_TO_CONNECT0 "Welcome to Online mode of corewar\n"
# define MSG_TO_CONNECT1 "Please, use \"connect\" command to connect to a "
# define MSG_TO_CONNECT2 "server or\nuse \"help\" command to get help info\n"
# define MSG_HELP_LOG0 "\t\t Log Level\tMessage\n"
# define MSG_HELP_LOG1 "\t\t\t 1 - show lives\n"
# define MSG_HELP_LOG2 "\t\t\t 2 - show current cycle\n"
# define MSG_HELP_LOG3 "\t\t\t 4 - show operations\n"
# define MSG_HELP_LOG4 "\t\t\t 8 - show deaths\n"
# define MSG_HELP_LOG5 "\t\t\t16 - show movements\n"
# define MSG_HELP_LOG6 "\t\t\t32 - show map\n"
# define CODE_MSG_HELP_LOG 0
# define MSG_NO_ARGS0 "\t==================================================="
# define MSG_NO_ARGS1 "=========\n"
# define MSG_NO_ARGS2 "\tHello, it is corewar game engine.\n"
# define MSG_NO_ARGS3 "\tThere are two modes of using this engine:\n"
# define MSG_NO_ARGS4 "\t1. Online mode: used with flag --server of -s\n"
# define MSG_NO_ARGS5 "\t\tfor help in Online mode type help in game console\n"
# define MSG_NO_ARGS6 "\t2. Offline mode: used without server flag.\n"
# define MSG_NO_ARGS7 "\t\tPossible options for Offline mode are:\n"
# define MSG_NO_ARGS8 "\t\t -dump <cycle_number> - shows map on defined cycle\n"
# define MSG_NO_ARGS9 "\t\t\t\t\tand exit program.\n"
# define MSG_NO_ARGS10 "\t\t -n <num> <champ_file> - set champ position\n"
# define MSG_NO_ARGS11 "\t\t --log or -l <log_level> - set logging level\n"
# define MSG_NO_ARGS12 "\t================================================"
# define MSG_NO_ARGS13 "============\n"
# define MSG_WORKER_LOG_SET "Success: worker %d has log status %d\n"
# define CODE_ERR_WRONG_ADDR_OR_PORT 6
# define ERR_WRONG_ADDR_OR_PORT "Error: entered address or port is not valid\n"
# define ERR_CONNECTION "Error: can't get data from provided address\n"
# define CODE_ERR_CONNECTION 7
# define ERR_NO_WK_ID "Error: worker id contains not only numbers\n"
# define CODE_ERR_NO_WK_ID 8
# define ERR_NOLOGMODE "Error: no log mode. Use help or h for help\n"
# define CD_ER_NOLOGMODE 9
# define MSG_SOCK_SUCCESS_CLOSED "Success: socket %d for %s:%s is closed\n"
# define ERR_SOCK_CLOSED "Failed:can't close socket %d for %s:%s is closed\n"
# define ERR_SOCK_DISCONNECT "Error: app is not connected\n"
# define CODE_ERR_SOCK_DISCONNECT 10
# define ERR_WRONG_HANDSHAKE "Error: server has wrong handshake message\n"
# define CODE_ERR_WRONG_HANDSHAKE 11
# define ERR_WRONG_MSG_HANDSHAKE "Error: wrong type of handshake message\n"
# define CODE_ERR_WRONG_MSG_HANDSHAKE 12
# define ERR_HNDSHK_KEY "Error: wrong magic key in handshake message\n"
# define CD_ERR_HNDSHK_KEY 13
# define MSG_STATUS_SERVER "Server connected to %s:%s\n"
# define ERR_SZ_HNDSHK "Error: wrong size of welcome message\n"
# define CD_ERR_SZ_HNDSHK 14
# define ERR_CANT_SEND_HANDSHAKE "Error: can't send handshake message\n"
# define CODE_ERR_CANT_SEND_HANDSHAKE 15
# define ERR_NOT_HNDSHK "Error: not a handshake\n"
# define CD_ERR_NOT_HNDSHK 16
# define ERR_PARSE_MSG_WRONG_MAGIC "Error: champ file has wrong magic header\n"
# define CODE_ERR_PARSE_MSG_WRONG_MAGIC 17
# define ERR_PARSE_MSG_NO_NULL_NAME "Error champ file: no null after name\n"
# define CODE_ERR_PARSE_MSG_NO_NULL_NAME 18
# define ERR_PRS_BIG_SIZE "Error: wrong champ file - code size is too big\n"
# define CD_ERR_PRS_BIG_SIZE 19
# define ERR_PARSE_MSG_NO_NULL_COM "Error champ file: no null after comment\n"
# define CODE_ERR_PARSE_MSG_NO_NULL_COM 20
# define ER_MO_CHMPS "Error: too many champions\n"
# define CD_ER_MO_CHMPS 21
# define ERR_SOCK_RECV "Error: %d is not enough data\n"
# define MSG_SOCK_RECV "Receive  %d bytes from %s:%s\n"
# define CD_ER_WRONG_SOCKET_HEADER_MSG 22
# define ER_PROC_PARSE_GAME "Error: error in game parsing process\n"
# define CD_ER_PROC_PARSE_GAME 23

#endif
