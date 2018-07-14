#pragma once
#include <iosfwd>
template <typename T>
class Transform {
private:
	Matrix4<T> matrix, matrixInverse;
public:
	inline Transform() {};
	inline Transform(const T a[4][4]) {
		matrix = Matrix4<T>(a);
		matrixInverse = math3d::MatrixInverse(matrix);
	}
	inline Transform(const Matrix4<T> &a) {
		matrix = a;
		matrixInverse = math3d::MatrixInverse(a);
	}
	inline Transform(const Matrix4<T> &a, const Matrix4<T> &aInv) {
		matrix = a;
		matrixInverse = aInv;
	}
	inline Matrix4<T> &getMatrix() { return matrix; }
	inline Matrix4<T> &getInverse() { return matrixInverse };

	template <typename T>
	inline Vector3<T> operator()(const Vector3<T> &v) const {
		T x = v.getX(), y = v.getY(), z = v.getZ();
		Vector4<T> el = matrix.getVectors();
		return Vector3<T>(vector::Dot(el[0], v), vector::Dot(el[0], v), vector::Dot(el[0], v));
	};
	/* Test if a transformation has a scaling term in it*//*
	bool IsScaled() const {
		T a = (*this)(Vector3<T>(1, 0, 0)).getLenSquared();
		T b = (*this)(Vector3<T>(0, 1, 0)).getLenSquared();
		T c = (*this)(Vector3<T>(0, 0, 1)).getLenSquared();
		return core::NotOne(a) || core::NotOne(b) || core::NotOne(c);
	}*/
};

namespace transform {
	template <typename T>
	inline Transform<T> Inverse(const Transform<T> &a) {
		return Transform(a.getInverse(), a.getMatrix());
	}
	template <typename T> 
	inline Transform<T> Transpose(const Transform<T> &a) {
		return Transform(matrix::Transpose(a.getMatrix()), matrix::Transpose(a.getInverse()));
	}
	template <typename T>
	inline Transform<T> Translate(const Vector3<T> &del) {
		return Transform((1, 0, 0, del.getX(),
						 0, 1, 0, del.getY(),
						 0, 0, 1, del.getZ(),
						 0, 0, 0, 1); , 
						 (1, 0, 0, -del.getX(),
						 0, 1, 0, -del.getY(),
						 0, 0, 1, -del.getZ(),
						 0, 0, 0, 1);)
	}
	template <typename T>
	inline Transform<T> Scale(T x, T y, T z) {
		return Transform((x, 0, 0, 0,
						 0, y, 0, 0,
						 0, 0, z, 0,
						 0, 0, 0, 1);,
						 (1/x, 0, 0, 0,
						 0, 1/y, 0, 0,
						 0, 0, 1/z, 0,
						 0, 0, 0, 1);)
	}
	template <typename T>
	inline Transform<T> RotateX(T theta) {
		T sinTheta = std::sin(core::Radians(theta));
		T cosTheta = std::cos(core::Radians(theta));
		Matrix4<T> matrix(1, 0, 0, 0,
						  0, cosTheta, -sinTheta, 0,
						  0, sinTheta, cosTheta, 0,
						  0, 0, 0, 1);
		return Transform(matrix, Transpose(matrix));
	}; 
	template <typename T>
	inline Transform<T> RotateY(T theta) {
		T sinTheta = std::sin(core::Radians(theta));
		T cosTheta = std::cos(core::Radians(theta));
		Matrix4<T> matrix(cosTheta, 0, sinTheta, 0,
						  0, 1, 0, 0, 
						  -sinTheta, 0, cosTheta, 0,
						  0, 0, 0, 1);
		return Transform(matrix, Transpose(matrix));
	};
	template <typename T>
	inline Transform<T> RotateZ(T theta) {
		T sinTheta = std::sin(core::Radians(theta));
		T cosTheta = std::cos(core::Radians(theta));
		Matrix4<T> matrix(cosTheta, -sinTheta, 0, 0,
						  sinTheta, cosTheta, 0, 0,
						  0, 0, 1, 0,
						  0, 0, 0, 1);
		return Transform(matrix, Transpose(matrix));
	};
	template <typename T>
	Transform<T> Rotate(T theta, const Vector3<T> &axis) {
		T sinTheta = std::sin(core::Radians(theta));
		T cosTheta = std::cos(core::Radians(theta));
		Vector3<T> norm = vector::Normalize(axis);
		Matrix4<T> m;
		m.setValues(
			// Compute rotation of first basis vector
				norm.getX() * norm.getX() + (1 - norm.getX() * norm.getX()) * cosTheta,
				norm.getX() * norm.getY() * (1 - cosTheta) - norm.getZ() * sinTheta,
				norm.getX() * norm.getZ() * (1 - cosTheta) + norm.getY() * sinTheta,
				(T)0,
			// Compute rotation of second 
			norm.getX() * norm.getY() * (1 - cosTheta) + norm.getZ() * sinTheta,
			norm.getY() * norm.getY() + (1 - norm.getY() * norm.getY()) * cosTheta,
			norm.getY() * norm.getZ() * (1 - cosTheta) - norm.getX() * sinTheta,
			(T)0,
			// Compute rotation of third
			norm.getX() * norm.getZ() * (1 - cosTheta) - norm.getY() * sinTheta,
			norm.getY() * norm.getZ() * (1 - cosTheta) + norm.getX() * sinTheta,
			norm.getZ() * norm.getZ() + (1 - norm.getZ() * norm.getZ()) * cosTheta,
			(T)0,
			(T)0,(T)0,(T)0,(T)1
		);
		return Transform<T>(m, matrix::Transpose(m));
	}
}
