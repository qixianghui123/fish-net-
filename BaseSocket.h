#ifndef BASE_SOCKET_H_
#define BASE_SOCKET_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include "ev.h"

using namespace std;

enum socket_status
{
				accept_over,
				wait_read,
				read_now,
				read_over,
				wait_quit
};

class BaseSocket
{
				public:
								BaseSocket(int client_fd = -1, struct ev_io* watcher = NULL, struct ev_loop* loop = NULL);
								~BaseSocket();
								int ReadBuf(char *buf, int &len);
								int SendBuf(char *buf, int &len);
								void SetSocketStatus(int status);
								int  GetSocketStatus();
								void CloseSocket();
								int GetSocket();
								time_t GetSocketTime();
								string GetClientKey();
								static bool SetNonBlock(int &sock);

				private:
								int									m_client_fd;
								int									m_client_fd_status;
								struct  ev_io*			m_watcher;
								struct  ev_loop*		m_loop;
								time_t							m_time;

};
#endif
