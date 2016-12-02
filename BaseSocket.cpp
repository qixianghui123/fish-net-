#include "BaseSocket.h"

#include <fcntl.h>
#include <iostream>

using namespace std;

BaseSocket::BaseSocket(int client_fd, struct ev_io* watcher, struct ev_loop* loop)
{
				m_client_fd = client_fd;
				m_client_fd_status = new_status;
				m_watcher = watcher;
				m_loop = loop;
				m_time = time(NULL);
}

BaseSocket::~BaseSocket()
{
				ev_io_stop(m_loop, m_watcher);
				if(m_watcher)
				{
								cout << "delete watcher" << endl;
								delete m_watcher;
				}
				CloseSocket();
}

int BaseSocket::GetSocket()
{
				return m_client_fd;
}

time_t BaseSocket::GetSocketTime()
{
				return m_time;
}

int BaseSocket::ReadBuf(char *buf, int &len)
{
				return recv(m_client_fd, buf, len, 0);
}

int BaseSocket::SendBuf(char *buf, int &len)
{
				return send(m_client_fd, buf, len, 0);
}

void BaseSocket::SetSocketStatus(int status)
{
				m_client_fd_status = status;
}

int BaseSocket::GetSocketStatus()
{
				return m_client_fd_status;
}

void BaseSocket::CloseSocket()
{
				close(m_client_fd);
}

bool BaseSocket::SetNonBlock(int &sock) 
{
				int opts = fcntl(sock , F_GETFL);
				if( -1 == opts ) 
				{
								return false;
				}
				opts = opts | O_NONBLOCK;
				if( fcntl(sock , F_SETFL , opts) < 0 ) 
				{
								return false;
				}
				return true;
}

string BaseSocket::GetClientKey() 
{
				char sKey[1024];
				sprintf(sKey,"JY%08X",m_client_fd);
				return string(sKey);
}

