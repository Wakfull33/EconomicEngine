#pragma once
#include <vector>

template<class T>
class ObjectManager {
	
public:
	ObjectManager() = default;

	static void Register(T& NewObject) {
		const auto it = std::find(ObjectRegistry.begin(), ObjectRegistry.end(), NewObject);
		if (it == ObjectRegistry.end()) {
			ObjectRegistry.push_back(NewObject);
		}
	}
	static T& GetObject(int index) {
		return AgentRegistry[index];
	}

	static int GetRegistrySize() {
		return AgentRegistry.size();
	}

private:

	static std::vector<T> ObjectRegistry;

};

template<class T>
std::vector<T> ObjectManager<T>::ObjectRegistry = std::vector<T>();