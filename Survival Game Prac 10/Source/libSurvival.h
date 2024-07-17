#ifndef LIBSURVIVAL_H_INCLUDED
#define LIBSURVIVAL_H_INCLUDED
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cassert>
using namespace std;
namespace RecipeSpace
{
 typedef* OneDarr;
 typedef**TwoDarr;


enum Errors
{
ERR_RANGE=-1,
ERR_CONV=-2,
ERR_ARG=-3
};

//Constants
const int Empty =0;
const int Player=1;
const int Trees=2;
const int Flint =3;
const int Bushes=4;

const char FEATURES[]={'.','P','*','o','+'};

 struct strucCrime
    {
        TwoDarr arrCrime;
        int intCols;
        int intRows;
        int NumturnLeft;
    };
enum eStatus
    {
        RUNNING,
        QUIT,
        WON,
        LOST
    };


//Functions Declarations
int ConvToInt(string strInput);
void Pause();
bool blnCraft(int& intStone ,int& intaxe,int& intFlint,char chInput);
bool IsinGame(int intRows,int intCols,int& intRow,int &intCol);
int EndGame(TwoDarr arrCraft,int intRows,int intCols,int intNumTurns);
void PlaceBushes(TwoDarr arrCraft,int intCols,int intRows,int intBushesChance);
TwoDarr AllocMem(int intRows,int intCols,int intBushesChance,int intNumTrees,int numStones,int intNumTurns);
void PlaceFeature(TwoDarr arrCraft,int intCols,int intRows,int intFeature,int intNums);
void MovePlayer(TwoDarr arrCraft,int intCols,int intRows,int& intNumTurns,int& intSticks,int& intFlint,char chInput);
void FindFeature(TwoDarr arrCraft,int intRows,int intCols,int& intRow,int& intCol,int intFeature);
void Display(TwoDarr arrCraft,int intCols, int intRows,int intNumturns,int intSticks,int intFlint,int intLogs);
void Deallocate(TwoDarr arrCraft,int intRows);
}

#endif // LIBSURVIVAL_H_INCLUDED
