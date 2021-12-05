// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

#include <iostream>
#include "ITokStream.h"
using namespace std;

int main(int argc, char const *argv[])
{

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

   //Create an ITokStream object
   ITokStream test(cin);

   //Create a token
   ITokStream::Token token;
   test >> token;

   //null, addop, mulop, powop, variable, number, lparen, rparen, assign, eol, end 

   
   //Test the TokType setting:
   cout << "value: " << token.value_ <<endl;

   if(token.type_ == ITokStream::TokType::addop){
      cout << "true" <<endl;
   }else
      cout << "false" <<endl;


}//end main