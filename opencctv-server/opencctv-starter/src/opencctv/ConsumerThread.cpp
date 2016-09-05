
#include "ConsumerThread.hpp"

namespace opencctv {

ConsumerThread::ConsumerThread(unsigned int iStreamId, ImageMulticaster* pImageMulticaster) {
	ApplicationModel* pModel = ApplicationModel::getInstance();
	_pQueue = NULL;
	if(pModel->containsInternalQueue(iStreamId))
	{
		_pQueue = pModel->getInternalQueues()[iStreamId];
	}
	_pImageMulticaster = pImageMulticaster;
}

void ConsumerThread::operator ()()
{
	if(_pImageMulticaster)
	{
		opencctv::util::log::Loggers::getDefaultLogger()->info("Consumer Thread started.");
		_pImageMulticaster->start();
	}
	opencctv::util::log::Loggers::getDefaultLogger()->info("Consumer Thread stopped.");
}

ConsumerThread::~ConsumerThread(){
	std::cout << "Consumer destructure called." << std::endl;
}

} /* namespace opencctv */
