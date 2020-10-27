#include "../src/utility.h"


class UtilityTest : public ::testing::Test {
protected:
void SetUp () override
{
        triangleVector3a4b5c.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector3a4b5c.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector3a4b5c.push_back (new TwoDimensionalCoordinate (0, 4));
        triangle1i3a4b5c = new Triangle ("2", triangleVector3a4b5c);
        ellipse1i3maj2mio = new Ellipse ("3", 3, 2, "red");
        rectangle1i3l4h = new Rectangle ("4", 3, 4);

        shapes01.push_back (triangle1i3a4b5c);
        compoundShape01 = new CompoundShape ("1", shapes01);

        shapes00.push_back (compoundShape01);
        shapes00.push_back (ellipse1i3maj2mio);
        shapes00.push_back (rectangle1i3l4h);
        compoundShape00 = new CompoundShape ("0", shapes00);
}

void TearDown () override
{
        delete rectangle1i3l4h;
        delete triangle1i3a4b5c;
        delete ellipse1i3maj2mio;
}

Shape * rectangle1i3l4h;
vector<TwoDimensionalCoordinate*> triangleVector3a4b5c;
Shape * triangle1i3a4b5c;
Shape * ellipse1i3maj2mio;

Shape * compoundShape00;
Shape * compoundShape01;

list<Shape *> shapes00;
list<Shape *> shapes01;
};

TEST_F (UtilityTest, GetShapeById) {
        ASSERT_EQ (triangle1i3a4b5c, getShapeById (compoundShape00, "2"));
}

TEST_F (UtilityTest, ExceptionForGetShapeByIdIsNotCompoundShape) {
        try{
                ASSERT_EQ (triangle1i3a4b5c, getShapeById (triangle1i3a4b5c, "1"));
        }catch (string e) {
                ASSERT_EQ ("Only compound shape can get shape!", e);
        }
}

TEST_F (UtilityTest, ExceptionForGetShapeByIdIsNotFound) {
        try{
                ASSERT_EQ (triangle1i3a4b5c, getShapeById (compoundShape00, "5"));
        }catch (string e) {
                ASSERT_EQ ("Expected get shape but shape not found", e);
        }
}

TEST_F (UtilityTest, ExceptionForFilterIsNotCompoundShape) {
        try{
                filterShape<AreaFilter> (triangle1i3a4b5c, AreaFilter (1, 10));
        }catch (string e) {
                ASSERT_EQ ("Only compound shape can filter shape!", e);
        }
}

TEST_F (UtilityTest, AreaFilterCompoundShape) {
        ASSERT_EQ (2, filterShape<AreaFilter> (compoundShape00, AreaFilter (10, 5)).size ());
        ASSERT_EQ (compoundShape01, filterShape<AreaFilter> (compoundShape00, AreaFilter (10, 5)).at (0));
        ASSERT_EQ (triangle1i3a4b5c, filterShape<AreaFilter> (compoundShape00, AreaFilter (10, 5)).at (1));
}

TEST_F (UtilityTest, PerimeterFilterCompoundShape) {
        ASSERT_EQ (3, filterShape<AreaFilter> (compoundShape00, AreaFilter (15, 5)).size ());
        ASSERT_EQ (compoundShape01, filterShape<AreaFilter> (compoundShape00, AreaFilter (15, 5)).at (0));
        ASSERT_EQ (triangle1i3a4b5c, filterShape<AreaFilter> (compoundShape00, AreaFilter (15, 5)).at (1));
        ASSERT_EQ (rectangle1i3l4h, filterShape<AreaFilter> (compoundShape00, AreaFilter (15, 5)).at (2));
}

TEST_F (UtilityTest, ColorFilterCompoundShape) {
        ASSERT_EQ (1, filterShape<ColorFilter> (compoundShape00, ColorFilter ("red")).size ());
        ASSERT_EQ (ellipse1i3maj2mio, filterShape<ColorFilter> (compoundShape00, ColorFilter ("red")).at (0));
}

TEST_F (UtilityTest, TypeFilterCompoundShape) {
        ASSERT_EQ (1, filterShape<TypeFilter> (compoundShape00, TypeFilter ("Compound Shape")).size ());
        ASSERT_EQ (compoundShape01, filterShape<TypeFilter> (compoundShape00, TypeFilter ("Compound Shape")).at (0));
}
