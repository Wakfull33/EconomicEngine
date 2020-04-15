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

	static void UpdateObjectsFromEvent(std::vector<T>& Elements, bool Start) {
		for (auto& Element : Elements) {
			auto it = std::find(ObjectRegistry.begin(), ObjectRegistry.end(), Element);
			if (it == ObjectRegistry.end()) {
				continue;
			}
			if (Start) {
				*it - Element;
			}
			else {
				*it + Element;
			}
		}
	}

private:

	static std::vector<T> ObjectRegistry;

};

template<class T>
std::vector<T> ObjectManager<T>::ObjectRegistry = std::vector<T>();