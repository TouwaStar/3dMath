#pragma once
#include <iosfwd>


/* Bounding boxes enclose complex geomtery in order to make complex operations more efficient
Example from wiki: Viewing frustum tests. If the ray or viewing frustum does not intersect the bounding volume, it cannot intersect the object contained within */

using namespace core;

template <typename T> 
class Bounds2 {
public:

};

template <typename T>
class Bounds3 {
public:
	Point3<T> pMax, pMin;


	/* Default constructor intentionaly sets the extent to an invalid configuration
	By initializing with largest and smallest representable numbers we make sure that any operations yield correct results*/
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

	Bounds3(Point3<T> &p1, Point3<T> &p2) :
		pMin(Min(p1.getX(), p2.getX()), Min(p1.getY(), p1.getY()), Min(p1.getZ(), p1.getZ())),
		pMax(Max(p1.getX(), p2.getX()), Max(p1.getY(), p1.getY()), Max(p1.getZ(), p1.getZ())) {}
	

	const Point3<T> &operator[](int i) const;
	Point3<T> &operator[] (int i);

	inline Point3<T> Corner(int corner) const {
		return Point3<T>((*this)[(corner & 1)].getX(),
						(*this)[(corner & 2) ? 1 : 0].getY(),
						(*this)[(corner & 4) ? 1 : 0].getZ());
	}

	inline Vector3<T> Diagonal() const { return pMax - pMin };

	inline T SurfaceArea() const {
		Vector3<T> diagonal = Diagonal();
		return 2 * (diagonal.getX() * diagonal.getY() + diagonal.getX() * diagonal.getZ() + diagonal.getY() * diagonal.getZ());
	}

	inline T Volume() const {
		Vector3<T> diagonal = Diagonal();
		return diagonal.getX() * diagonal.getY() * diagonal.getZ();
	}
	// Returns index of which of the three axes is the longest
	// x = 0 y = 1 z = 2
	int MaxExtent() const {
		Vector3<T> diagonal = Diagonal();
		if (diagonal.getX() > diagonal.getY() && diagonal.getX() > diagonal.getZ()) {
			return 0;
		}
		else if (diagonal.getY() > diagonal.getZ()) {
			return 1;
		}
		return 2;
	}

	Point3<T> Lerp(const Point3f &p) const {
		return Point3<T>(point::Lerp(p.getX(), pMin.getX(), pMax.getX()),
						 point::Lerp(p.getY(), pMin.getY(), pMax.getY()),
						 point::Lerp(p.getZ(), pMin.getZ(), pMax.getZ()));
	}

	Vector3<T> Offset(const Point3<T> &p) const {
		Vector3<T> offset = p - pMin;
		if (pMax.getX() > pMin.getX()) {
			offset.setX(offset.getX() / pMax.getX() - pMin.getX());
		}
		if (pMax.getY() > pMin.getY()) {
			offset.setY(offset.getY() / pMax.getY() - pMin.getY());
		}
		if (pMax.getZ() > pMin.getZ()) {
			offset.setZ(offset.getZ() / pMax.getZ() - pMin.getZ());
		}
		return offset;
	}
};

namespace bounds {
	template <typename T>
	inline Bounds3<T> Union(const Bounds3<T> &a, const Point3<T> &p) {
		return Bounds3<T>(Point3<T>(Min(a.pMin.getX(), p.getX()),
									Min(a.pMin.getY(), p.getY()),
									Min(a.pMin.getZ(), p.getZ())),
						  Point3<T>(Max(a.pMax.getX(), p.getX()),
									Max(a.pMax.getY(), p.getY()),
									Max(a.pMax.getZ(), p.getZ())));
	}

	template <typename T>
	inline Bounds3<T> Union(const Bounds3<T> &a, const Bounds3<T> &b) {
		return Bounds3<T>(Point3<T>(Min(a.pMin.getX(), b.pMin.getX()),
									Min(a.pMin.getY(), b.pMin.getY()),
									Min(a.pMin.getZ(), b.pMin.getZ())),
						  Point3<T>(Max(a.pMax.getX(), b.pMax.getX()),
									Max(a.pMax.getY(), b.pMax.getY()),
									Max(a.pMax.getZ(), b.pMax.getZ())));
	}
	template <typename T>
	inline Bounds3<T> Intersect(const Bounds3<T> &a, const Bounds3<T> &b) {
		return Bounds3<T>(Point3<T>(Max(a.pMin.getX(), b.pMin.getX()),
									Max(a.pMin.getY(), b.pMin.getY()),
									Max(a.pMin.getZ(), b.pMin.getZ())),
						  Point3<T>(Min(a.pMax.getX(), b.pMax.getX()),
									Min(a.pMax.getY(), b.pMax.getY()),
									Min(a.pMax.getZ(), b.pMax.getZ())));
	}
	template <typename T>
	inline bool Overlaps(const Bounds3<T> &a, const Bounds3<T> &b) {
		return (a.pMax.getX() >= b.pMin.getX() && a.pMin.getX() <= b.pMax.getX() &&
				a.pMax.getY() >= b.pMin.getY() && a.pMin.getY() <= b.pMax.getY() && 
				a.pMax.getZ() >= b.pMin.getZ() && a.pMin.getZ() <= b.pMax.getZ())
	}
	template <typename T>
	inline bool Inside(const Bounds3<T> &a, const Point3<T> &p) {
		return (p.getX() >= a.pMin.getX() && p.getX() <= a.pMax.getX() &&
				p.getY() >= a.pMin.getY() && p.getY() <= a.pMax.getY() && 
				p.getZ() >= a.pMin.getZ() && p.getZ() <= a.pMax.getZ())
	}
	// the InsideEx version doesn't consider upper boundary points to be inside bounds.
	template <typename T>
	inline bool InsideEx(const Bounds3<T> &a, const Point3<T> &p) {
		return (p.getX() >= a.pMin.getX() && p.getX() < a.pMax.getX() &&
			p.getY() >= a.pMin.getY() && p.getY() < a.pMax.getY() &&
			p.getZ() >= a.pMin.getZ() && p.getZ() < a.pMax.getZ())
	}
	template <typename T, typename E>
	inline Bounds3<T> Expand(const Bounds3<T> &a, E expansion) {
		return Bounds3<T>(a.pMin - Vector3<T>(expansion, expansion, expansion),
						  a.pMax + Vector3<T>(expansion, expansion, expansion));
	}
}

typedef Bounds2<float> Bounds2f;
typedef Bounds2<int> Bounds2i;
typedef Bounds3<float> Bounds3f;
typedef Bounds3<int> Bounds3i;