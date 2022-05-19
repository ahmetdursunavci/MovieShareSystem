//
// Created by hp on 1.12.2020.
//

#include "LibrarySystem.h"
#include "ReadFromFile.h"
#include <iostream>
#include <fstream>
using namespace std;



void LibrarySystem::write(string output,string path) {
        ofstream outfile;
        outfile.open(path, ios_base::app);
        outfile << output;

        if(output=="Game Over!\n"){
            outfile.close();
    }
}




struct CheckedOutMovie{
    CheckedOutMovie *next;

    int movieId;
    string movieTitle;
    int year;

};

struct User{
    User *next;
    User *prev;

    int userId;
    string userName;

    CheckedOutMovie *movie;

}*User_head;

User *check_user;

struct Not_Checked_Out_Movie {
    Not_Checked_Out_Movie *next;

    int movieId;
    string movieTitle;
    int year;

}*ncm_head;

void LibrarySystem::add_movie( const int movieId, const string movieTitle, const int year,string path ) {
/* in this method i controlled my linked either empty or full, after that I filled the linked list
 * if it is empty I made head equal added elements, after that if the second element add my linked list works like that:
 * first two elements are my edge elements other elements which are added are middle elements of my linked list*/

    User *temp_user=User_head;
    bool kontrol=false;
    if(temp_user!=NULL) {
        do{
            CheckedOutMovie *temp_cm=temp_user->movie;
            if(temp_cm!=NULL) {
                do {
                    if(temp_cm->movieId==movieId) {
                        kontrol=true;
                        break;
                    }
                    temp_cm=temp_cm->next;
                }while (temp_cm!=temp_user->movie);
            }
            temp_user=temp_user->next;
        }while (temp_user!=User_head);
    }
    if(kontrol) {
        write("Movie "+ to_string(movieId)+ " already exists\n",path);
        return;
    }

    Not_Checked_Out_Movie *movie =  new Not_Checked_Out_Movie();

    movie->movieId=movieId;
    movie->movieTitle=movieTitle;
    movie->year=year;
    movie->next=NULL;

    if(ncm_head==NULL) {
        ncm_head=movie;
        ncm_head->next=ncm_head;
       write("Movie " +to_string(movieId)+ " has been added\n",path);
    }
    else {
        if(ncm_head->next==ncm_head) {
            if(ncm_head->movieId==movie->movieId) {
                write("Movie "+ to_string(movieId)+ " already exists\n",path);
                return;
            }
            else {
                movie->next = ncm_head;
                ncm_head->next = movie;
                ncm_head = movie;
                write("Movie "+ to_string(movieId)+ " has been added\n",path);
            }
        }
        else {
            Not_Checked_Out_Movie *temp = ncm_head;
            do {
                if(temp->movieId==movieId) {
                    write("Movie "+ to_string(movieId)+ " already exists\n",path);
                    return;
                }
                else {
                    temp=temp->next;
                }
            }while (temp!=ncm_head);

            movie->next=ncm_head->next;
            ncm_head->next=movie;
            write("Movie "+ to_string(movieId)+ " has been added\n",path);
        }
    }
}

