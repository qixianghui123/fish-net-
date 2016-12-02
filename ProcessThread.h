#ifndef PROCESS_THREAD_H_
#define PROCESS_THREAD_H_

#include "BaseServer.h"
#include "ClientManager.h"
#include "Thread.h"

#include <iostream>
#include <string.h>
using namespace std;

class ProcessThread:public Thread
{
				public:
								void run()
								{
												cout << "start process thread" << endl;
												ClientManager *m_pClientMngr = ClientManager::GetInstance();
												while(1)
												{
																map<string, BaseSocket*> vctClients;
																m_pClientMngr->GetClients(vctClients);
																if( vctClients.size()<= 0) 
																{
																				usleep(100);
																				continue;
																}
																cout << "find read map num is " << vctClients.size() << endl;
																map<string, BaseSocket*>::iterator it;
																for(it=vctClients.begin(); it!=vctClients.end(); it++)
																{
																				BaseSocket* &client = it->second;
																				char buf[128];
																				int len = 128;
																				client->ReadBuf(buf, len);
																				cout << "read buf is " << buf << endl;
																				int num = strlen(buf);
																				cout << "send num is " << client->SendBuf(buf, num) << endl;
																				m_pClientMngr->MoveToDestoryMap(client);
																				//delete client;
																}
												}
								}
};
#endif

