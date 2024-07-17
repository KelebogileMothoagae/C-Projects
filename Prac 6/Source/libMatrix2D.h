#ifndef LIBMATRIX2D_H_INCLUDED
#define LIBMATRIX2D_H_INCLUDED
#include <iostream>
#include<cstdlib>
#include<string>
#include<sstream>

enum StatusCode
{
    SUCCESS,
    ERROR_RANGE,
    ERROR_ROWS_MISMATCH,
    ERROR_COLS_MISMATCH,
    ERROR_CLONING
};

struct ujColour
{
    int intGrayValue;
};

class Matrix2D
{
public:
    //No args constructor
    Matrix2D();
    //Parameterized Constructor
    Matrix2D(int intRows,int intCols,ujColour recDefault);
    //Copy Constructor
    Matrix2D(Matrix2D& objOriginal);

    ///Overloading the assignment (=) operator
    Matrix2D& operator=(const Matrix2D& objRHS);
    ///Overloading the function invocation operator (())
    ujColour& operator()(int intRow,int intCol);

    //If
    bool operator==(const Matrix2D& objRHS)const;
    bool operator!=(const Matrix2D& objRHS)const;
    //Overloading the stream insertion operator

    friend std::ostream& operator <<(std::ostream& sLHS,const Matrix2D& objRHS);
    //Accessors
    int getRows() const;
    int getCols() const;


//return new value
    Matrix2D operator++();
    //return old value
    Matrix2D operator++(int);

    static const int Max = 250;
    static const int Min=0;
    static const int DefaultRows=500;
    static const int DefaultCols=500;
    static const int DEFAULT_SIZE = 1;
    static const int DefaultColour = 0;

    ~Matrix2D();
private:
    void Dealloc();
    void enforceRange(int intValue, int intMin, int intMax);
    void allocmem(int intRows,int intCols,ujColour recDefault);
     void copyfunc(const Matrix2D& objImage);
    int _rows;
    int _cols;
    ujColour**_pixel;
};



#endif // LIBMATRIX2D_H_INCLUDED
