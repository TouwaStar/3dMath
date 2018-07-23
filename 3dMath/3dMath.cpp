
#include <iostream>
#include "Base\math3d.h"
using namespace math3d;
int main()
{
	Vector3f test(3, 5, 7);
	Vector3f test2(6, 8, 2);
	Vector4f test3(1, 2, 3);
	Vector2f test4((float)9.2, (float)5.1);
	Vector2f test5((float)-5.432, 0);
	test + test2;
	test3 + test2;
	Point3<float> Point1(3,4,6);
	Point3<float> Point2(5,8,12);
	Transform<float> transform1;
	Ray<float> ray(Point2,test2);
	RayDifferential<float> rayDiff(Point1, test);
	Bounds3f();
	Bounds3<float>(Point1, Point2);
	Bounds3<float>(Point3<float>(3,5,6));
	
	//Sample use and syntax

	//std::cout << transform1.IsScaled();
	std::cout << ray.direction << std::endl;
	std::cout << rayDiff.hasDifferentials << std::endl;
	std::cout << Max<float>()<<std::endl;
	std::cout << Infinity<float>() << std::endl;
	transform1 = transform::Rotate(1.2f, test);

	std::cout << point::Distance(Point1, Point2) << std::endl;
	std::cout << Point1.getDistance(Point2) << "\n\n";

	std::cout << test4 + test5 << std::endl;
	std::cout << test5.getLen() << std::endl;
	std::cout << test4 * 9 << std::endl;

	std::cout << test << std::endl;
	std::cout << test3 << std::endl;
	std::cout << (Vector4f)test2 << std::endl;
	std::cout << (Vector3f)test3 << std::endl;
	std::cout << test.getCross(test2) << std::endl;

	Matrix3f testMatrix(test, test2, test);
	Matrix3f testMatrix2(test3, test, test);
	std::cout<<testMatrix - testMatrix2;
	std::cout<<testMatrix * testMatrix2;
	std::cout << testMatrix.getVectors()->getX()<<"\n\n";
	std::cout << testMatrix << std::endl;
	testMatrix.transpose();
	std::cout << testMatrix << std::endl;

	Quaternion<float> testQuaternion(test3, 4.6);
	std::cout << testQuaternion << std::endl;
    std::cout << testQuaternion.getNormalize()<<std::endl;
	std::cout << testQuaternion.getInverse() << std::endl;

	std::cout << quaternion::Slerp(testQuaternion, testQuaternion, (float)3.2) << std::endl;
	std::cout << matrix::Negate(testMatrix) << std::endl;
	std::cout << vector::Cross(test, test2) << std::endl;
	
    return 0;
}

