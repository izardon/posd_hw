#include "../src/triangle.h"

using namespace std;

class CompoundTriangle : public ::testing::Test {
protected:
void SetUp () override
{
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));
        triangle01 = new Triangle ("1", triangleVector);
        triangle02 = new Triangle ("2", triangleVector);
}

void TearDown () override
{
        delete triangle01;
        delete triangle02;
}

Shape * triangle01;
Shape * triangle02;
vector<TwoDimensionalCoordinate*> triangleVector;
};

TEST (Triangle, ConstructorNoException) {
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));

        ASSERT_NO_THROW (Triangle triangle ("1", triangleVector));
}

TEST (Triangle, ExceptionForVectorLessThanThree) {
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));

        try {
                Triangle triangle ("1", triangleVector);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not a triangle!", e);
        }
}

TEST (Triangle, ExceptionForVectorMoreThanThree) {
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (4, 7));

        try {
                Triangle triangle ("1", triangleVector);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not a triangle!", e);
        }
}

TEST (Triangle, Area) {
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));
        Triangle triangle ("1", triangleVector);

        ASSERT_NEAR (6, triangle.area (), 0.001);
}

TEST (Triangle, Perimeter) {
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));
        Triangle triangle ("1", triangleVector);

        ASSERT_DOUBLE_EQ (12, triangle.perimeter ());
}

TEST (Triangle, Info) {
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));
        Triangle triangle ("1", triangleVector);

        ASSERT_EQ ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", triangle.info ());
}

TEST (Triangle, GetId){
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));
        Triangle triangle ("1", triangleVector);

        ASSERT_EQ ("1", triangle.id ());
}

TEST (Triangle, GetDefaultColor){
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));
        Triangle triangle ("1", triangleVector);

        ASSERT_EQ ("white", triangle.color ());
}

TEST (Triangle, GetColor){
        vector<TwoDimensionalCoordinate*> triangleVector;

        triangleVector.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector.push_back (new TwoDimensionalCoordinate (0, 4));
        Triangle triangle ("1", triangleVector, "red");

        ASSERT_EQ ("red", triangle.color ());
}

TEST_F (CompoundTriangle, ExceptionForAddShape){
        try {
                triangle01->addShape (triangle02);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can add shape!", e);
        }
}

TEST_F (CompoundTriangle, ExceptionForDeleteShapeById){
        try {
                triangle01->deleteShapeById ("2");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can delete shape!", e);
        }
}

TEST_F (CompoundTriangle, ExceptionForGetShapeById){
        try {
                triangle01->getShapeById ("2");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can get shape!", e);
        }
}
