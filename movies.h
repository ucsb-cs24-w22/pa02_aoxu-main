#ifndef MOVIES_H
#define MOVIES_H
#include <string>
#include <iostream>
using namespace std;

struct Movie {

    string name; // Movie name
    double rating; // Movie rating 

    //Setter 
    void setName(string s); 
    void setRating(double r);

    //Getter 
    string getName();
    double getRating();
};


#endif