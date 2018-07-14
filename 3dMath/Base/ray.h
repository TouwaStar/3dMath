#pragma once
#include <iosfwd>
	template<typename T>
	class Ray {
	public:
		mutable T tMax;
		Point3<T> origin;
		Vector3<T> direction;
		T time;
		//const Medium *medium;

		Ray() {
			tMax = Infinity<T>();
			time = (T)0;
			//medium(nullptr)
		}
		Ray(const Point3<T> &o, const Vector3<T> &d, T tM = Infinity<T>(), T ti = (T)0/*,const med = Medium(nullptr)*/) {
			origin = o;
			direction = d;
			tMax = tM;
			time = ti;
			// medium = med;
		}
		Point3<T> operator()(T t)const {
			return origin + destination * t;
		}

	};
	
	template <typename T>
	class RayDifferential : public Ray<T> {
	public:
		bool hasDifferentials;
		Point3<T> rayXOrigin, rayYOrigin;
		Vector3<T> rayXDirection, rayYDirection;
		RayDifferential(const Ray &ray) : Ray(ray) {
			hasDifferentials = false;
		}
		RayDifferential() {
			hasDiffrentials = false;
		}
		RayDifferential(const Point3<T> &o, const Vector3<T> &d, T tM = Infinity<T>(), T ti = (T)0/*,const Medium *med = nullptr*/) {
			origin = o;
			direction = d;
			tMax = tM;
			time = ti;
			//medium = med;
			hasDifferentials = false;
		}
		void ScaleDifferentials(T s) {
			rayXOrigin = (rayXOrigin - origin)*s + origin;
			rayXDirection = (rayXDirection - direction)*s + direction;

			rayYOrigin = (rayYOrigin - origin)*s + origin;
			rayYDirection = (rayYDirection - direction)*s + direction;
		}
	};