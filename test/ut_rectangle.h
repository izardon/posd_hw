#include "../src/rectangle.h"

using namespace std;

TEST(Rectangle, ConstructorNoException) {
        ASSERT_NO_THROW(Rectangle rectangle(3, 1));
}

TEST(Rectangle, ExceptionForLengthIsZero) {
        try {
                Rectangle rectangle(0, 1);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not a rectangle!", e);
        }
}

TEST(Rectangle, ExceptionForWidthIsZero) {
        try {
                Rectangle rectangle(1, 0);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not a rectangle!", e);
        }
}

TEST(Rectangle, ExceptionForLengthLessThanZero) {
        try {
                Rectangle rectangle(0, -1);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not a rectangle!", e);
        }
}

TEST(Rectangle, ExceptionForWidthLessThanZero) {
        try {
                Rectangle rectangle(-1, 0);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not a rectangle!", e);
        }
}

TEST(Rectangle, AreaInt) {
        Rectangle rectangle(4, 6);

        ASSERT_DOUBLE_EQ(24, rectangle.area());
}

TEST(Rectangle, AreaDouble) {
        Rectangle rectangle(4.5, 6.2);

        ASSERT_DOUBLE_EQ(27.9, rectangle.area());
}

TEST(Rectangle, PerimeterInt ) {
        Rectangle rectangle(4, 6);

        ASSERT_DOUBLE_EQ(20, rectangle.perimeter());
}

TEST(Rectangle, PerimeterDouble) {
        Rectangle rectangle(4.3, 6.5);

        ASSERT_DOUBLE_EQ(21.6, rectangle.perimeter());
}

TEST(Rectangle, Info) {
        Rectangle rectangle(4.5, 6);

        ASSERT_EQ("Rectangle (4.500, 6.000)", rectangle.info());
}
