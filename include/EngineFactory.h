#pragma once

#include <map>
#include <string>

template<class T>
T CreateObject() {
	return new T();
}

template<class T>
class EngineFactory{

public:

	static std::map<std::string, T*(*)()>* GetRegistry() {
		if (Registry == nullptr) {
			Registry = new std::map<std::string, T*(*)()>;
		}
		return Registry;
	}
	static T* CreateEntity(std::string& Name) {
		typename std::map<std::string, T*(*)()>::iterator it = GetRegistry()->find(Name);
		if (it != GetRegistry()->end()) {
			return it->second();
		}
		return nullptr;
	}
	static void Register(std::string& Name, T*(*func)()) {
		GetRegistry()->insert(std::make_pair(Name, func));
	}
	
private:	
	static std::map<std::string, T*(*)()>* Registry;
};

template<typename T>
std::map<std::string, T*(*)()>* EngineFactory<T>::Registry = nullptr;