void LibrarySystem::add_user(const int userId, const string userName,string path) {
    /* I implemented same algorithm with add_movie method but since this is doubly linked list
     * I always chechk prev pointer*/

    User *user = new User();
    user->userId=userId;
    user->userName=userName;

    user->next=NULL;
    user->prev=NULL;
    user->movie=NULL;

    if(User_head==NULL) {
        User_head=user;
        User_head->next=user;
        User_head->prev=user;
        write("User " + to_string(userId)+ " has been added\n",path);
    }
    else {
        if(User_head->next==User_head) {
            if(User_head->userId==userId) {
                write("User " + to_string(userId)+ " already exist\n",path);
                return;
            }
            else {
            user->next=User_head;
            user->prev=User_head;
            User_head->next=user;
            User_head->prev=user;
            User_head=user;
                write("User " + to_string(userId)+ " has been added\n",path);
            }

        }
        else {
            User *temp = User_head;
            do{
                if(temp->userId==userId) {
                    write("User " + to_string(userId)+ " already exist\n",path);
                    return;
                }
                else {
                    temp=temp->next;
                }

            }while (temp!=User_head);

            user->next = User_head->next;
            user->prev = User_head;
            User_head->next->prev=user;
            User_head->next=user;
            write("User " + to_string(userId)+ " has been added\n",path);

        }
    }



}
void LibrarySystem::add_checked_movie( const int movieId, const string movieTitle, const int year, const int userId,string path ) {
    /* this is my helper method, my code below check the movies, after that I call this method to add user's movie
     * linkedlist*/

    CheckedOutMovie *movie =  new CheckedOutMovie();

    movie->movieId=movieId;
    movie->movieTitle=movieTitle;
    movie->year=year;
    movie->next=NULL;

    User *temp = User_head;
    do{
        if(temp->userId==userId) {
            break;
        }
        else {
            temp=temp->next;
        }
    }while(temp!=User_head);


    if(temp->movie==NULL) {
        temp->movie=movie;
        temp->movie->next=temp->movie;
        write("Movie "+to_string( movieId)+" has been checked out by User "+to_string(temp->userId)+"\n",path);
    }
    else {
        if(temp->movie->next==temp->movie) {

                movie->next = temp->movie;
                temp->movie->next = movie;
                temp->movie = movie;
            write("Movie "+to_string( movieId)+" has been checked out by User "+to_string(temp->userId)+"\n",path);

        }
        else {
            movie->next=temp->movie->next;
            temp->movie->next=movie;
            write("Movie "+to_string( movieId)+" has been checked out by User "+to_string(temp->userId)+"\n",path);
        }
    }
}
int LibrarySystem::check_out_control(int movieId) {
    /*there are two probability when we check movies, firstone is movies may be in Not check library,
     * secondone is movie may have been checked already, lastone is film may not exist. My this method control these probability
     * after that return int(firstone=0,secondone=1,lastone=2)*/

    Not_Checked_Out_Movie *temp_ncm=ncm_head;
    do {
        if(temp_ncm->movieId==movieId) {
            return 0;
        }
        else {
            temp_ncm=temp_ncm->next;
        }
    }while(temp_ncm!=ncm_head);

    User *temp_user = User_head;
    do {
        CheckedOutMovie *temp_cm=temp_user->movie;
        if(temp_cm!=NULL) {
            do {
                if (temp_cm->movieId == movieId) {
                    check_user=temp_user;
                    return 1;
                } else {
                    temp_cm=temp_cm->next;
                }
            }while(temp_cm!=temp_user->movie);
        }
        temp_user=temp_user->next;
    }while(temp_user!=User_head);

    return 2;

}
void LibrarySystem::check_out(const int movieId, const int userId,string path) {
    /* number which came from check_control method are read, after that implement these 3 probability which ı mentioned
     * above*/

    User *temp_users = User_head;
    bool a=true;
    do{
        if(temp_users->userId==userId) {
            a=false;
            break;
        }
        temp_users=temp_users->next;
    }while(temp_users!=User_head);
    if(a) {
        write("User "+to_string( userId)+" does not exist for checked out\n",path);
        return;
    }
    int control = check_out_control(movieId);

    if(control==0) {
        Not_Checked_Out_Movie *temp = ncm_head;
        Not_Checked_Out_Movie *prev=NULL;
        if(temp->movieId==movieId) {
            add_checked_movie(temp->movieId,temp->movieTitle,temp->year,userId,path);
            do {
                if(temp->next==ncm_head) {
                    prev=temp;
                    break;
                }
                temp=temp->next;
            }while(temp!=ncm_head);
            prev->next=ncm_head->next;
            free(ncm_head);
            ncm_head=prev->next;
            return;
        }
        prev=temp;
        temp=temp->next;
        do{
            if(temp->movieId==movieId) {
                break;
            }
            else {
                prev=prev->next;
                temp=temp->next;
            }
        }while(temp!=ncm_head);

        add_checked_movie(temp->movieId,temp->movieTitle,temp->year,userId,path);
        prev->next=temp->next;
        free(temp);


    }
    else if(control==1) {
        write("User "+to_string( movieId)+" does not exist for checked out\n",path);

    }
    else if(control==2) {
        write("User "+to_string( movieId)+" does not exist for checked out\n",path);
    }

}

