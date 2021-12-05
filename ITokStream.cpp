// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

/** Tokenizer Wrapper Class*/  
#include <iostream>
#include <string>
#include "ITokStream.h"
using namespace std;
  
/* Constructor*/
ITokStream::ITokStream(istream& inputStream)
   :  is_(inputStream){};

/* This input operator>> overload will take in
a token object and then help to set the TokType
for that object. In essence, this is a setter for
the type_ variable in the TokType enum class
 @post The token will have a TokType set
   inside of the TokType type_ variable
 @param rhs will take in a token object */
ITokStream& ITokStream::operator>>(Token& rhs)
{

}

/** Explicit type converter to a bool will
test if there is an error on the input stream.
 @return  True if there is a flag */
ITokStream::operator bool() const
{

}