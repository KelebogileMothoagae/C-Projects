#include "libMatrix2D.h"
using namespace std;
//No args constructor
Matrix2D::Matrix2D(): Matrix2D(DefaultRows,DefaultCols,{DefaultColour})
{

}
//Parameterized Constructor
Matrix2D::Matrix2D(int intRows,int intCols,ujColour recDefault)
{
    allocmem(intRows,intCols,recDefault);
}

//Copy Constructor
Matrix2D:: Matrix2D(Matrix2D& objOriginal): Matrix2D(objOriginal._rows,objOriginal._cols,{DefaultColour})
{
    copyfunc(objOriginal);
}

///Overloading the assignment (=) operator
Matrix2D& Matrix2D:: operator=(const Matrix2D& objRHS)
{
    //check for self assignment
    if(this !=&objRHS)
    {
        Dealloc();
        allocmem(objRHS._rows,objRHS._cols,{DefaultColour});
        copyfunc(objRHS);
    }
    return *this;
}
///Overloading the function invocation operator (())
ujColour& Matrix2D::operator()(int intRow,int intCol)
{
    enforceRange(intRow, 0, _rows - 1);
    enforceRange(intCol, 0, _cols - 1);
    return _pixel[intRow][intCol];
}

//If operators implementations
bool Matrix2D::operator==(const Matrix2D& objRHS)const
{
    if(_rows != objRHS._rows)
        return false;
    if(_cols != objRHS._cols)
        return false;
    for(int r=0; r<_rows; r++)
    {
        for(int c=0; c<_cols; c++)
        {
            ujColour recP1 = _pixel[r][c];
            ujColour recP2 = objRHS._pixel[r][c];

            if(recP1.intGrayValue!=recP2.intGrayValue)
                return false;

        }

    }
    return true;
}
bool Matrix2D::operator!=(const Matrix2D& objRHS)const
{
    return !(*this == objRHS);
}

//Overloading the stream insertion operator
std::ostream& operator <<(std::ostream& sLHS,const Matrix2D& objRHS)
{
    sLHS << "P2" << endl
         << objRHS._cols << ' ' << objRHS._rows << endl
         << "255" << endl;
    for(int r = 0; r < objRHS._rows; r++)
    {
        for(int c = 0; c < objRHS._cols; c++)
        {
            ujColour recDefault = objRHS._pixel[r][c];
            sLHS << recDefault.intGrayValue << ' ';
        }
        sLHS << endl;
    }

    return sLHS;

}
//Accessors
int Matrix2D:: getRows() const
{
    return _rows;
}

int Matrix2D::getCols() const
{
    return _cols;
}



void Matrix2D::allocmem(int intRows,int intCols,ujColour recDefault)
{
    _rows=intRows;
    _cols=intCols;
    _pixel= new ujColour*[_rows];
    for(int r=0; r<_rows; r++)
    {
        _pixel[r]=new ujColour[_cols];
        for(int c=0; c<_cols; c++)
        {
            _pixel[r][c]=recDefault;
        }
    }

}

Matrix2D Matrix2D:: operator++()
{
    for(int r=0; r<_rows; r++)
    {
        for(int c=0; c<_cols; c++)
        {
            ujColour recDefault = _pixel[r][c];
            if(recDefault.intGrayValue < 255)
                recDefault.intGrayValue++;
        }
    }
    return *this;
}
    Matrix2D Matrix2D::operator++(int)
    {
        Matrix2D objBackup(*this);
        for(int r=0; r<_rows; r++)
        {
            for(int c=0; c<_cols; c++)
            {
                ujColour recDefault = _pixel[r][c];
                if(recDefault.intGrayValue < 255)
                    recDefault.intGrayValue++;

                     _pixel[r][c] = recDefault;
            }
        }
        return objBackup;
        }
        void Matrix2D::copyfunc(const Matrix2D& objImage)
        {
            for(int r = 0; r < _rows; r++)
            {
                for(int c = 0; c < _cols; c++)
                {
                    _pixel[r][c] = objImage._pixel[r][c];
                }
            }
        }

        void Matrix2D::enforceRange(int intValue, int intMin, int intMax)
        {
            if(intValue < intMin|| intValue > intMax)
            {
                cerr <<"Incorrect value" << endl;
                exit(ERROR_RANGE);
            }
        }

        void Matrix2D::Dealloc()
        {
            for(int r=0; r<_rows; r++)
            {
                delete [] _pixel[r];
            }
            delete _pixel;
        }

        Matrix2D::~Matrix2D()
        {
            Dealloc();
        }
