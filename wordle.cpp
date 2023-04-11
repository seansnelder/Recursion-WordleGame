#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordlehelper(int in_index, const std::string& in, const std::string& floating,  std::string alphabet, std::set<std::string>& wordcombos, const std::set<std::string>& dict); 

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in, //correct position, i.e --n-
    const std::string& floating, //floating letters, i.e di
    const std::set<std::string>& dict /*epresent all valid words in dictionary from comb*/)
{
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz"; 
    
     
    std::set<std::string> wordcombos;
    
    int in_index = 0; 

    
    wordlehelper(in_index, in, floating, alphabet, wordcombos, dict); 
    // Add your code here
    //helper func. , pass in string in , pass in string of alphabet, int length, pass in set of strings to hold combinations


    return wordcombos;  
}

// Define any helper functions here

void wordlehelper(int in_index, const std::string& in, const std::string& floating,  std::string alphabet, std::set<std::string>& wordcombos, const std::set<std::string>& dict){
    
    std::string inplace = in; // declare and initialize inplace variable
    std:: string floatplace = floating;
    size_t nondashcount = 0; //have to keep track of nondashcount

    if(in_index == in.size()){ //BC, check if we have reached end of word
      
      if(dict.find(in) != dict.end() && floating.size() == 0){
       wordcombos.insert(in);  
      
      }
      return;
    }
            
      for(int i = in_index +1; i < inplace.size(); i++){

            if(inplace.at(i) != '-'){
              nondashcount++; 
          }
          }
      

    if(inplace.at(in_index) == '-'){ //create an index to go through the "in" function 
          
          

          int numblanks = inplace.size() - in_index;
            
            std::set<char> usedfloating; 

            for(int i = 0; i < floatplace.size(); i++){ //looping through the floating string
                 
                if(usedfloating.find(floatplace.at(i)) != usedfloating.end()){
                  continue; //if we do find and there is no repetition of letter


                }
                inplace[in_index] = floatplace.at(i); //originally "-",setting floating character to a character in "in"
                std::string tempfloat = floatplace; 
                tempfloat.erase(i, 1); 

                
                wordlehelper(in_index + 1, inplace, tempfloat, alphabet, wordcombos, dict); 
                //}
                usedfloating.insert(floatplace.at(i)); 

                inplace[in_index] = '-'; 
                
                
            }


            if(numblanks > floatplace.size() + nondashcount){
                for(char a: alphabet){ //we need a check whether alphabet has floating 
            //update usedfloating 
            //secondary updae
                  if(usedfloating.find(a) != usedfloating.end()){
               
              continue; 
                  }

            inplace.at(in_index) = a; 
            wordlehelper(in_index + 1, inplace, floatplace, alphabet, wordcombos, dict);

            inplace.at(in_index) = '-'; 
            

            } 
            
          }
    }
    
    else if(inplace.at(in_index) != '-'){ //doesn't go through the 

      wordlehelper(in_index + 1, inplace, floatplace, alphabet, wordcombos, dict); 
    }
}






//How would I approach? 

