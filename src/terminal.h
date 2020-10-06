#ifndef TERMINAL_H
#define TERMINAL_H

#include <gtest/gtest.h>
#include <regex>
#include "shape.h"
#include "sort.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"

using namespace std;

class Terminal {
public:

Terminal()
{
}

Terminal(string input)
{
        vector<string> inputVector = splitInput (input);
        //正常運作在 featureToSort 跟 order 之間只有一個空白 ex: area inc
        string order = trim (inputVector.at (inputVector.size () - 1));
        string featureToSort = trim (inputVector.at (inputVector.size () - 2));

        if (!((order.compare ("inc") == 0 || order.compare ("dec") == 0) &&
              (featureToSort.compare ("area") == 0 || featureToSort.compare ("perimeter") == 0))) {
                throw string ("invalid input");
        }

        int idx = 0;

        for (auto shapeStr: inputVector) {
                if (isShapeRegexValidation (shapeStr, idx)) {
                        addShape (shapeStr);
                }
                ++idx;
                if (idx == inputVector.size () - 2) break;
        }

        if (_shapesVector.size () == 0) {
                throw string ("invalid input");
        }

        setResult (featureToSort, order);
}

string showResult ()
{
        return _result;
}

void setResult (string featureToSort, string order)
{
        ostringstream stream;

        if (order.compare ("inc") == 0) {
                quickSort (_shapesVector.begin (), _shapesVector.end (), AscendingCompare (featureToSort));
        }
        else if (order.compare ("dec") == 0) {
                quickSort (_shapesVector.begin (), _shapesVector.end (), DescendingCompare (featureToSort));
        }

        for (auto shape: _shapesVector) {
                if (featureToSort.compare ("area") == 0) {
                        stream << fixed << setprecision (3) << shape->area ();
                }
                else if (featureToSort.compare ("perimeter") == 0) {
                        stream << fixed << setprecision (3) << shape->perimeter ();
                }

                if (shape != *(_shapesVector.end () - 1)) {
                        stream << "\n";
                }
        }

        _result = stream.str ();
}

string trim (string s)
{
        if (s.empty ()) {
                return s;
        }

        s.erase (0, s.find_first_not_of (" "));
        s.erase (s.find_last_not_of (" ") + 1);
        return s;
}

private:
string _result;
vector<Shape *> _shapesVector;

FRIEND_TEST (Terminal, SplitInput);
vector<string> splitInput (string inputStr)
{
        int begin = 0;
        vector<string> inputVector;

        while (inputStr.find (")") != string::npos) {
                string token = inputStr.substr (begin, inputStr.find (")") + 1);
                inputVector.push_back (token);
                inputStr = inputStr.substr (inputStr.find (")") + 1);
        }

        while (inputStr.find (" ") != string::npos) {
                string token = inputStr.substr (begin, inputStr.find (" ") + 1);
                inputVector.push_back (token);
                inputStr = inputStr.substr (inputStr.find (" ") + 1);
        }

        inputVector.push_back (inputStr);

        return inputVector;
}

FRIEND_TEST (Terminal, IsShapeRegexValidation);
bool isShapeRegexValidation (string shapeStr, int indexOfVector)
{
        //Floating Number regex: (-?\\d+)(\\.\\d+)?
        regex rectangleReg ("^Rectangle\\s+\\(\\s*(-?\\d+)(\\.\\d+)?\\s*\\,\\s*(-?\\d+)(\\.\\d+)?\\s*\\)$");
        regex ellipseReg ("^Ellipse\\s+\\(\\s*(-?\\d+)(\\.\\d+)?\\s*\\,\\s*(-?\\d+)(\\.\\d+)?\\s*\\)$");
        regex triangleReg ("^Triangle\\s+\\(\\s*\\[(-?\\d+)(\\.\\d+)?\\,(-?\\d+)(\\.\\d+)?\\]\\s*\\,\\s*\\[(-?\\d+)(\\.\\d+)?\\,(-?\\d+)(\\.\\d+)?\\]\\s*\\,\\s*\\[(-?\\d+)(\\.\\d+)?\\,(-?\\d+)(\\.\\d+)?\\]\\s*\\)$");

        if (indexOfVector > 0) {
                if (shapeStr.at (0) == ' ') {
                        shapeStr.erase (0, shapeStr.find_first_not_of (" "));
                }
                else {
                        return false;
                }
        }

        if (regex_match (shapeStr, rectangleReg) ||
            regex_match (shapeStr, ellipseReg) ||
            regex_match (shapeStr, triangleReg)) {
                return true;
        }

        return false;
}

FRIEND_TEST (Terminal, AddShape);
FRIEND_TEST (Terminal, SetResult);
void addShape (string shapeStr)
{
        string shapeNameStr;
        smatch match;
        regex shapeNameReg ("(Rectangle|Ellipse|Triangle)");

        while (std::regex_search (shapeStr, match, shapeNameReg)) {
                shapeNameStr = match.str ();
                shapeStr = match.suffix ().str ();
        }

        if (shapeNameStr.compare ("Rectangle") == 0) {
                addRectangle (shapeStr);
        }
        else if (shapeNameStr.compare ("Ellipse") == 0) {
                addEllipse (shapeStr);
        }
        else if (shapeNameStr.compare ("Triangle") == 0) {
                addTriangle (shapeStr);
        }
}

FRIEND_TEST (Terminal, AddRectangle);
void addRectangle (string shapeStr)
{
        vector<string> shapeParams;
        //Floating Number regex: (-?\\d+)(\\.\\d+)?
        regex paramsReg ("(-?\\d+)(\\.\\d+)?");
        smatch match;

        double l = 0;
        double w = 0;

        while (std::regex_search (shapeStr, match, paramsReg)) {
                shapeParams.push_back (match.str ());
                shapeStr = match.suffix ().str ();
        }

        l = stod (shapeParams.at (0));
        w = stod (shapeParams.at (1));

        try {
                _shapesVector.push_back (new Rectangle (l, w));
        } catch (string e) {
        }
}

FRIEND_TEST (Terminal, AddEllipse);
void addEllipse (string shapeStr)
{
        vector<string> shapeParams;
        //Floating Number regex: (-?\\d+)(\\.\\d+)?
        regex paramsReg ("(-?\\d+)(\\.\\d+)?");
        smatch match;

        double semiMajorAxes = 0;
        double semiMinorAxes = 0;

        while (std::regex_search (shapeStr, match, paramsReg)) {
                shapeParams.push_back (match.str ());
                shapeStr = match.suffix ().str ();
        }

        semiMajorAxes = stod (shapeParams.at (0));
        semiMinorAxes = stod (shapeParams.at (1));

        try {
                _shapesVector.push_back (new Ellipse (semiMajorAxes, semiMinorAxes));
        } catch (string e) {
        }
}

FRIEND_TEST (Terminal, AddTriangle);
void addTriangle (string shapeStr)
{
        vector<string> shapeParams;
        //Floating Number regex: (-?\\d+)(\\.\\d+)?
        regex paramsReg ("(-?\\d+)(\\.\\d+)?");
        smatch match;

        vector<TwoDimensionalCoordinate*> triangleVector;

        while (std::regex_search (shapeStr, match, paramsReg)) {
                shapeParams.push_back (match.str ());
                shapeStr = match.suffix ().str ();
        }

        triangleVector.push_back (new TwoDimensionalCoordinate (stod (shapeParams.at (0)), stod (shapeParams.at (1))));
        triangleVector.push_back (new TwoDimensionalCoordinate (stod (shapeParams.at (2)), stod (shapeParams.at (3))));
        triangleVector.push_back (new TwoDimensionalCoordinate (stod (shapeParams.at (4)), stod (shapeParams.at (5))));

        try {
                _shapesVector.push_back (new Triangle (triangleVector));
        } catch (string e) {
        }
}
};

#endif
