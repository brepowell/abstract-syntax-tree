// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "ITokStream.h"
#include "AST.h"
using namespace std;


/**
 * @brief Checks the vector/expression for parentheses
 * Makes sure the parentheses match.
 * @param infix the vector of tokens in infix format
 * @return true if infix vector had matching parens
 * @return false if infix vector has an error
 */
bool checkBalancedParens(vector<Token> infix, bool &hasParens)
{
   stack<Token> TokenStack;
   bool balancedSoFar = true;
   int i = 0; //Tracks position in vector
   while (balancedSoFar && i < infix.size())
   {
      Token token = infix[i];
      i++;
      // Push an open lparen
      if (token.type_ == TokType::lparen){
         TokenStack.push(token);
         hasParens = true;
      // Find a close rparen 
      }else if (token.type_ == TokType::rparen){
         if (!TokenStack.empty())
            TokenStack.pop();   // Pop a matching lparen
         else              // No matching lparen
            balancedSoFar = false;
      }
      // Ignore all characters other than braces
   }
   if (balancedSoFar && TokenStack.empty())
      return true;
   else
      return false;
}

/** Converts to postfix
  @brief Converts an infix expression to a postfix expression
  @param infix the vector of tokens in infix format
  @param assign False initially, becomes True if 
  the := assign operator is found
  @param variable tracks what variable will need to be assigned
  if the assignment operator is located
  @return the postfix vector*/
vector<Token> toPostfix(const vector<Token> &infixTokens, 
   bool foundError, bool &assign, char &var)
{
   //Index i for traversing the infix vector
   int i = 0; 
   //check for the assignment operator
   if(infixTokens[0].type_ == TokType::variable && 
      infixTokens[1].value_ == " " &&
      infixTokens[2].type_ == TokType::assign){
      assign = true;
      var = tolower(infixTokens[0].value_[0]);
      cerr << "Found an assignment operator" << endl;
      i += 3;//move i to the first token after :=
   }//end if

   //Contain the operators and the postfix expression
   vector<Token> postfixExp;
   stack<Token> operators;

   //Loop through the infix expression.
   //If there are errors, stop.
   while (i < infixTokens.size() && !foundError){
      
      //Look for invalid tokens:
      if(infixTokens[i].type_ == TokType::null &&
        infixTokens[i].value_ != " "){
           //ERROR - THIS IN NOT A VALID TOKEN
           cerr << "error" << endl;
           foundError = true;

      //Skip spaces:
      //}else if (infixTokens[i].type_ == TokType::null){
         //i++;
      
      //Look for operands (numbers or variables):
      }else if (infixTokens[i].type_ == TokType::number ||
         infixTokens[i].type_ == TokType::variable){
         //Add them to the postfix expression
         postfixExp.push_back(infixTokens[i]);
         //i++;

      //Look for operators
      }else if(infixTokens[i].type_ == TokType::addop ||
         infixTokens[i].type_ == TokType::mulop ||
         infixTokens[i].type_ == TokType::powop){

         //Check the current operators stack (make sure it is not empty)
            //If the stack of operators is not empty...
               //While the top operator in the stack is not a left parentheses,
               //and either the top operator in the stack 
               //has a higher precedence than the current operator
               //OR the top operator in the stack and the current operator have
               //equal precedence and the current operator 
               //is not a power operator
               //SEGMENTATION FAULT WAS HERE!
            while(!operators.empty() &&
               operators.top().type_ != TokType::lparen &&
               (operators.top().type_ > infixTokens[i].type_ ||
               infixTokens[i].type_ == operators.top().type_ &&
               infixTokens[i].type_ != TokType::powop)){
               //add the higher operator to the postfix expression
               postfixExp.push_back(operators.top());
               operators.pop();//remove the top from the stack
            }//end inner while

         //add the current operator to the operators stack
         operators.push(infixTokens[i]);

      //Check for parentheses
      }else if (infixTokens[i].type_ == TokType::lparen){
         operators.push(infixTokens[i]);
      }else if (infixTokens[i].type_ == TokType::rparen){
         if(!operators.empty()){
            //Keep taking operators off of the operator stack
            //until a left parenthesis is reached or the end
            //of the vector is reached (Error - no matching paren)
            while(operators.top().type_ != TokType::lparen && 
               !operators.empty() && !foundError){
               //place the operators into the postfix expression
               postfixExp.push_back(operators.top());
               operators.pop();//remove the top from the stack
            }//while stops when a left parenthesis is reached or stack is empty

            //Check whether or not the last operator in the stack is an lparen
            if (operators.top().type_ == TokType::lparen){
               operators.pop();//take the left parenthesis off.
               if(!operators.empty()){
                  //After finding the lparen, move the operator at the top
                  //of the stack to the postfix expression
                  postfixExp.push_back(operators.top());
                  operators.pop();//remove the top from the stack
               }
            //The stack is empty and no match was found
            }else{
               //ERROR - no matching parenthesis found
               foundError = true;
            }//end nested if/else
         }//end if -- the operator stack is empty
      }//end outer if -- handled parentheses
      i++;
   }//end while -- looped through the end of the infix expression

   //Check if there are any operators remaining in the stack
   while (!operators.empty()){
      //If a left parenthesis "(" remains, then it did not have a match
      if(operators.top().type_ == TokType::lparen){
         foundError = true;
      }else{
         //add remaining operators to the postfix expression
         postfixExp.push_back(operators.top());
         operators.pop();//remove the top from the stack 
      }
   }//end while
   
   //The postfix expression should be complete

   /*
   input of two operands with no operator in between: 5x
   input of one operand next to a parentheses with no operator in between: 7(
   input of two operators next to each other: //
   input of a variable to the right of an exponent operator: ^y
   input of a negative integer (with a minus sign): -1 + x
   input of an operators in prefix form (operators appearing before operands): + 7 * 6 8
   input of a number larger than 2147483647 (cannot fit inside an int)
   invalid chars, like & or %
   */

   return postfixExp;
}


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
3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3

