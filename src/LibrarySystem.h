//
// Created by hp on 1.12.2020.
//

#ifndef ASSIGNMENT2_LIBRARYSYSTEM_H
#define ASSIGNMENT2_LIBRARYSYSTEM_H

#include <iostream>

using namespace std;

class LibrarySystem {
public:

    void write(string output,string path);


    void add_movie( const int movieId, const string movieTitle, const int year,string path );

    void add_checked_movie( const int movieId, const string movieTitle, const int year,const int userId,string payh );

    void delete_movie( const int movieId,string path );

    void add_user( const int userId, const string userName,string path );

    void delete_user( const int userId,string path );

    void delete_users_movie(int userId);

    void show_user( const int userId ,string path);

    void check_out( const int movieId, const int userId,string path );

    int check_out_control(int movieId) ;

    string return_movie( const int movieId,string path );

    void return_added_movie( const int movieId, const string movieTitle, const int year );

    void show_all_movies(string path);

    void show_movie( const int movieId,string path );






};


#endif //ASSIGNMENT2_LIBRARYSYSTEM_H
