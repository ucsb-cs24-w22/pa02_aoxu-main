#include "movies.h"
#include <fstream>
#include <iostream>
using namespace std;

void Movie::setName(string s)
{
    name = s;
}

void Movie::setRating(double r)
{
    rating = r; 
}

string Movie::getName()
{
    return name;
}

double Movie::getRating()
{
    return rating; 
}

