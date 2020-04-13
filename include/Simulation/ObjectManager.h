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
		return ObjectRegistry[index];
	}

	static int GetRegistrySize() {
		return ObjectRegistry.size();
	}

	static void UpdateObject(int index, T Element) {
		ObjectRegistry[index] = Element;
		//TODO Benoit Save Actual registry if update is temporary
	}

	static void UpdateObjects(std::vector<T>& Elements) {
		for (auto& Element : Elements) {
			//TODO Benoit Replace Element in registry
			//TODO Benoit Save Actual registry if update is temporary
		}
	}

private:

	static std::vector<T> ObjectRegistry;

};

template<class T>
std::vector<T> ObjectManager<T>::ObjectRegistry = std::vector<T>();