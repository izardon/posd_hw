#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "terminal.h"

using namespace std;

/*
 * argv[0]: The path of binary file.
 * argv[1]: The full name of input file.
 * argv[2]: The full name of output file.
 * argv[3]: The feature of shape that sorting basis on.
 * argv[4]: The 'inc' for increasing, 'dec' for decreasing.
 */
int main (int argc, char **argv)
{
        try {
                if (argc != 5) {
                        throw string ("Number of arg error!");
                }
                std::vector<std::string> argList (argv, argv + argc);
                string inputPath = argList [1];
                string outputPath = argList [2];
                string orderBy = argList [3];
                string orderPower = argList [4];

                string line;
                ifstream inputfile (inputPath);
                ostringstream stream;
                string inputStr;

                if (inputfile.is_open ()) {
                        while (getline (inputfile, line)) {
                                stream << line << endl;
                        }
                        inputfile.close ();
                        stream << " " << orderBy << " " << orderPower;
                        inputStr = stream.str ();
                        string::size_type pos = 0;

                        while ((pos = inputStr.find ("\r\n", pos)) != string::npos) {
                                inputStr.replace (pos, 2, " ");
                        }
                }
                else {
                        throw(string ("Input file is not exist!"));
                }

                Terminal terminal (inputStr);

                fstream outputfile (outputPath);
                string outputStr = terminal.showResult ();

                if (outputfile.is_open ()) {
                        outputfile << outputStr;
                        outputfile.close ();
                }
                else {
                        throw(string ("Output file is not exist!"));
                }
        }
        catch (string message) {
                cout << message << endl;
        }

        return 0;
}
