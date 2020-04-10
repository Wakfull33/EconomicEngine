#pragma once
#include <map>

template<typename ... Args>
class Signal {

public:
	Signal()
		: CurrentId(0){
	}
	~Signal() {
		DisconnectAll();
	}
	Signal(const Signal& _Signal){
		DisconnectAll();
	}
	Signal& operator=(const Signal& _Signal) {
		DisconnectAll();
		return *this;
	}
	template<typename T>
	int Connect(void(T::*func)(Args...)) {
		typename std::map<int, void(*)(Args...)>::iterator it = Slots.find(func);
		if (it == Slots.end()) {
			CurrentId++;
			Slots.insert(std::make_pair(CurrentId, func));
		}
		return CurrentId;
	}
	void Disconnect(int Id) {
		Slots.erase(Id);
		CurrentId--;
	}
	void DisconnectAll() {
		for (auto& Slot: Slots) {
			Disconnect(Slot.first());
		}
	}
	void BroadCast(Args... _Args) {
		for (auto& Slot : Slots) {
			Slot.second(_Args...);
		}
	}
	
private:
	std::map<int, void(*)(Args...)> Slots;
	int CurrentId;
};