void LibrarySystem::show_movie(const int movieId,string path) {
    /* I control two libraries firstone is not check ,secondone is user's check after that return their datases*/

    Not_Checked_Out_Movie *temp_ncm = ncm_head;
    bool control=false;
    if(temp_ncm!=NULL) {
        do{
            if(temp_ncm->movieId==movieId) {
                control=true;
                break;
            }
            temp_ncm=temp_ncm->next;
        }while(temp_ncm!=ncm_head);

    }
    if(control) {
        write(to_string(temp_ncm->movieId)+" "+temp_ncm->movieTitle+" "+to_string(temp_ncm->year)+" Not checked out\n",path);
        return;

    }
    else {
        User *temp_user=User_head;
        do {
            if(temp_user->movie!=NULL) {
                CheckedOutMovie *temp_cm = temp_user->movie;
                do {
                    if(temp_cm->movieId==movieId) {

                        write(to_string(temp_cm->movieId)+" "+temp_cm->movieTitle+" "+to_string(temp_cm->year)+" Checked out by User "+to_string(temp_user->userId)+"\n",path);
                        return;
                    }
                    temp_cm=temp_cm->next;
                }while (temp_cm!=temp_user->movie);
            }
            temp_user=temp_user->next;
        }while (temp_user!=User_head);

        write("Movie with the id "+to_string(movieId)+" does not exist\n",path);
        return;

    }

}

void LibrarySystem::show_all_movies(string path) {
    Not_Checked_Out_Movie *temp_ncm = ncm_head;
    User *temp_user = User_head;

    if(temp_ncm!=NULL) {
        do{
            write(to_string(temp_ncm->movieId)+" "+temp_ncm->movieTitle+" "+to_string(temp_ncm->year)+" Not checked out\n",path);;
            temp_ncm=temp_ncm->next;
        }while(temp_ncm!=ncm_head);
    }

    do {
        CheckedOutMovie *temp_cm = temp_user->movie;
        if(temp_cm!=NULL) {
            do {
                write(to_string(temp_cm->movieId)+" "+temp_cm->movieTitle+" "+to_string(temp_cm->year)+" Checked out by User "+to_string(temp_user->userId)+"\n",path);
                temp_cm=temp_cm->next;
            }while(temp_cm!=temp_user->movie);
        }
        temp_user=temp_user->next;
    }while(temp_user!=User_head);



}

void LibrarySystem::show_user(const int userId,string path) {
        User *temp_user = User_head;
        bool a =true;
        do {
            if (temp_user->userId==userId) {
                a= false;
                write("User id: "+to_string(temp_user->userId)+" User name: "+temp_user->userName+"\n",path);
                write("User "+to_string(temp_user->userId)+" checked out the following Movies:\n",path);
                CheckedOutMovie *temp_cm=temp_user->movie;
                if(temp_cm!=NULL) {
                    write("Movie id - Movie name - Year\n",path);
                    do {
                        write(to_string(temp_cm->movieId)+" "+temp_cm->movieTitle+" "+to_string(temp_cm->year)+"\n",path);
                        temp_cm=temp_cm->next;
                    }while (temp_cm!=temp_user->movie);
                }
            }
            temp_user=temp_user->next;
        }while (temp_user!=User_head);

    if(a) {
        write("User "+to_string( userId)+" does not exist\n",path);
    }


}

