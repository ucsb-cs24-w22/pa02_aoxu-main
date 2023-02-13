// Winter'22
// Instructor: Diba Mirza
// Student name: Marco Wong, Ao Xu 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>

#include "movies.h"

using namespace std;



bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
  if(argc < 2)   {
    cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
    cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
    exit(1);
  }

  ifstream movieFile (argv[1]);
 

  if (movieFile.fail()){
    cerr << "Could not open file " << argv[1];
    exit(1);
  }

  
vector<Movie> movieVector; 
int countMovies = 0;
//Create an object of a STL data-structure to store all the movies

string line, movieName;
double movieRating;
// Read each file and store the name and rating
while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
  // Use std::string movieName and double movieRating
  // to construct your Movie objects
  //cout << movieName << " has rating: " << movieRating << endl;
  // insert elements into your data structure
  Movie movieTemp;
  movieTemp.setName(movieName);
  movieTemp.setRating(movieRating);

  movieVector.insert(movieVector.end(),movieTemp);
  countMovies++; 
 
}

for (int i=0; i < countMovies; i++) // Bubble Sorting algorithm to set the Movie Vector in alphabetical order
{
  for (int j = i + 1; j < countMovies; j++) 
  {
    if (movieVector[j].getName() < movieVector[i].getName())
    {
      Movie tempHolder;
      tempHolder = movieVector[i]; 
      movieVector[i] = movieVector[j];
      movieVector[j] = tempHolder; 
    }
  }
} 

//cout << "Testing Movie In Alphabetical Order: " << endl;
movieFile.close();

if(argc == 2){
  //print all the movies in ascending alphabetical order of movie names
  for (int i = 0; i < countMovies; i++)
  {
    cout << movieVector[i].getName() << ", " 
    << fixed << setprecision(1) << movieVector[i].getRating() << endl;
  }
  return 0;
}

int prefixCounter = 0;  // Keeps track of the number of prefixes that were passed in
if (argc != 2)
{
  vector<string> prefixVector;  // Vector that holds all the prefix strings passed in
  vector<Movie> bestMovie;    // Vector that holds the best movie of each prefix that exists
  vector<string> foundPrefix; // Vector that holds the prefixes that can be found in the Movie vector
  vector<string> notFoundPrefix;  // Vector that holds the prefixes that cannot be found in the Movie vector

  for (int i = 2; i < argc; i++)   // Inserting the strings of the prefix that we want to find into the prefixVector
  {
    prefixVector.insert(prefixVector.end(),argv[i]);
    prefixCounter++;
  }

  for (int i = 0; i < prefixCounter; i++) // Goes through the Prefixes that I pass in  //O(m)*(O(n)+O(1)....))
  {
    vector<Movie> movieWithPrefixVector;  // Vector that holds the movies given the same prefix, for example, if prefix is "the", contains all the movies beginnning with "the"
    int prefixExist = 0;  // If this equals 0, that means never found a word with this prefix

    for (int j = 0; j < countMovies; j++) // Goes through the Movies that are in the Movie Vector
    {
      if (movieVector[j].getName().rfind(prefixVector[i],0) == 0)
      {
        
        Movie movieTempTwo;   // Temporary Movie to hold the movie title and rating 

        movieTempTwo.setName(movieVector[j].getName());
        movieTempTwo.setRating(movieVector[j].getRating());

        movieWithPrefixVector.insert(movieWithPrefixVector.end(), movieTempTwo); // We add the temporary Movie into our vector that contains the Movie with the processed prefix
        prefixExist++; // Since there exists a movie with a given prefix, increment this value 
        
      } 
    } 

    // Sets the rating from highest to lowest in movieWithPrefixVector with a given prefix

    for (long unsigned int l = 0; l < movieWithPrefixVector.size(); l++)  // Bubble Sort 
    {
      for (long unsigned int m = 0; m < movieWithPrefixVector.size()-1 -l; m++)
      {
        if (movieWithPrefixVector[m].getRating() < movieWithPrefixVector[m + 1].getRating())
        {
          Movie tempHolder;
          tempHolder = movieWithPrefixVector[m];
          movieWithPrefixVector[m] = movieWithPrefixVector[m + 1];
          movieWithPrefixVector[m+1] = tempHolder;
        }

      }
    } 
    
    if (movieWithPrefixVector.size() != 0) // If the vector that contains the processed movie given a prefix is not empty, we print out the title and rating
    {
      for (long unsigned int k = 0; k < movieWithPrefixVector.size(); k++)
      {
        cout << movieWithPrefixVector[k].getName() << ", "
             << fixed << setprecision(1) << movieWithPrefixVector[k].getRating() << endl;
      }
      cout << endl;
    }
    
    if (prefixExist != 0)   // So if the prefix exists, we insert the best movie into the bestMovie vector
    {                       //  and then we add the prefix that existed in the movies vector into the foundPrefix vector.
      bestMovie.insert(bestMovie.end(), movieWithPrefixVector[0]);
      foundPrefix.insert(foundPrefix.end(), prefixVector[i]);
    }
    
    if (prefixExist == 0) // So if the prefix does't exist, we insert that prefix into our notFoundPrefix vector
    {
      notFoundPrefix.insert(notFoundPrefix.end(), prefixVector[i]);
    }
  }
  
  for (unsigned long int i = 0; i < notFoundPrefix.size(); i++) // Print out the vector that contains that prefix that weren't found
  { 
      cout << "No movies found with prefix " << notFoundPrefix[i] << endl << endl; 
  }
  for (long unsigned int k = 0; k < bestMovie.size(); k++)  // Print out the vector that contains the best movie according to the prefix
  {
     /* cout << prefixVector[k] << endl;
     cout << bestMovie[k].getName() << bestMovie[k].getRating() << endl ; */
     cout << "Best movie with prefix "
          << foundPrefix[k]
          << " is: "
          << bestMovie[k].getName()
          << " with rating " << fixed << showpoint << setprecision(1) << bestMovie[k].getRating() << endl;
  }
}

  
return 0;
}

