#pragma once
#include <vector>

template<class T>
class ObjectManager {
	
public:
	ObjectManager() = default;

	void Register(T& NewObject) {
		const auto it = std::find(ObjectRegistry.begin(), ObjectRegistry.end(), NewObject);
		if (it == ObjectRegistry.end()) {
			ObjectRegistry.push_back(NewObject);
		}
	}
	T& GetObject(int index) {
		return ObjectRegistry[index];
	}

	int GetRegistrySize() {
		return ObjectRegistry.size();
	}

	void UpdateObjectsFromEvent(std::vector<T>& Elements, bool Start) {
		for (auto& Element : Elements) {
			auto it = std::find(ObjectRegistry.begin(), ObjectRegistry.end(), Element);
			if (it == ObjectRegistry.end()) {
				continue;
			}
			if (Start) {
				*it + Element;
			}
			else {
				*it - Element;
			}
		}
	}

	std::vector<T>& GetRegistry(){
		return ObjectRegistry;
	}
	
private:

	std::vector<T> ObjectRegistry;

};
