#include "AccepetThread.h"
#include "ProcessThread.h"
#include <iostream>

using namespace std;
int main()
{
				Thread *accept_thread = new AcceptThread;
				Thread *process_thread = new ProcessThread;
				cout << "create thread ok\n";
				while(1)
				{}
}
