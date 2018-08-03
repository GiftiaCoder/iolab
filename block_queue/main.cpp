

#include <liblog.h>
#include <pthread.h>
#include <list>
#include <tuple>
#include <thread>

#include <unistd.h>

template<typename T>
class block_queue : public std::list<T>
{
public:
	block_queue() : 
		m_size(0),
		m_opsmut(PTHREAD_MUTEX_INITIALIZER), 
		m_takemut(PTHREAD_MUTEX_INITIALIZER)
	{
		//I("size: %d", m_size);
		// TODO
	}

	void put(T t)
	{
		pthread_mutex_lock(&m_opsmut);
		this->push_back(t);
		++m_size;
		pthread_mutex_unlock(&m_takemut);
		pthread_mutex_unlock(&m_opsmut);
	}

	T take()
	{
		pthread_mutex_lock(&m_opsmut);
		if (m_size <= 0)	
		{
			pthread_mutex_unlock(&m_opsmut);
			
			I("cannot get data, block");
			
			pthread_mutex_trylock(&m_takemut);
			pthread_mutex_lock(&m_takemut);
			
			I("data got, unblock");

			pthread_mutex_lock(&m_opsmut);
		}
	
		I("get value");

		--m_size;
		T t(this->front());
		this->pop_front();
		
		pthread_mutex_unlock(&m_opsmut);
		return t;
	}

private:
	int m_size;
	pthread_mutex_t m_opsmut;
	pthread_mutex_t m_takemut;
};

int main()
{
	I("begin");
	block_queue<int> bq;
	std::thread t([&](){
		int i = 0;
		while (true)
		{
			I("loop %d", ++i);
			I("take: %d", bq.take());
		}
	});
	int j = 0;
	while (true)
	{
		sleep(1);
		bq.put(++j);
		bq.put(++j);
		bq.put(++j);
	}
	t.join();
	//bind<int(*)(), const char *, const char *> b(main, "fuyuumi", "ai");
	//invoke(print, "fuyuumi", "ai");
	//std::tuple<const char *, int, double> t("fuyuumi ai", 0, 0.0);
	//I("%s", std::get<0>(t));
	return 0;
}

