#include "Thread.h"

#include <iostream>

using namespace std;

Thread::Thread()
{
				thread_id = new pthread_t;
				create();
}

Thread::~Thread()
{
				if(thread_id != NULL)
				{
								delete thread_id;
				}
				thread_id = NULL;
}

void Thread::create()
{
				int rs = pthread_create(thread_id, NULL, thread_routine, (void*)this);
				m_thread_id = *thread_id;
}

void Thread::cancel()
{
				pthread_cancel(m_thread_id);
}

void Thread::join()
{
				pthread_join(m_thread_id, NULL);
}

void* Thread::thread_routine(void *arg)
{
				Thread *thr = (Thread *)arg;
				thr->run();
				return NULL;
}
