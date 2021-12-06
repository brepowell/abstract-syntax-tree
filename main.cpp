// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

#include <iostream>
#include <vector>
#include "ITokStream.h"
using namespace std;

/** Echoes the input to cout for the user to see
  @param tokens the vector of tokens of one line
  @param lineCount the number of input lines so far */
void echo(const vector<Token> &tokens, int lineCount)
{
   cout << "in [" << lineCount << "]: ";
   for(int i = 0; i < tokens.size(); i++){
      //Output the value of each token in the vector
      cout << tokens[i].value_;
   }
   cout << endl;
}//end echo

/** MAIN */
int main(int argc, char const *argv[])
{
   //g++ *.cpp -std=c++11 -g -o test
   //./test

//Sample input to test:
/*
5 + 7
x := 1
x + 8
z := x + y
y := 8
z
.
*/

   //The count of the number of lines so far (for echoing):
   int lineCount = 0;
   //Create an ITokStream object that takes in cin
   ITokStream input(cin);
   //Create a token
   Token eachToken;
   //A vector to store tokens
   vector<Token> tokens;

   //Until the end token is reached
   do {
      //Take in one token (the first token in a line)
      input >> eachToken;
      
      //Make sure the token is NOT an end of line or end token
      if(eachToken.type_ != TokType::eol && eachToken.type_ != TokType::end){

         //Take in one line of input
         while(eachToken.type_ != TokType::eol){
            //Take in more tokens (each one in the line)
            input >> eachToken;
            //Store the tokens from that line in order in a vector
            tokens.push_back(eachToken);
         }//end inner while - stop taking a line when eol is reached    
      
      //The end of the line has been reached
      }else if (eachToken.type_ == TokType::eol){   
         //If the tokens vector is not empty, echo it
         if(!tokens.empty() && tokens[0].type_ != TokType::end){
            echo(tokens, lineCount); //echo the line
            lineCount++; //Increase line count
         }//end if
         //Else, the line was blank - don't echo a blank line
      }//end else
   }
   while(eachToken.type_ != TokType::end);//end do - stop taking all input

   
}//end main

   /** TESTS COMPLETED */

/*
   //Test the TokType setting - SUCCESSFUL WITH ALL TESTS!
   cout << "value: " << eachToken.value_ <<endl;

   //null, addop, mulop, powop, variable, number, lparen, rparen, assign, eol, end 
   if(eachToken.type_ == TokType::eol){
      cout << "true" <<endl;
   }else{
      cout << "false" <<endl;
   }//end if-else
*/
