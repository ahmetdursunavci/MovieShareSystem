//
// Created by hp on 1.12.2020.
//

#include "ReadFromFile.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "LibrarySystem.h"

using namespace std;

string path;
string path2;



ReadFromFile::ReadFromFile(string file_path,string file_path2)  {
    path=file_path;
    path2=file_path2;
}
LibrarySystem Library_System;
void ReadFromFile::write(string output) {
    ofstream outfile;
    outfile.open(path2, ios_base::app);
    outfile << output;

    if(output=="Game Over!\n"){
        outfile.close();
    }
}

void ReadFromFile::Reading() {
    write("===Movie Library System===\n");
    fstream file(path);
    string command;
    string command2;
    if (!file) {
        printf("file does not exist");
    } else {
        while (file.good()) {
            getline(file, command);
            string array[4];

            char commandarray[command.length()];

            strcpy(commandarray, command.c_str());

            char split[] = "\t";

            char *str = strtok(commandarray, "\t");

            int i = 0;
            while (str) {

                array[i] = str;

                str = strtok(NULL, split);

                i++;
            }
            if(array[0]=="addUser") {
                if(command2!="===addUser() method test===") {
                    write("\n===addUser() method test===\n");
                    command2="===addUser() method test===";
                }

                const  int userId=stoi(array[1]);
                const string userName=array[2];

                Library_System.add_user(userId,userName,path2);

            }
            else if(array[0]=="deleteUser") {
                if(command2!="===deleteUser() method test===") {
                    write( "\n===deleteUser() method test===\n");
                    command2 = "===deleteUser() method test===";
                }

               const int userId=stoi(array[1]);

                Library_System.delete_user(userId,path2);

            }
            else if(array[0]=="showUser") {
                if(command2!="===showUser() method test===") {
                    write("\n===showUser() method test===\n");
                    command2 = "===showUser() method test===";
                }

                const  int userId=stoi(array[1]);

                Library_System.show_user(userId,path2);

            }
            else if(array[0]=="addMovie") {
                if(command2!="===addMovie() method test===") {
                    write("\n===addMovie() method test===\n");
                    command2 = "===addMovie() method test===";
                }

                const int movieId=stoi(array[1]);
                const string title = array[2];
                const int year = stoi(array[3]);

                Library_System.add_movie(movieId,title,year,path2);

            }
            else if(array[0]=="deleteMovie") {
                if(command2!="===deleteMovie() method test===") {
                write("\n===deleteMovie() method test===\n");
                command2="===deleteMovie() method test===";

                }

                const int movieId=stoi(array[1]);

                Library_System.delete_movie(movieId,path2);

            }
            else if(array[0]=="checkoutMovie") {
                if(command2!="checkoutMovie() method test===") {
                    write( "\n===checkoutMovie() method test===\n");
                    command2="checkoutMovie() method test===";
                }

                const int movieId = stoi(array[1]);
                const int userId = stoi(array[2]);
                Library_System.check_out(movieId,userId,path2);

            }
            else if(array[0]=="showMovie") {
                if(command2!="===showMovie() method test===") {
                    write( "\n===showMovie() method test===\n");
                    command2="===showMovie() method test===";

                }

                const int movieId = stoi(array[1]);

                Library_System.show_movie(movieId,path2);

            }
            else if(array[0]=="showAllMovie") {
                if(command2!="===showAllMovie() method test===") {
                    write( "\n===showAllMovie() method test===\n");
                    write( "Movie id - Movie name - Year - Status\n");
                    command2="===showAllMovie() method test===";
                }
                Library_System.show_all_movies(path2);

            }
            else if(array[0]=="returnMovie") {
                if(command2!="===returnMovie() method test===") {
                    write( "\n===returnMovie() method test===\n");
                    command2 = "===returnMovie() method test===";
                }

                const int movieId = stoi(array[1]);

                Library_System.return_movie(movieId,path2);

            }

        }

    }
}



