// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

#include <iostream>
#include "ITokStream.h"
using namespace std;

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
   ITokStream test(cin);

   //Create a token
   Token testerToken;
   test >> testerToken;

   //null, addop, mulop, powop, variable, number, lparen, rparen, assign, eol, end 
   //Test the TokType setting:
   cout << "value: " << testerToken.value_ <<endl;

   if(testerToken.type_ == TokType::mulop){
      cout << "true" <<endl;
   }else{
      cout << "false" <<endl;
   }//end if-else

}//end main