/*
 * Headstart for Assignment 2
 * CS 4420/5420
 * SS 2019/2020
 *
 * Student Name: Jeff Parker
 *
 *  Part 1 for Assignment 2: Simple skeleton bash
 *
 */

#include "parser.h"
#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <unistd.h>
using namespace std;

bool isBuiltIn(string input) {
  if (input == "exit") {
    return true;
  } else {
    return false;
  }
}

int main(int argc, char *argv[]) {
  string line;
  char *char_array;
  CommandData *data = new CommandData;
  string cwd = getcwd(NULL, 0);
  bool built_in;
  do {
    built_in = false;
    cout << endl << cwd << "> ";
    getline(cin, line);
    char_array = const_cast<char *>(line.c_str());
    ParseCommandLine(char_array, data);

    cout << "\nNumber of simple commands: " << data->numcommands << endl;
    for (int i = 0; i < data->numcommands; ++i) {
      cout << "command" << i + 1 << ": " << data->TheCommands[i].command
           << endl;
      built_in = isBuiltIn(data->TheCommands[i].command);
      for (int k = 0; k < data->TheCommands[i].numargs; ++k) {
        cout << "arg[" << k << "]: " << data->TheCommands[i].args[k] << endl;
      }
    }
    if (data->infile == NULL) {
      cout << "Input file: "
           << "(NULL)" << endl;
    } else {
      cout << "Input file: " << data->infile << endl;
    }
    if (data->outfile == NULL) {
      cout << "Output file: "
           << "(NULL)" << endl;
    } else {
      cout << "Output file: " << data->outfile << endl;
    }
    cout << "Background option: " << data->background << endl;
    cout << "Built-in command: " << built_in << endl;
  } while (built_in == 0);
  exit(0);
}
