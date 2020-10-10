#include "../src/ellipse.h"

using namespace std;

class CompoundEllipse : public ::testing::Test {
protected:
void SetUp () override
{
        ellipse01 = new Ellipse ("1", 6, 5);
        ellipse02 = new Ellipse ("2", 5, 4);
}

void TearDown () override
{
        delete ellipse01;
        delete ellipse02;
}

Shape * ellipse01;
Shape * ellipse02;
};

TEST (Ellipse, ConstructorNoException) {
        ASSERT_NO_THROW (Ellipse ellipse ("1", 2, 1));
}

TEST (Ellipse, ExceptionForSemiMajorAxesIsZero) {
        try {
                Ellipse ellipse ("1", 0, 1);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not an ellipse!", e);
        }
}

TEST (Ellipse, ExceptionForSemiMinorAxesIsZero) {
        try {
                Ellipse ellipse ("1", 1, 0);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not an ellipse!", e);
        }
}

TEST (Ellipse, ExceptionForSemiMajorAxesLessThanZero) {
        try {
                Ellipse ellipse ("1", 0, -1);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not an ellipse!", e);
        }
}

TEST (Ellipse, ExceptionForSemiMinorAxesLessThanZero) {
        try {
                Ellipse ellipse ("1", -1, 0);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not an ellipse!", e);
        }
}

TEST (Ellipse, ExceptionForSemiMajorAxesLessThanSemiMinorAxes) {
        try {
                Ellipse ellipse ("1", 1, 2);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not an ellipse!", e);
        }
}

TEST (Ellipse, AreaInt) {
        Ellipse ellipse ("1", 5, 4);

        ASSERT_NEAR (62.831, ellipse.area (), 0.001);
}

TEST (Ellipse, AreaDouble) {
        Ellipse ellipse ("1", 5.2, 4.3);

        ASSERT_NEAR (70.246, ellipse.area (), 0.001);
}

TEST (Ellipse, PerimeterInt) {
        Ellipse ellipse ("1", 3, 2);

        ASSERT_NEAR (16.566, ellipse.perimeter (), 0.001);
}

TEST (Ellipse, PerimeterDouble) {
        Ellipse ellipse ("1", 3.2, 2.8);

        ASSERT_NEAR (19.192, ellipse.perimeter (), 0.001);
}

TEST (Ellipse, Info) {
        Ellipse ellipse ("1", 6, 5);

        ASSERT_EQ ("Ellipse (6.000, 5.000)", ellipse.info ());
}

TEST (Ellipse, GetId){
        Ellipse ellipse ("1", 6, 5);

        ASSERT_EQ ("1", ellipse.id ());
}

TEST (Ellipse, GetDefaultColor){
        Ellipse ellipse ("1", 6, 5);

        ASSERT_EQ ("white", ellipse.color ());
}

TEST (Ellipse, GetColor){
        Ellipse ellipse ("1", 6, 5, "red");

        ASSERT_EQ ("red", ellipse.color ());
}

TEST_F (CompoundEllipse, ExceptionForAddShape){
        try {
                ellipse01->addShape (ellipse02);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can add shape!", e);
        }
}

TEST_F (CompoundEllipse, ExceptionForDeleteShapeById){
        try {
                ellipse01->deleteShapeById ("2");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can delete shape!", e);
        }
}

TEST_F (CompoundEllipse, ExceptionForGetShapeById){
        try {
                ellipse01->getShapeById ("2");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can get shape!", e);
        }
}