should be 3 4 2 * 1 5 − 2 3 ^ ^ / +
OR MAYBE 342*15-/23^^+ ????

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
   //(Note: the push_back function makes copies of each token)
   vector<Token> infixTokens;
   
   //Until the end token is reached, collect tokens
   do {
      //A map to store ASTs
      map<char, AST> variableStore;
      
      //Take in the first token
      input >> eachToken;
      //The >> will set the value_ and type_ 
      //of the token as each token is absorbed

      //Make sure the token is NOT an end of line or end token
      if(eachToken.type_ != TokType::eol && eachToken.type_ != TokType::end){
         
         //Take in one line of input
         //Check to see if the end of the line is reached
         while(eachToken.type_ != TokType::eol){
            //Store the previous token in the vector
            infixTokens.push_back(eachToken);
            //Get and set the next token
            input >> eachToken;
         }//end inner while - stop taking a line when eol is reached    
      }//end if
      
      //The eol token has been reached
      if (eachToken.type_ == TokType::eol){   
         //If the tokens vector is not empty, perform these steps
         //for each line of input that contains an expression
         if(!infixTokens.empty() && infixTokens[0].type_ != TokType::end){
            lineCount++; //Increase line count
            
            //isInput allows the echo to work for input or output
            bool isInput = true;

            //Errors should be caught before echoing the input
            //Errors will be caught in the conversion to postfix:
            bool hasErrors = false; //will check for errors
            bool assign = false; //will check for assign tokens
            char var = '\0'; //The key for variable store structure

            //convert to postfix
            vector<Token> postfixTokens = 
            toPostfix(infixTokens, hasErrors, assign, var); 

            //Now echo the original output, if no errors
            
            if(!hasErrors){
               echo(infixTokens, lineCount, isInput); //echo the input
               cout << "TEST OF POSTFIX" << endl;
               echo(postfixTokens, lineCount, isInput); //TEST OF POSTFIX
               cout << endl;
            };
            
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
