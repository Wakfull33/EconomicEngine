#pragma once
#include <vector>

template<class T>
class ObjectManager {
	
public:
	ObjectManager() = default;

	static void Register(T& NewObject) {
		const auto it = std::find(AgentRegistry.begin(), AgentRegistry.end(), NewObject);
		if (it == AgentRegistry.end()) {
			AgentRegistry.push_back(NewObject);
		}
	}
	static T& GetObject(int index) {
		return AgentRegistry[index];
	}

private:

	static std::vector<T> AgentRegistry;

};

template<class T>
std::vector<T> ObjectManager<T>::AgentRegistry = std::vector<T>();