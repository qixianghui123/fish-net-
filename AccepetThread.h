#ifndef ACCEPT_THREAD_H_
#define ACCEPT_THREAD_H_

#include "BaseServer.h"
#include "ClientManager.h"
#include "Thread.h"

#include <iostream>

using namespace std;

class AcceptThread:public Thread
{
				public:
								void run()
								{
												cout << "accept thread start" << endl;
												BaseServer server_t;
												server_t.InitServer();
								}
};
#endif
