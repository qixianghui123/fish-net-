#ifndef PROCESS_THREAD_H_
#define PROCESS_THREAD_H_

#include "BaseServer.h"
#include "ClientManager.h"
#include "Thread.h"

#include <iostream>

using namespace std;

class ProcessThread:public Thread
{
				public:
								void run()
								{
												ClientManager *m_pClientMngr = ClientManager::GetInstance();
												vector<BaseSocket *> vctClients;
												while(1)
												{
																int count = m_pClientMngr->GetClients(vctClients);
																if( count <= 0 ) 
																{
																				usleep(1000);
																				continue;
																}
																size_t i;
																for(i=0; i<count; i++)
																{
																				BaseSocket *client = vctClients[i];
																				if(client)
																				{
																								client->SetSocketStatus(read_now);
																								char buf[128];
																								int len = 128;
																								client->ReadBuf(buf, len);
																								cout << "read buf is " << buf << endl;
																								client->SetSocketStatus(read_over);
																								client->SetSocketStatus(wait_quit);
																				}
																}
												}
								}
};
#endif

