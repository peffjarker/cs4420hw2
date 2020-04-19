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
#include <stdlib.h>
using namespace std;

bool isBuiltIn(string input) {
  if (input == "exit" || input == "cd"
      || input == "export" || input == "set"
      || input == "pwd") {
    return true;
  } else {
    return false;
  }
}

int main(int argc, char *argv[]) {
  bool debug = false;
  string line;
  string com;
  char *char_array;
  CommandData *data = new CommandData;
  bool built_in;
  do {
    string cwd = getcwd(NULL, 0);
    built_in = false;
    cout << endl << cwd << "> ";
    getline(cin, line);
    char_array = const_cast<char *>(line.c_str());
    ParseCommandLine(char_array, data);
    built_in = isBuiltIn(data->TheCommands[0].command);
    for (int i = 0; i < data ->numcommands; ++i) {
      if (data ->TheCommands[i].numargs == 0) {
        if (data -> infile == NULL) {
          string de = "DEBUG=yes";
          string bug = "DEBUG=no";
          if (data->TheCommands[i].command == de) {
            debug = true;
          } else if (data->TheCommands[i].command == bug) {
            debug = false;
          }
          system(data -> TheCommands[i].command);
        } else {
          fstream file;
          file.open(data->infile);
          if (file.is_open()) {
            while (getline(file,line) ) {
              cout << line << '\n';
            }
            file.close();
          } else {
            cout << "error opening file" << endl;
          }
        }
      } else {
        string args;
        for (int k = 0; k < data->TheCommands[i].numargs; ++k) {
          string arg(data->TheCommands[i].args[k]);
          args += " " + arg;
        }
        string command = data->TheCommands[i].command + args;
        system(command.c_str());
      }
    }

    if (debug == true) {
      cout << "\nDEBUG OUTPUT:" << endl;
      cout << "-----------------------------";
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
      cout << "-----------------------------";
    }
    com = data->TheCommands[0].command;
  } while (com != "exit");
  exit(0);
}
