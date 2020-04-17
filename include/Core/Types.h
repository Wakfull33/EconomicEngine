#pragma once

template<class T>
class ValKeeper {
public:

	ValKeeper() = default;
	
	ValKeeper(T Value)
		: ActualValue(Value), PrecedentValue(T()){
	}

	const T& Get() const {
		return ActualValue;
	}

	void Set(const T& NewValue) {
		if (NewValue != ActualValue) {
			PrecedentValue = ActualValue;
			ActualValue = NewValue;
		}
	}

	void Restore() {
		if (ActualValue != PrecedentValue) {
			T Temporary = ActualValue;
			ActualValue = PrecedentValue;
			PrecedentValue = Temporary;
		}
	}
private:
	T ActualValue;
	T PrecedentValue;
};