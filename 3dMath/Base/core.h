#pragma once
#pragma warning( disable : 4244 )
#include <iosfwd>
static float Pi = 3.14159265358979323846;

template <typename T>
inline T Max(){
	return std::numeric_limits<T>::max();
}
template <typename T>
inline T Infinity() {
	return std::numeric_limits<T>::infinity();
}

namespace core {
	template <typename a, typename b, typename c>
	inline a Clamp(a value, b low, c high) {
		if (value < low) {
			return low;
		}
		else if(value > high){
			return high;
		}
		else {
			return value;
		}
	}
	
	template<class T>
	const T& Min(const T& a, const T& b)
	{
		return (b < a) ? b : a;
	}

	template<class T>
	const T& Max(const T& a, const T& b)
	{
		return (a < b) ? b : a;
	}

	template<typename T> 
	const bool NotOne(const T a) {
		return a<.999f || a>1.001f;
	}

	template<typename T>
	inline T Radians(T a) { return (Pi / 180)*a; };

	template<typename T>
	inline T Degrees(T a) { return (180 / Pi)*a; };
}

