#pragma once
#include <iosfwd>

template <typename T> 
class Bounds2 {
public:

};

template <typename T>
class Bounds3 {
public:
	Point3<T> pMax, pMin;

	Bounds3() {
		T max = std::numeric_limits<T>::max();
		pMin = Point3<T>(max, max, max);
		T min = std::numeric_limits<T>::lowest();
		pMax = Point3<T>(min, min, min);
	}

	Bounds3(const Point3<T> &p) {
		pMin = p;
		pMax = p;
	}

	Bounds3(const Point3<T> &p1, const Point3<T> &p2) {
		pMin(std::min(p1.x, p2.x), std::min(p1.y, p1.y), std::min(p1.z, p1.z));
		pMax(std::max(p1.x, p2.x), std::max(p1.y, p1.y), std::max(p1.z, p1.z));
	};

	const Point3<T> &operator[](int i) const;
	Point3<T> &operator[] (int i);

	Point3<T> Corner(int corner) const {
		return Point3<T>((*this)[(corner & 1)].x,
						(*this)[(corner & 2) ? 1 : 0].y,
						(*this)[(corner & 4) ? 1 : 0].z);
	}
};

namespace bounds {
	template <typename T>
	inline Bounds3<T> Union(const Bounds3<T> &a, const Point3<T> &p) {
		return Bounds3<T>(Point3<T>(std::min(a.pMin.x, p.x),
									std::min(a.pMin.y, p.y),
									std::min(a.pMin.z, p.z)),
						  Point3<T>(std::max(a.pMax.x, p.x),
									std::max(a.pMax.y, p.y),
									std::max(a.pMax.z, p.z)));
	}

	template <typename T>
	inline Bounds3<T> Union(const Bounds3<T> &a, const Bounds3<T> &b) {
		return Bounds3<T>(Point3<T>(std::min(a.pMin.x, b.pMin.x),
									std::min(a.pMin.y, b.pMin.y),
									std::min(a.pMin.z, b.pMin.z)),
						  Point3<T>(std::max(a.pMax.x, b.pMax.x),
									std::max(a.pMax.y, b.pMax.y),
									std::max(a.pMax.z, b.pMax.z)));
	}
	template <typename T>
	inline Bounds3<T> Intersect(const Bounds3<T> &a, const Bounds3<T> &b) {
		return Bounds3<T>(Point3<T>(std::max(a.pMin.x, b.pMin.x),
									std::max(a.pMin.y, b.pMin.y),
									std::max(a.pMin.z, b.pMin.z)),
						  Point3<T>(std::min(a.pMax.x, b.pMax.x),
									std::min(a.pMax.y, b.pMax.y),
									std::min(a.pMax.z, b.pMax.z)));
	}
}

typedef Bounds2<float> Bounds2f;
typedef Bounds2<int> Bounds2i;
typedef Bounds3<float> Bounds3f;
typedef Bounds3<int> Bounds3i;