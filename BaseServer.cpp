#include "BaseServer.h"
#include "BaseSocket.h"
#include "ClientManager.h"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int BaseServer::Create()
{
				m_fd = socket(AF_INET, SOCK_STREAM, 0);
				return m_fd;
}

int BaseServer::Bind()
{
				sockaddr_in mAddr;
				mAddr.sin_family = AF_INET;
				mAddr.sin_port = htons(1999);
				mAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
				socklen_t len = sizeof(struct sockaddr);
				return bind(m_fd, (struct sockaddr *)&mAddr, len);
}

int BaseServer::Listen()
{
				return listen(m_fd, 1024);
}

int BaseServer::InitServer()
{
				if(Create() == -1)
				{
								cout << "create socket error" << endl;
								return -1;
				}
				if(Bind() == -1)
				{
								cout << "bind socket error" << endl;
								return -1;
				}
				if(Listen() == -1)
				{
								cout << "listen socket error" << endl;
								return -1;
				}
				//while(1)
				//{
								struct ev_loop *loop=ev_default_loop(0);
								struct ev_io socket_accept;
								ev_io_init(&socket_accept, AcceptCallBack, m_fd, EV_READ);
								ev_io_start(loop, &socket_accept);
								ev_run(loop, 0);
								cout << "accept thread runing" << endl;
				//}
}

void BaseServer::AcceptCallBack(struct ev_loop* loop, struct ev_io* watcher, int events)//accept callback function
{
				if(EV_ERROR & events)
				{
								return;
				}
				struct sockaddr_in clientAddr;
				bzero(&clientAddr, sizeof(sockaddr_in));
				socklen_t addrLen = sizeof(sockaddr_in);

				struct ev_io* clientWatcher = new ev_io();
				if (NULL==clientWatcher)
				{
								return;
				}
				int clientSock = accept(watcher->fd, (struct sockaddr*)&clientAddr, &addrLen);
				if (clientSock<0)
				{
								delete clientWatcher;
								return;
				}
				int nReUse = 1;
				setsockopt(clientSock, SOL_SOCKET, SO_LINGER, (void *)&nReUse, sizeof(nReUse));
				BaseSocket::SetNonBlock(clientSock);
				BaseSocket *pClient = new BaseSocket(clientSock, clientWatcher, loop);

				int iClientQueueSize = ClientManager::GetInstance()->GetClientQueueSize();
				if( iClientQueueSize >= 1024 )
				{
								cout << "queue is full------------------------------------" << endl;
								//pClient->doSendAcceptQueueFull();
								ev_io_stop(loop, clientWatcher);
								if(pClient)
								{
												delete pClient;
								}
								return;
				}
				else
				{
								pClient->SetSocketStatus(accept_over);
								ClientManager::GetInstance()->Insert(pClient);
				}

				ev_io_init(clientWatcher, ClientCallBack, clientSock, EV_READ);
				ev_io_start(loop, clientWatcher);
}

void BaseServer::ClientCallBack(struct ev_loop* loop, struct ev_io* watcher, int evevts)//read call back function
{
				BaseSocket *pClient = ClientManager::GetInstance()->FindSocket(watcher->fd);
				if(NULL == pClient)
				{
								return;
				}       
				else
				{
								pClient->SetSocketStatus(wait_read);
				} 		
}
