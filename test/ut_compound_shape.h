#include "../src/shape.h"
#include "../src/compound_shape.h"

class CompoundShapeTest : public ::testing::Test {
protected:
void SetUp () override
{
        rectangle1i3l4h = new Rectangle ("r1", 3, 4);
        rectangle2i2l2h = new Rectangle ("r2", 2, 2);

        triangleVector3a4b5c.push_back (new TwoDimensionalCoordinate (0, 0));
        triangleVector3a4b5c.push_back (new TwoDimensionalCoordinate (3, 0));
        triangleVector3a4b5c.push_back (new TwoDimensionalCoordinate (0, 4));
        triangle1i3a4b5c = new Triangle ("t1", triangleVector3a4b5c);

        ellipse1i3maj2mio = new Ellipse ("e1", 3, 2);

        shapes01 = new vector<Shape *>();
        shapes02 = new vector<Shape *>();
        shapes03 = new vector<Shape *>();
}

void TearDown () override
{
        delete rectangle1i3l4h;
        delete rectangle2i2l2h;
        delete triangle1i3a4b5c;
        delete ellipse1i3maj2mio;
        delete shapes03;
        delete shapes02;
        delete shapes01;
}

Shape * rectangle1i3l4h;
Shape * rectangle2i2l2h;
vector<TwoDimensionalCoordinate*> triangleVector3a4b5c;
Shape * triangle1i3a4b5c;
Shape * ellipse1i3maj2mio;

vector<Shape *> * shapes01;
vector<Shape *> * shapes02;
vector<Shape *> * shapes03;
};

TEST_F (CompoundShapeTest, ConstructorNoException){
        shapes01->push_back (rectangle1i3l4h);
        shapes01->push_back (rectangle2i2l2h);
        ASSERT_NO_THROW (CompoundShape ("c1", shapes01));
}

TEST_F (CompoundShapeTest, ExceptionForNoShape){
        try {
                CompoundShape ("c1", shapes01);
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("This is not a compound shape!", e);
        }
}

TEST_F (CompoundShapeTest, GetId){
        shapes01->push_back (rectangle1i3l4h);
        CompoundShape compoundShape ("c1", shapes01);

        ASSERT_EQ ("c1", compoundShape.id ());
}

TEST_F (CompoundShapeTest, GetDefaultColor){
        shapes01->push_back (rectangle1i3l4h);
        CompoundShape compoundShape ("c1", shapes01);

        ASSERT_EQ ("transparent", compoundShape.color ());
}

TEST_F (CompoundShapeTest, Area){
        shapes01->push_back (rectangle1i3l4h);
        shapes01->push_back (rectangle2i2l2h);
        CompoundShape compoundShape ("c1", shapes01);

        ASSERT_EQ (16, compoundShape.area ());
}

TEST_F (CompoundShapeTest, Perimeter){
        shapes01->push_back (rectangle1i3l4h);
        shapes01->push_back (rectangle2i2l2h);
        CompoundShape compoundShape ("c1", shapes01);

        ASSERT_EQ (22, compoundShape.perimeter ());
}

TEST_F (CompoundShapeTest, Info){
        shapes01->push_back (rectangle1i3l4h);
        shapes01->push_back (rectangle2i2l2h);
        CompoundShape compoundShape ("c1", shapes01);

        ASSERT_EQ ("Compound Shape {Rectangle (3.000, 4.000), Rectangle (2.000, 2.000)}", compoundShape.info ());
}

TEST_F (CompoundShapeTest, AddShape){
        shapes02->push_back (triangle1i3a4b5c);//12
        CompoundShape * compoundShape02 = new CompoundShape ("c2", shapes02);

        shapes01->push_back (compoundShape02);
        shapes01->push_back (rectangle1i3l4h);//14
        shapes01->push_back (rectangle2i2l2h);//8
        CompoundShape * compoundShape01 = new CompoundShape ("c1", shapes01);

        shapes03->push_back (ellipse1i3maj2mio);//16.566
        CompoundShape * compoundShape03 = new CompoundShape ("c3", shapes03);

        compoundShape02->addShape (compoundShape03);

        ASSERT_NEAR (50.566, compoundShape01->perimeter (), 0.001);

        delete compoundShape01;
        delete compoundShape02;
        delete compoundShape03;
}

TEST_F (CompoundShapeTest, ExceptionForGetShapeByIdNotFound){
        shapes01->push_back (rectangle1i3l4h);//14
        CompoundShape * compoundShape01 = new CompoundShape ("c1", shapes01);

        shapes02->push_back (triangle1i3a4b5c);//12
        CompoundShape * compoundShape02 = new CompoundShape ("c2", shapes02);

        shapes03->push_back (ellipse1i3maj2mio);//16.566
        CompoundShape * compoundShape03 = new CompoundShape ("c3", shapes03);

        compoundShape02->addShape (compoundShape03);
        compoundShape01->addShape (compoundShape02);
        compoundShape01->addShape (rectangle2i2l2h);//8

        try {
                compoundShape01->getShapeById ("9");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Expected get shape but shape not found", e);
        }

        delete compoundShape03;
        delete compoundShape02;
        delete compoundShape01;
}

