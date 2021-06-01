#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "hashTable.h"
#include "timer.h"
using namespace std;

// We create a 2-D array of some big size, and assume that the grid
// read in will be less than this size (a valid assumption for lab 6)
#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];
hashTable dic;
vector<string> outputs;

// Forward declarations
bool readInGrid(string filename, int& rows, int& cols);
string getWordInGrid(int startRow, int startCol, int dir, int len,
                     int numRows, int numCols);
bool readInDic(string filename);
bool sethtable(string filename);

int main(int argc, char* argv[]) {
  timer t;
  string file(argv[2]);
  string dict(argv[1]);
  //  argv[1] >> dict;
  //  argv[2] >> file;
    // to hold the number of rows and cols in the input file
    int rows, cols;
    // attempt to read in the file
    bool result = readInGrid(file, rows, cols);
    result = sethtable(dict);
    result = readInDic(dict);
    t.start();
    string dir;
    string word;
    string output;
    int count = 0;
    bool repeat = false;
    for (int rs = 0; rs < rows; rs++) {
      for (int cs = 0; cs < cols; cs++) {
	for (int d = 0; d < 8; d++) {
	  for (int b = 3; b < 23; b++) {
	    word = getWordInGrid(rs, cs, d, b, rows, cols);
	    if (!dic.prefix(word)) {
	      break;
	    }
	    if (word.length() > 2) {
	      if (dic.contains(word)) {
		if (d == 0) {
		  dir = "N ";
		} else if (d == 1) {
		  dir = "NE";
		} else if (d == 2) {
		  dir = "E ";
		} else if (d == 3) {
		  dir = "SE";
		} else if (d == 4) {
		  dir = "S ";
		} else if (d == 5) {
		  dir = "SW";
		} else if (d == 6) {
		  dir = "W ";
		} else {
		  dir = "NW";
		}
		repeat = false;
		output = dir + "(" + to_string(rs) + ", " + to_string(cs) + "):       " + word;
		for (int i = 0; i < outputs.size(); i++) {
		  if (outputs[i] == output) {
		    repeat = true;
		  }
		}
		if (!repeat) {
		  outputs.push_back(output);
		  cout << output << endl;
		  count += 1;
		}
	      }
	    }
	  }	  
	}
      }
    }
    cout << count << " words found" << endl;
    t.stop();
    //cout << "Found all words in " << t.getTime() << " seconds" << endl;
    //cout << (trunc(t.getTime()*1000)) << endl;
    return 0;
}
bool sethtable(string filename) {
  // try to open the file
  ifstream file(filename);

  int count = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
  hashTable h(count+10);
  dic = h;

  // close the file
  file.close();
  return true;
}

bool readInDic(string filename) {
  // try to open the file
  ifstream file(filename);
  string ins;

  while(getline(file, ins)) {
    dic.insert(ins);
  }

  // close the file
  file.close();
  return true;
}

bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
    ifstream file(filename);

    file >> rows;

    // then the columns
    file >> cols;

    // and finally the grid itself
    string data;
    file >> data;

    // close the file
    file.close();


    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
        }
    }
    return true;
}


string getWordInGrid (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {

    static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= numCols || r >= numRows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }

    return output;
}