/*
Part 3: Big O Analysis
m prefix value, a dataset of n movies and each prefix matches with at most k movies
-Lines 25- 30: O(1) which is constant time, bc it doesn't matter what size the input is, the comparison
will always be made the same between argc and 2
-Lines 34-37: O(1), again it doesn't matter what the input size is, still making a comparison if the file opened or not
-Creating any varaible would be of time complexity O(1)
-Creating an empty vector would be of time complexity O(1)
-Inserting "Movies" into a vector would be of time complexity O(n) bc "n" depends on the number of movies
-Lines 61-73: Bubble Sorting takes O(n^2) bc there is 2 for loops which depends on "n" inputs
-Lines 80-84: One for loop that depends on the size of "n" would be of time complexity O(n)
-Lines 96-100: One for loop that depends on the size of "n" would be of time complexity O(n)
-Lines 107-121: For the one for loop, it depends on size of "n" which means O(n). Even though there
is a if loop and a vector insert function, they are of time complexity O(1), but O(n) takes longer which means the
overall time complexity of that block, would be O(n).
-Lines 125-138: The Bubble Sorting algorithm is known to be of O(k^2) since the 2 for loops depends on the size of "k". 
The if-statement is of O(1), but is less than O(k^2). Overall time complexoty of that block would be O(k^2).
-Lines 140-148: The if-loop and the size() funciton of a vector are both of O(1), but the for loop is of O(k) which means the overall time complexity is O(n) since it takes longer
-Lines 150-154: The if-loop and insert() function are both of O(1)
-Lines 156-159: The if-loop and insert() function are both of O(1)
-Lines 162-176: Totally the sum of notfoundprefix.size() and bestmovie.size() equals to n, which is number of total movies so it is O(n) for totally these two functions
-For overall (Lines 102-180): It's O(m)*(O(n)+O(k^2)) since the outside function depends on the number of prefix values and the biggest algorithm for the n and k are O(k^2) and O(n) in the nested part. Also that's because O(1) is eliminated when calculating the big O in the sum for the individual nestd functions.
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
  if(line.length() <= 0) return false;
  string tempRating = "";

  bool flag = false;
  movieName = tempRating = "", movieRating = 0.0, flag = false;

  for (long unsigned int i = 0; i < line.length(); i++){
    if(flag) tempRating += line[i];
    else if(line[i]==','&& line[0]!='"') flag = true;
    else {
		  if(i==0 && line[0]=='"') continue;
		  if(line[i]=='"'){ i++; flag=true; continue;}
		  movieName += line[i];
	  }
  }
  
  movieRating = stod(tempRating);
  return true;
}