TEST_F (CompoundShapeTest, GetShapeById){
        shapes01->push_back (rectangle1i3l4h);//14
        CompoundShape * compoundShape01 = new CompoundShape ("c1", shapes01);

        shapes02->push_back (triangle1i3a4b5c);//12
        CompoundShape * compoundShape02 = new CompoundShape ("c2", shapes02);

        shapes03->push_back (ellipse1i3maj2mio);//16.566
        CompoundShape * compoundShape03 = new CompoundShape ("c3", shapes03);

        compoundShape02->addShape (compoundShape03);
        compoundShape01->addShape (compoundShape02);
        compoundShape01->addShape (rectangle2i2l2h);//8

        ASSERT_EQ (rectangle1i3l4h, compoundShape01->getShapeById ("r1"));
        ASSERT_EQ (compoundShape02, compoundShape01->getShapeById ("c2"));
        ASSERT_EQ (triangle1i3a4b5c, compoundShape01->getShapeById ("t1"));
        ASSERT_EQ (compoundShape03, compoundShape01->getShapeById ("c3"));
        ASSERT_EQ (ellipse1i3maj2mio, compoundShape01->getShapeById ("e1"));
        ASSERT_EQ (rectangle2i2l2h, compoundShape01->getShapeById ("r2"));

        delete compoundShape03;
        delete compoundShape02;
        delete compoundShape01;
}

TEST_F (CompoundShapeTest, ExceptionForDeleteIdNotFound){
        shapes01->push_back (rectangle1i3l4h);//14
        CompoundShape * compoundShape01 = new CompoundShape ("c1", shapes01);

        shapes02->push_back (triangle1i3a4b5c);//12
        CompoundShape * compoundShape02 = new CompoundShape ("c2", shapes02);

        shapes03->push_back (ellipse1i3maj2mio);//16.566
        CompoundShape * compoundShape03 = new CompoundShape ("c3", shapes03);

        compoundShape02->addShape (compoundShape03);
        compoundShape01->addShape (compoundShape02);
        compoundShape01->addShape (rectangle2i2l2h);//8

        try {
                compoundShape01->deleteShapeById ("9");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Expected delete shape but shape not found", e);
        }

        delete compoundShape03;
        delete compoundShape02;
        delete compoundShape01;
}

TEST_F (CompoundShapeTest, DeleteShapeById){
        shapes01->push_back (rectangle1i3l4h);//14
        CompoundShape * compoundShape01 = new CompoundShape ("c1", shapes01);

        shapes02->push_back (triangle1i3a4b5c);//12
        CompoundShape * compoundShape02 = new CompoundShape ("c2", shapes02);

        shapes03->push_back (ellipse1i3maj2mio);//16.566
        CompoundShape * compoundShape03 = new CompoundShape ("c3", shapes03);

        compoundShape02->addShape (compoundShape03);
        compoundShape01->addShape (compoundShape02);
        compoundShape01->addShape (rectangle2i2l2h);//8

        ASSERT_EQ (rectangle1i3l4h, compoundShape01->getShapeById ("r1"));
        ASSERT_EQ (compoundShape02, compoundShape01->getShapeById ("c2"));
        ASSERT_EQ (triangle1i3a4b5c, compoundShape01->getShapeById ("t1"));
        ASSERT_EQ (compoundShape03, compoundShape01->getShapeById ("c3"));
        ASSERT_EQ (ellipse1i3maj2mio, compoundShape01->getShapeById ("e1"));
        ASSERT_EQ (rectangle2i2l2h, compoundShape01->getShapeById ("r2"));

        compoundShape01->deleteShapeById ("c2");

        ASSERT_EQ (rectangle1i3l4h, compoundShape01->getShapeById ("r1"));
        ASSERT_EQ (rectangle2i2l2h, compoundShape01->getShapeById ("r2"));

        try {
                compoundShape01->deleteShapeById ("e1");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Expected delete shape but shape not found", e);
        }

        try {
                compoundShape01->deleteShapeById ("c3");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Expected delete shape but shape not found", e);
        }

        try {
                compoundShape01->deleteShapeById ("t1");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Expected delete shape but shape not found", e);
        }

        try {
                compoundShape01->deleteShapeById ("c2");
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Expected delete shape but shape not found", e);
        }

        ASSERT_NEAR (22, compoundShape01->perimeter (), 0.001);

        delete compoundShape03;
        delete compoundShape02;
        delete compoundShape01;
}
