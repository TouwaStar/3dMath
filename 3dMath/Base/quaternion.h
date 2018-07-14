#pragma once
#include <iosfwd>


template <typename T>
class Quaternion {
private:
	T scalar;
	Vector3<T> Vector;
public:
	inline Quaternion() {
		scalar = 0;
		Vector = Vector3();
	};
	inline Quaternion(const Vector3<T> v, const T s) {
		scalar = s;
		Vector = v;
	};

	inline Quaternion<T> operator +(const Quaternion<T>& q) 
	{ return Quaternion(Vector + q.Vector, scalar + q.scalar);}
	
	inline Quaternion<T> operator -(const Quaternion<T>& q)
	{ return Quaternion(Vector - q.Vector, scalar - q.scalar);}
	
	inline Quaternion<T> operator *(const Quaternion<T>& q){
		return Quaternion(q.Vector*scalar + Vector * q.scalar + Vector.getCross(q.Vector), 
							scalar * q.scalar - Vector.getDot(q.Vector));
	}
	inline Quaternion<T> operator *(const T& f) {
		return Quaternion(this->Vector*f, this->scalar*f);
	}
	inline Quaternion<T> operator /(const Quaternion<T>& q) {
		Quaternion p(q);
		return *this * p.getInverse();
	}
	inline Quaternion<T> operator /(const T& f) {
		return Quaternion(this->Vector / f, this->scalar / f);
	}

	inline Quaternion<T>& operator +=(const Quaternion<T>& q){
		scalar += q.scalar;
		Vector += q.Vector;
		return *this;
	}
	
	inline Quaternion<T>& operator -=(const Quaternion<T>& q){
		scalar -= q.scalar;
		Vector-= q.Vector;
		return *this;
	}
	
	inline Quaternion<T>& operator *=(const Quaternion<T>& q) {
		T scalarTemp = scalar * q.scalar - Vector.getDot(q.Vector);
		Vector = q.Vector*scalar + Vector * q.scalar + Vector.getCross(q.Vector);
		scalar = scalarTemp;
		return *this;
	}
	inline Quaternion<T> operator *=(const T& f) {
		this->scalar *= f;
		this->Vector *= f;
		return *this;
	}


	inline T dot(const Quaternion<T>& q) {
		return this->Vector.getDot(q.Vector) + this->scalar *q.scalar;
	}

	inline Quaternion<T> getConjugate() {
		return Quaternion(this->Vector*(-1), this->scalar);
	}

	inline Quaternion<T> getInverse() {
		T abs = sqrt(dot(*this));
		abs *= abs;
		abs = 1 / abs;
		Quaternion conj = getConjugate();
		return Quaternion(conj.Vector*abs, conj.scalar*abs);
	}

	inline void normalize() {
		*this = *this / sqrt(this->dot(*this));
	}
	inline Quaternion getNormalize() {
		return *this / sqrt(this->dot(*this));
	}

	friend inline std::ostream& operator<<(std::ostream& os, Quaternion<T>& e) {
		os << e.Vector << e.scalar << std::endl;
		return os;
	}
};

namespace quaternion {
	template <typename T>
	inline Quaternion<T> Normalize(Quaternion<T>& q) {
		return q / sqrt(q.dot(q));
	}
	template <typename T>
	Quaternion<T> Slerp(Quaternion<T>& q1,Quaternion<T>& q2, T t) {
		T cosTheta = q1.dot(q2);
		if (cosTheta > .9995f) {
			return quaternion::Normalize(q1 *(1 - t) + q2 * t);
		}
		else {
			T thetap = std::acos(core::Clamp(cosTheta, -1, 1)) * t;
			return q1 * std::cos(thetap) * quaternion::Normalize(q2 - q1 * cosTheta) * std::sin(thetap);
		}
	};


}
