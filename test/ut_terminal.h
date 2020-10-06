#include "../src/terminal.h"
#include "../src/shape.h"
#include "../src/rectangle.h"

using namespace std;

TEST(Terminal, ConstructorNoException) {
        ASSERT_NO_THROW(Terminal terminal("Rectangle (1, 1) area inc"));
}

TEST (Terminal, ExceptionForConstructor) {
        try {
                Terminal terminal("Ellipse (-1, -1) area inc");
                FAIL();
        } catch(string e) {
                ASSERT_EQ("invalid input", e);
        }
}

TEST (Terminal, ShowResult) {
        Terminal terminal01("Rectangle (2, 2) Rectangle (1, 1) Ellipse$%^&(1, 1) area inc");
        ASSERT_EQ("1.000\n4.000", terminal01.showResult());

        Terminal terminal02("Rectangle (2, 2) Rectangle (1, 1) Ellipse (-1, -1) area inc");
        ASSERT_EQ("1.000\n4.000", terminal02.showResult());

        Terminal terminal03("Rectangle (2, 2) Rectangle (1, 1) Ellipse (-1, -1) perimeter dec");
        ASSERT_EQ("8.000\n4.000", terminal03.showResult());
}

TEST (Terminal, Trim) {
        Terminal terminal;
        ASSERT_EQ("area", terminal.trim("   area  "));
}

TEST (Terminal, SplitInput) {
        Terminal terminal;
        vector<string> assert01 = {"Rectangle (2, 2)", " Rectangle (1, 1)", " ", "area ", "inc"};
        ASSERT_EQ(assert01, terminal.splitInput("Rectangle (2, 2) Rectangle (1, 1) area inc"));

        vector<string> assert02 = {"Rectangle (2, 2)", " Ellipse$%^&(1, 1)", " ", "area ", "inc"};
        ASSERT_EQ(assert02, terminal.splitInput("Rectangle (2, 2) Ellipse$%^&(1, 1) area inc"));

        vector<string> assert03 = {"Rectangle (2, 2)", " ", "Ellipse$%^&(1, ", "1 ", "area ", "inc"};
        ASSERT_EQ(assert03, terminal.splitInput("Rectangle (2, 2) Ellipse$%^&(1, 1 area inc"));

        vector<string> assert04 = {"Rectangle (2, 2)", " Ellipse$%^&1, 1)", " ", "area ", "inc"};
        ASSERT_EQ(assert04, terminal.splitInput("Rectangle (2, 2) Ellipse$%^&1, 1) area inc"));

        vector<string> assert05 = {"Rectangle (2, 2)", "Rectangle (1, 1)", " ", "area ", "inc"};
        ASSERT_EQ(assert05, terminal.splitInput("Rectangle (2, 2)Rectangle (1, 1) area inc"));
}

TEST (Terminal, IsShapeRegexValidation) {
        Terminal terminal;
        ASSERT_EQ(true, terminal.isShapeRegexValidation("Rectangle (2, 2)", 0));
        ASSERT_EQ(true, terminal.isShapeRegexValidation("Rectangle (2.96485, 0.123456)", 0));
        ASSERT_EQ(true, terminal.isShapeRegexValidation("Rectangle      (2, 2)", 0));
        ASSERT_EQ(true, terminal.isShapeRegexValidation("Rectangle (2,2)", 0));
        ASSERT_EQ(true, terminal.isShapeRegexValidation("    Rectangle (1, 2)", 1));
        ASSERT_EQ(true, terminal.isShapeRegexValidation("Triangle ([0,-3], [-3,0], [0,-4])", 0));
        ASSERT_EQ(true, terminal.isShapeRegexValidation("Rectangle (2.96485, -0.123456)", 0));
        ASSERT_EQ(true, terminal.isShapeRegexValidation("Rectangle (0, 0.123456)", 0));

        ASSERT_EQ(false, terminal.isShapeRegexValidation("rectangle (2, 2)", 0));
        ASSERT_EQ(false, terminal.isShapeRegexValidation("Rectangle(2! 2)", 0));
        ASSERT_EQ(false, terminal.isShapeRegexValidation("   Rectangle (2,2)", 0));
}

TEST (Terminal, AddShape) {
        Terminal terminal;
        terminal.addShape("Rectangle (2, 2)");
        terminal.addShape("Ellipse (4, 3)");
        terminal.addShape("Triangle ([0,0], [3,0], [0,4])");
        ASSERT_EQ(3, terminal._shapesVector.size());
}

TEST (Terminal, AddRectangle) {
        Terminal terminal;
        terminal.addRectangle("Rectangle (2, 2)");
        ASSERT_EQ(1, terminal._shapesVector.size());
}

TEST (Terminal, AddEllipse) {
        Terminal terminal;
        terminal.addEllipse("Ellipse (4, 3)");
        ASSERT_EQ(1, terminal._shapesVector.size());
}

TEST (Terminal, AddTriangle) {
        Terminal terminal;
        terminal.addTriangle("Triangle ([0,0], [3,0], [0,4])");
        ASSERT_EQ(1, terminal._shapesVector.size());
}

TEST (Terminal, SetResult) {
        Terminal terminal("Rectangle (1, 1) Rectangle (2, 2) area inc");

        terminal.setResult("area", "inc");
        ASSERT_EQ("1.000\n4.000", terminal._result);

        terminal.setResult("area", "dec");
        ASSERT_EQ("4.000\n1.000", terminal._result);

        terminal.setResult("perimeter", "inc");
        ASSERT_EQ("4.000\n8.000", terminal._result);

        terminal.setResult("perimeter", "dec");
        ASSERT_EQ("8.000\n4.000", terminal._result);
}

TEST (Terminal, InvalidInputNoShape) {
        try {
                Terminal terminal("a area inc");
                FAIL();
        } catch(string e) {
                ASSERT_EQ("invalid input", e);
        }
}

TEST (Terminal, InvalidInputShapeLowerCap) {
        try {
                Terminal terminal("rectangle (1, 1) area inc");
                FAIL();
        } catch(string e) {
                ASSERT_EQ("invalid input", e);
        }
}

TEST (Terminal, InvalidInputShapeNoSpace) {
        try {
                Terminal terminal("Rectangle(1, 1) area inc");
                FAIL();
        } catch(string e) {
                ASSERT_EQ("invalid input", e);
        }
}

TEST (Terminal, InvalidInputNoFeatureToSort) {
        try {
                Terminal terminal("Rectangle (1, 1)  inc");
                FAIL();
        } catch(string e) {
                ASSERT_EQ("invalid input", e);
        }
}

TEST (Terminal, InvalidInputNoOrder) {
        try {
                Terminal terminal("Rectangle (1, 1) area");
                FAIL();
        } catch(string e) {
                ASSERT_EQ("invalid input", e);
        }
}

TEST (Terminal, AreaIncreasingWithOneShapeExceptionIgnore) {
        ASSERT_NO_THROW(Terminal terminal("Rectangle (1, 1) Rectangle!@#1, 1) area inc"));
}

TEST (Terminal, AreaIncreasingWithOneShapeErrorArgumentIgnore) {
        ASSERT_NO_THROW(Terminal terminal("Rectangle (1, 1) Rectangle (-1, 1) area inc"));
}
