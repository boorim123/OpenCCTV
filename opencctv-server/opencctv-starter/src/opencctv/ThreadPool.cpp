/*
 * ThreadPool.cpp
 *
 *  Created on: Sep 1, 2016
 *      Author: nhutumdai
 */

#include "ThreadPool.h"

namespace opencctv {

ThreadPool* ThreadPool::_pThreadPool = NULL; // Static variable has to be written again.
ThreadPool::ThreadPool() {
	// TODO Auto-generated constructor stub
}


ThreadPool* ThreadPool::getInstance() {
	if (!_pThreadPool) {
		_pThreadPool = new ThreadPool();
	}
	return _pThreadPool;
}


void ThreadPool::interruptAll(){
	consumerInterruptAll();
	producerInterruptAll();
}


void ThreadPool::joinAll(){
	consumerThreadJoinAll();
	producerThreadJoinAll();
	resultRouterThreadJoinAll();
}



void ThreadPool::consumerThreadJoinAll(){

	std::map<unsigned int, boost::thread*>::iterator it;

	for (it = _mConsumerThreadManagers.begin(); it != _mConsumerThreadManagers.end(); ++it) {

		boost::thread* pConsumerThread = it->second;

		//if (pConsumerThread->joinable()){
		//	pConsumerThread->join();
		//}

		if(pConsumerThread){
		   	pConsumerThread->detach();
//native_handle()
		   // boost::this_thread::
			delete pConsumerThread;
			pConsumerThread = NULL;
			opencctv::util::log::Loggers::getDefaultLogger()->error("Delete Consumer");
		}

	}
}

void ThreadPool::producerThreadJoinAll(){

	std::map<unsigned int, boost::thread*>::iterator it;

	for (it = _mProducerThreadManagers.begin(); it != _mProducerThreadManagers.end(); ++it) {

		boost::thread* pProducerThread = it->second;

		//if (pProducerThread->joinable()){
		//	pProducerThread->join();
		//}

		if(pProducerThread){
			pProducerThread->detach();
			delete pProducerThread;
			pProducerThread = NULL;
			opencctv::util::log::Loggers::getDefaultLogger()->error("Delete Producer");
		}
	}
}


void ThreadPool::resultRouterThreadJoinAll(){

	std::map<unsigned int, boost::thread*>::iterator it;

	for (it = _mResultRouterThreadManagers.begin(); it != _mResultRouterThreadManagers.end(); ++it) {

		boost::thread* pResultRouterTherad = it->second;

		if(pResultRouterTherad){
			delete pResultRouterTherad;
			pResultRouterTherad = NULL;
			opencctv::util::log::Loggers::getDefaultLogger()->error("Delete Result router ");
		}
	}
}



 void ThreadPool::consumerInterruptAll(){

	 opencctv::util::log::Loggers::getDefaultLogger()->error("Consumer interruption size: " + _mConsumerThreadManagers.size());

	std::map<unsigned int, boost::thread*>::iterator it;

	for (it = _mConsumerThreadManagers.begin(); it != _mConsumerThreadManagers.end(); ++it) {

		boost::thread* pConsumerThread = it->second;

		if (!pConsumerThread->interruption_requested()){
			pConsumerThread->interrupt();
		}
	}
}



void ThreadPool::producerInterruptAll(){

	opencctv::util::log::Loggers::getDefaultLogger()->error("Producer interruption size: " + _mProducerThreadManagers.size());

	std::map<unsigned int, boost::thread*>::iterator it;

	for (it = _mProducerThreadManagers.begin(); it != _mProducerThreadManagers.end(); ++it) {

		boost::thread* pProducerThread = it->second;

		if (!pProducerThread->interruption_requested()){
			pProducerThread->interrupt();
		}
	}
}



/*void ThreadPool::setResultRouterThreadManagers(unsigned int analyticId, const std::map<unsigned int, ::ResultRouterThread*>& resultRouterThreadManagers) {
	//_mResultRouterThreadManagers[analyticId] = resultRouterThreadManagers;
}*/

void ThreadPool::setConsumerThreadManagers( unsigned int analyticId, boost::thread* pConsumerThread) {
	_mConsumerThreadManagers[analyticId] = pConsumerThread;
}

void ThreadPool::setProducerThreadManagers(unsigned int analyticId, boost::thread* pProducerThread) {
	_mProducerThreadManagers[analyticId] = pProducerThread;
}

void ThreadPool::setResultRouterThreadManagers(unsigned int analyticId, boost::thread* pResulterThread){
	_mResultRouterThreadManagers[analyticId] = pResulterThread;
}


ThreadPool::~ThreadPool() {
	// TODO Auto-generated destructor stub
}


} /* namespace  */
