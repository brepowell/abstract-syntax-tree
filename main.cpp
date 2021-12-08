// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

#include <iostream>
#include <vector>
#include <map>
#include "ITokStream.h"
#include "AST.h"
using namespace std;

/** Echoes the input to cout for the user to see
  @param tokens the vector of tokens in infix format
  @param assign False initially, 
  becomes True if the := assign operator is found
  @param variable tracks what variable will need to be assigned
  if the assignment operator is located
  @return the postfix vector*/

/**
vector<Token> toPostfix(vector<Token> infix, bool &assign, string& variable)
{
   //new vector to hold the tokens
   vector<Tokens> postfixTokens;
   //find errors
   /*
   input of two operands with no operator in between: 5x
   input of one operand next to a parentheses with no operator in between: 7(
   input of two operators next to each other: //
   input of a variable to the right of an exponent operator: ^y
   input of a negative integer (with a minus sign): -1 + x
   input of an operators in prefix form (operators appearing before operands): + 7 * 6 8
   input of a number larger than 2147483647 (cannot fit inside an int)
   missing closing parenthesis: a * (b + c
   invalid chars, like & or %

   */

/*
   return postfixTokens;
}
*/

/** Echoes the input to cout for the user to see
  @param tokens the vector of tokens of one line
  @param lineCount the number of input lines so far */
void echo(vector<Token> tokens, int lineCount, bool isInput)
{
   if (isInput){
      cout << "in  [" << lineCount << "]: ";
   }else{
      cout << "out [" << lineCount << "]: ";
   }

   //Output the value of each token in the vector
   for(Token i : tokens){
      cout << i.value_;
   }//end for
   
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
   //COULD THIS BE TURNED INTO A POINTER, AND USED TO CREATE NEW TOKENS IN THE LOOP?

   //A vector to store tokens
   vector<Token> infixTokens;
   
   //Take in one token (the first token in a line)
   //input >> eachToken;

   //Until the end token is reached
   //MAYBE - TRY MAKING THIS A WHILE LOOP? - QSC
   do {

      //A map to store ASTs
      map<string, AST> variableStore;
      
      //Take in one token (the first token in a line)
      input >> eachToken;
      //Now the value_ and the type_ have been set for the token

      //Make sure the token is NOT an end of line or end token
      if(eachToken.type_ != TokType::eol && eachToken.type_ != TokType::end){
         //Take in one line of input
         while(eachToken.type_ != TokType::eol){
            //Store the tokens from that line in order in a vector
            infixTokens.push_back(eachToken);
            //Take in more tokens (each one in the line)
            //The >> will set their value_ and type_ as they are absorbed
            input >> eachToken; //THIS MUST BE WHERE THE ERROR IS HAPPENING!
         }//end inner while - stop taking a line when eol is reached    
      }//end if
      
      //The eol token has been reached
      if (eachToken.type_ == TokType::eol){   
         //If the tokens vector is not empty, echo it
         if(!infixTokens.empty() && infixTokens[0].type_ != TokType::end){
            lineCount++; //Increase line count
            
            bool isInput = true;
            echo(infixTokens, lineCount, isInput); //echo the input
            
            //bool assign = false; //will check for assign tokens
            //string = variable;

            //convert to postfix
            //vector<Tokens> postfixTokens = toPostfix(infixTokens, assign, variable); 

            //AST tree(postfixTokens); //make an abstract syntax tree
            /*
            if (assign){
               //if there was assignment, store the AST
               //using "variable" as the key
               store(variableStorage, tree, variable);
            }
            */ 
            //isInput = false; //now display the output
            //echo(infixTokens, lineCount, isInput); //echo the output

         }//end if
         //Else, the line was blank - don't echo a blank line
      }//end else
      
      infixTokens.clear();
   }
   while(eachToken.type_ != TokType::end);//end do - stop taking all input
   
   //tokens.clear();
   //cerr << "tokens are cleared again" << endl;
   
}//end main

   /** TESTS COMPLETED */

/*
   //Create an ITokStream object that takes in cin
   ITokStream input(cin);
   
   //Create a token
   Token eachToken;

   //Take in one token (the first token in a line)
   input >> eachToken;

   //Test the TokType setting - SUCCESSFUL WITH ALL TESTS!
   cout << "value: " << eachToken.value_ <<endl;

   //null, addop, mulop, powop, variable, number, lparen, rparen, assign, eol, end 
   if(eachToken.type_ == TokType::eol){
      cout << "true" <<endl;
   }else{
      cout << "false" <<endl;
   }//end if-else
*/
