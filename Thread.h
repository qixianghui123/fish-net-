#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
class Thread
{
				public:
								Thread();
								virtual ~Thread();
								virtual void run()=0;
								void create();
								void join();
								void cancel();
				private:
								static void *thread_routine(void *arg);
				private:
								pthread_t *thread_id;
								long long m_thread_id;
};
#endif
