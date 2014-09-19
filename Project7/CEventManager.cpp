#include "CEventManager.hpp"

CEventManager::CEventManager() {

}

CEventManager::~CEventManager() {

}

void CEventManager::subscribe(IEventable *eventable) {
	if (hasEventable(eventable)) {
		clog << "[INFO] Eventable already subscribed." << endl;
	}
	else {
		subscribed.push_back(eventable);
	}
}

void CEventManager::unsubscribe(IEventable *eventable) {
	list<IEventable *>::iterator it = subscribed.begin();
	for (; it != subscribed.end(); ++it) {
		if (*it == eventable) {
			subscribed.erase(it);
			return;
		}
	}
}

bool CEventManager::hasEventable(IEventable *eventable) {
	list<IEventable *>::iterator it = subscribed.begin();
	for (; it != subscribed.end(); ++it) {
		if (*it == eventable) {
			return true;
		}
	}
	return false;
}

void CEventManager::notify(IEvent *e) {
	list<IEventable *>::iterator it = subscribed.begin();
	if (e->getType().length() > 0) {
		for (; it != subscribed.end(); ++it) {
			(*it)->notify(e);
		}
	}
}

CEventManager *CEventManager::instance() {
	static CEventManager *inst = 0;
	if (!inst) {
		inst = new CEventManager();
		clog << "[INFO] Event manager instance created." << endl;
	}
	return inst;
}