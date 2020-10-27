#include "../src/rectangle.h"

using namespace std;

class CompoundRectangle : public ::testing::Test {
protected:
void SetUp () override
{
        rectangle01 = new Rectangle ("1", 3, 4);
        rectangle02 = new Rectangle ("2", 2, 2);
}

void TearDown () override
{
        delete rectangle01;
        delete rectangle02;
}

Shape * rectangle01;
Shape * rectangle02;
};

TEST (Rectangle, ConstructorNoException) {
        ASSERT_NO_THROW (Rectangle rectangle ("1", 3, 1));
        ASSERT_NO_THROW (Rectangle rectangle ("2", 3, 1, "red"));
}

TEST (Rectangle, ExceptionForLengthIsZero) {
        try {
                Rectangle rectangle ("1", 0, 1);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not a rectangle!", e);
        }
}

TEST (Rectangle, ExceptionForWidthIsZero) {
        try {
                Rectangle rectangle ("1", 1, 0);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not a rectangle!", e);
        }
}

TEST (Rectangle, ExceptionForLengthLessThanZero) {
        try {
                Rectangle rectangle ("1", 0, -1);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not a rectangle!", e);
        }
}

TEST (Rectangle, ExceptionForWidthLessThanZero) {
        try {
                Rectangle rectangle ("1", -1, 0);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not a rectangle!", e);
        }
}

TEST (Rectangle, AreaInt) {
        Rectangle rectangle ("1", 4, 6);

        ASSERT_DOUBLE_EQ (24, rectangle.area ());
}

TEST (Rectangle, AreaDouble) {
        Rectangle rectangle ("1", 4.5, 6.2);

        ASSERT_DOUBLE_EQ (27.9, rectangle.area ());
}

TEST (Rectangle, PerimeterInt) {
        Rectangle rectangle ("1", 4, 6);

        ASSERT_DOUBLE_EQ (20, rectangle.perimeter ());
}

TEST (Rectangle, PerimeterDouble) {
        Rectangle rectangle ("1", 4.3, 6.5);

        ASSERT_DOUBLE_EQ (21.6, rectangle.perimeter ());
}

TEST (Rectangle, Info) {
        Rectangle rectangle ("1", 4.5, 6);

        ASSERT_EQ ("Rectangle (4.500, 6.000)", rectangle.info ());
}

TEST (Rectangle, Type) {
        Rectangle rectangle ("1", 4.5, 6);

        ASSERT_EQ ("Rectangle", rectangle.type ());
}

TEST (Rectangle, GetId){
        Rectangle rectangle ("1", 4.5, 6);

        ASSERT_EQ ("1", rectangle.id ());
}

TEST (Rectangle, GetDefaultColor){
        Rectangle rectangle ("1", 4.5, 6);

        ASSERT_EQ ("white", rectangle.color ());
}

TEST (Rectangle, GetColor){
        Rectangle rectangle ("1", 4.5, 6, "red");

        ASSERT_EQ ("red", rectangle.color ());
}

TEST_F (CompoundRectangle, ExceptionForAddShape){
        try {
                rectangle01->addShape (rectangle02);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can add shape!", e);
        }
}

TEST_F (CompoundRectangle, ExceptionForDeleteShapeById){
        try {
                rectangle01->deleteShapeById ("2");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can delete shape!", e);
        }
}

TEST_F (CompoundRectangle, ExceptionForGetShapeById){
        try {
                rectangle01->getShapeById ("2");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Only compound shape can get shape!", e);
        }
}
