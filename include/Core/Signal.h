#pragma once
#include <map>
#include <functional>

template<typename ...Args>
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
	int Connect(T* Instance, void(T::*func)(Args...)) {
		return Connect([=](Args... _args) {
			(Instance->*func)(_args...);
		});
	}

	int Connect(const std::function<void(Args...)>& _slot) const{
		Slots.insert({ ++CurrentId, _slot });
		return CurrentId;
	}
	
	void Disconnect(int Id) {
		Slots.erase(Id);
		CurrentId--;
	}
	void DisconnectAll() {
		Slots.clear();
		CurrentId = 0;
	}
	void BroadCast(Args... _Args) {
		for (auto& Slot : Slots) {
			Slot.second(_Args...);
		}
	}
	
private:
	mutable std::map<int, std::function<void(Args...)>> Slots;
	mutable int CurrentId;
};

