#include "../src/triangle.h"

using namespace std;

TEST(Triangle, ConstructorNoException) {
        vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));

        ASSERT_NO_THROW(Triangle triangle(triangleVector));
}

TEST(Triangle, ExceptionForVectorLessThanThree) {
        vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));

        try {
                Triangle triangle(triangleVector);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not a triangle!", e);
        }
}

TEST(Triangle, ExceptionForVectorMoreThanThree) {
        vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(4, 7));

        try {
                Triangle triangle(triangleVector);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not a triangle!", e);
        }
}

TEST(Triangle, Area) {
        vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        Triangle triangle(triangleVector);

        ASSERT_NEAR(6, triangle.area(), 0.001);
}

TEST(Triangle, Perimeter) {
        vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        Triangle triangle(triangleVector);

        ASSERT_DOUBLE_EQ(12, triangle.perimeter());
}

TEST(Triangle, Info) {
        vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        Triangle triangle(triangleVector);

        ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", triangle.info());
}