void LibrarySystem::delete_movie(const int movieId,string path) {

        Not_Checked_Out_Movie *temp_ncm = ncm_head;

        if(ncm_head!=NULL) {
            if(temp_ncm->movieId==movieId) {
                if(ncm_head->next==ncm_head) {
                    free(temp_ncm);
                    ncm_head=NULL;
                    write("Movie "+to_string(movieId)+" has not been checked out\nMovie "+to_string(movieId)+" has been deleted\n",path);
                    return;

                }
                else {
                    Not_Checked_Out_Movie *last = NULL;
                    Not_Checked_Out_Movie *temp_ncm2=temp_ncm;
                    do {
                        if(temp_ncm2->next==ncm_head) {
                            last=temp_ncm2;
                            temp_ncm2=temp_ncm2->next;
                            break;
                        }
                        temp_ncm2=temp_ncm2->next;
                    }while (temp_ncm2!=ncm_head);
                    last->next=ncm_head->next;
                    ncm_head=ncm_head->next;
                    free(temp_ncm);
                    write("Movie "+to_string(movieId)+" has not been checked out\nMovie "+to_string(movieId)+" has been deleted\n",path);
                    return;
                }
            }
            else {
                bool a = false;
                Not_Checked_Out_Movie *prev = temp_ncm;
                temp_ncm=temp_ncm->next;
                do {
                    if(temp_ncm->movieId==movieId) {
                        a= true;
                        break;
                    }
                    temp_ncm=temp_ncm->next;
                    prev=prev->next;
                }while (temp_ncm!=ncm_head);
                if(a) {
                    prev->next=temp_ncm->next;
                    free(temp_ncm);
                    write("Movie "+to_string(movieId)+" has not been checked out\nMovie "+to_string(movieId)+" has been deleted\n",path);
                    return;
                }
            }
        }
        if(User_head!=NULL) {
            User *temp_user=User_head;
            int user_id;
            CheckedOutMovie *checked_movie=NULL;
            bool a=false;

            do{
                CheckedOutMovie *temp_cm=temp_user->movie;
                if(temp_cm!=NULL) {
                    if(temp_cm->movieId==movieId) {
                        if(temp_user->movie->next==temp_user->movie) {

                                temp_user->movie=NULL;
                                free(temp_cm);
                            write("Movie "+to_string(movieId)+" has been checked out\nMovie "+to_string(movieId)+" has been deleted\n",path);
                                return;

                        }
                        else {
                            CheckedOutMovie *prev=temp_cm;
                            temp_cm=temp_cm->next;
                            do{
                                if(temp_cm->next==temp_user->movie) {
                                    a= true;
                                    break;
                                }
                                temp_cm=temp_cm->next;
                                prev=prev->next;


                            }while(temp_cm!=temp_user->movie);
                            if(a) {
                                prev->next=temp_cm->next;
                                temp_user->movie=temp_user->movie->next;
                                free(temp_cm);
                                write("Movie "+to_string(movieId)+" has been checked out\nMovie "+to_string(movieId)+" has been deleted\n",path);
                                return;
                            }
                        }



                    }
                    else {
                        CheckedOutMovie *prev = temp_cm;
                        temp_cm=temp_cm->next;
                        do {
                          if(temp_cm->movieId==movieId) {
                              a= true;
                              break;
                          }
                          temp_cm=temp_cm->next;
                          prev=prev->next;


                        }while (temp_cm!=temp_user->movie);
                        if(a) {
                            prev->next=temp_cm->next;
                            free(temp_cm);
                            write("Movie "+to_string(movieId)+" has been checked out\nMovie "+to_string(movieId)+" has been deleted\n",path);
                            return;

                        }


                    }

                }

                temp_user=temp_user->next;
            }while (temp_user!=User_head);
        }

    write("Movie "+to_string(movieId)+" does not exist\n",path);


}
void LibrarySystem::delete_users_movie(int userId) {

    /* I use these method to avoid memory leak*/
    User *temp_user=User_head;
    do {
        if(temp_user->userId==userId) {
            break;
        }
        temp_user=temp_user->next;
    }while (temp_user!=User_head);

    if(temp_user->movie!=NULL) {
        CheckedOutMovie *temp_cm = temp_user->movie;
        while (temp_user->movie!=NULL) {
            temp_user->movie=temp_user->movie->next;
            free(temp_cm);
            temp_cm=temp_user->movie;

        }

    }

}

void LibrarySystem::delete_user(const int userId,string path) {
        User *temp_user=User_head;
        if(User_head==NULL) {
            write("User "+to_string(userId)+" does not exist\n",path);
            return;
        }
        bool control = false;
        do{
            if(temp_user->userId == userId) {
                control= true;
                break;
            }
            temp_user=temp_user->next;
        }while (temp_user!=User_head);

        if(control) {
            delete_users_movie(userId);

            if(temp_user==User_head) {
                if(User_head->next==User_head) {
                    free(temp_user);
                    User_head=NULL;

                }
                else {
                    User_head->prev->next = User_head->next;
                    User_head->next->prev = User_head->prev;
                    User_head = User_head->next;
                    free(temp_user);
                }
            }
            else {
                temp_user->next->prev=temp_user->prev;
                temp_user->prev->next=temp_user->next;
                free(temp_user);
            }
            write("User "+to_string(userId)+" has been deleted\n",path);
            return;



        }
        else {
            write("User "+to_string(userId)+" has been deleted\n",path);
        }

}

string LibrarySystem::return_movie(const int movieId,string path) {
        Not_Checked_Out_Movie *temp_ncm=ncm_head;

        if(temp_ncm!=NULL) {
            do {
                if(temp_ncm->movieId==movieId) {
                    write("Movie "+to_string(movieId)+" has not been checked out\n",path);
                    return temp_ncm->movieTitle;
                }
                temp_ncm=temp_ncm->next;


            }while (temp_ncm!=ncm_head);
        }
        User *temp_user=User_head;
        CheckedOutMovie *movie_head;
        CheckedOutMovie *delete_movie;
        bool a=false;
        if(temp_user!=NULL) {
            do {
                CheckedOutMovie *temp_cm=temp_user->movie;
                if(temp_cm!=NULL) {
                    do {
                        if(temp_cm->movieId==movieId) {
                            a= true;
                            movie_head=temp_user->movie;
                            delete_movie=temp_cm;
                            break;
                        }
                        temp_cm=temp_cm->next;
                    }while (temp_cm!=temp_user->movie);
                }

                temp_user=temp_user->next;
            }while (temp_user!=User_head);
        }

        if(a) {
            CheckedOutMovie *temp_cm=movie_head;
            if(movie_head==delete_movie) {
                if (movie_head->next == movie_head) {
                    string b = movie_head->movieTitle;
                    write("Movie "+to_string(movieId)+" has been returned\n",path);
                    return_added_movie(movie_head->movieId,movie_head->movieTitle,movie_head->year);
                    free(movie_head);
                    return b;

                } else {
                    do {
                        if (temp_cm->next == movie_head) {
                            break;
                        }
                        temp_cm=temp_cm->next;
                    } while (temp_cm != movie_head);
                    string b = delete_movie->movieTitle;
                    temp_cm->next=movie_head->next;
                    movie_head=temp_cm->next;
                    return_added_movie(delete_movie->movieId,delete_movie->movieTitle,delete_movie->year);
                    free(delete_movie);
                    write("Movie "+to_string(movieId)+" has been returned\n",path);
                    return b;

                }
            }
            else {
                CheckedOutMovie *prev=movie_head;
                CheckedOutMovie *temp_cm=movie_head->next;
                do {
                    if(temp_cm==delete_movie) {
                        break;
                    }
                    prev=prev->next;
                    temp_cm=temp_cm->next;
                }while (temp_cm!=movie_head);

                prev->next=delete_movie->next;
                string b = delete_movie->movieTitle;
                return_added_movie(delete_movie->movieId,delete_movie->movieTitle,delete_movie->year);
                free(delete_movie);
                write("Movie "+to_string(movieId)+" has been returned\n",path);
                return b;

            }

        }
        write("Movie "+to_string(movieId)+" not exist in the library\n",path);


return "";

}

void LibrarySystem::return_added_movie( const int movieId, const string movieTitle, const int year ) {

    Not_Checked_Out_Movie *movie =  new Not_Checked_Out_Movie();

    movie->movieId=movieId;
    movie->movieTitle=movieTitle;
    movie->year=year;
    movie->next=NULL;

    if(ncm_head==NULL) {
        ncm_head=movie;
        ncm_head->next=ncm_head;
    }
    else {
        if(ncm_head->next==ncm_head) {
            if(ncm_head->movieId==movie->movieId) {
                return;
            }
            else {
                movie->next = ncm_head;
                ncm_head->next = movie;
                ncm_head = movie;
            }
        }
        else {
            Not_Checked_Out_Movie *temp = ncm_head;
            do {
                if(temp->movieId==movieId) {
                    return;
                }
                else {
                    temp=temp->next;
                }
            }while (temp!=ncm_head);

            movie->next=ncm_head->next;
            ncm_head->next=movie;
        }
    }
}

