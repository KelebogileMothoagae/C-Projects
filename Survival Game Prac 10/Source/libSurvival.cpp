#include "libSurvival.h"
namespace RecipeSpace
{
int GetRand(int intLowest,int intHighest)
{
    assert(intHighest>intLowest);
    int Random = intHighest-intLowest+1;
    return rand()%Random+intLowest;
}
void Pause()
{
    cin.ignore(100,'\n');
    cin.get();
    cout<<"Press Enter To continue......"<<endl;
}

int ConvToInt(string strInput)
{
    int intConv=0;
    stringstream ss(strInput);
    ss>>intConv;
    if(ss.fail())
    {
        cerr<<"Could not convert String to integer"<<endl;
        exit(ERR_CONV);
    }
    return intConv;
}

//Allocate Memory
TwoDarr AllocMem(int intRows,int intCols,int intBushesChance,int intNumTrees,int numStones,int intNumTurns)
{
    TwoDarr arrCraft;
    arrCraft = new OneDarr[intRows];
    for(int r=0; r<intRows; r++)
    {
        arrCraft[r]=new int[intCols];
        for(int c=0; c<intCols; c++)
        {
            arrCraft[r][c]=Empty;
        }
    }
    int intPRow=intRows/2;
    int intPcol=intCols/2;
    //Place the player near the center

    arrCraft[intPRow][intPcol]=Player;
    //Place Trees
    PlaceFeature(arrCraft,intCols,intRows,Trees,intNumTrees);
    //Place Flint
    PlaceFeature(arrCraft,intCols,intRows,Flint,numStones);
    //Place Bushes
    PlaceBushes(arrCraft,intCols,intRows,intBushesChance);
    return arrCraft;
}

void PlaceBushes(TwoDarr arrCraft,int intCols,int intRows,int intBushesChance)
{
    for(int r=0; r<intRows; r++)
    {
        for(int c=0; c<intCols; c++)
        {
            int intRandom =GetRand(0,100);
            if(arrCraft[r][c]!=Player )
            {
                if(intRandom<intBushesChance)
                {
                    arrCraft[r][c]=Bushes;
                }
            }
        }
    }
}
//Deallocation of the memory
void Deallocate(TwoDarr arrCraft,int intRows)
{

    for(int r=0; r<intRows; r++)
    {
        delete[] arrCraft[r];
    }
    delete[]  arrCraft;
    arrCraft=nullptr;
}

void PlaceFeature(TwoDarr arrCraft,int intCols,int intRows,int intFeature,int intNums)
{
    for(int n=0; n<intNums; n++)
    {
        int intRow=GetRand(0,intRows-1);
        int intCol=GetRand(0,intCols-1);

        while (arrCraft[intRow][intCol]!=Empty)
        {
            intRow=GetRand(0,intRows-1);
            intCol=GetRand(0,intCols-1);
        }
        arrCraft[intRow][intCol]=intFeature;
    }
}

//Move Player

//Find Player
void FindFeature(TwoDarr arrCraft,int intRows,int intCols,int& intRow,int& intCol,int intFeature)
{
    intRow=-1;
    intCol=-1;

    for(int r=0; r<intRows; r++)
    {
        for(int c=0; c<intCols; c++)
        {
            if(arrCraft[r][c]==intFeature)
            {
                intRow=r;
                intCol=c;
                return;
            }
        }
    }
}

bool IsinGame(int intRows,int intCols,int& intRow,int &intCol)
{
    return (intRow>=0 && intRow<intRows && intCol>=0 && intCol<intCols);

}

bool blnCraft(int& intStone ,int& intaxe,int& intFlint,char chInput)
{

if(intFlint>=1 && intStone>=1 && chInput=='c')
{
    intFlint--;
    intStone--;
    intaxe++;
    return true;
}else
{
return false;
}
}

//End game
int EndGame(TwoDarr arrCraft,int intRows,int intCols,int intNumTurns)
{
    //Nightfall
    int intReturn = RUNNING;
    if(intNumTurns<=-1)
    {
        cout<<"You Lost the Game!!!"<<endl;
        intReturn = LOST;


    }
    return intReturn;
}

void MovePlayer(TwoDarr arrCraft,int intCols,int intRows,int& intNumTurns,int& intSticks,int&  intFlint,char chInput)
{
    //Find the players current location
    int intPCol=0;
    int intPRow=0;
    assert(intPCol>=0);
    assert(intPRow>=0);
    FindFeature(arrCraft,intRows,intCols,intPRow,intPCol,Player);
    if(intPRow<0 || intPCol<0)
    {
        return;
    }

    int intDRow = intPRow;
    int intDCol = intPCol;

    //calculate the players destination location
    switch(chInput)
    {
    case 'q':
    {
        intDRow--;
        intDCol--;
        break;
    }
    case 'w':
    {
        intDRow --;
        break;
    }
    case 'e':
    {
        intDRow--;
        intDCol++;
        break;
    }
    case 's':
    {
        intDRow++;
        break;
    }
    case 'a':
    {
        intDCol--;
        break;
    }
    case 'd':
    {
        intDCol++;
        break;
    }
    case 'z':
    {
        intDRow++;
        intDCol--;
        break;
    }
    case 'x':
    {
        intDRow++;
        intDCol++;
        break;
    }
    }

    //if is in the Game
    if(IsinGame(intRows,intCols,intDRow,intDCol))
    {
        //When player steps inside the bushes the number of sticks increase
        if(arrCraft[intDRow][intDCol]==Bushes)
        {
            intSticks++;
            arrCraft[intDRow][intDCol]=Player;

        }
        else
        {
            arrCraft[intDRow][intDCol]=arrCraft[intDRow][intDCol]+Player;
        }
        arrCraft[intDRow][intDCol]=arrCraft[intDRow][intDCol]-Player;
//when player moves into the tree
    if(arrCraft[intDRow][intDCol]==Trees)
        {

            arrCraft[intDRow][intDCol]=Player;
        }
        else
        {
            arrCraft[intDRow][intDCol]=arrCraft[intDRow][intDCol]+Player;
        }
        arrCraft[intDRow][intDCol]=arrCraft[intDRow][intDCol]-Player;

//when player bumps into a flint stone
        if(arrCraft[intDRow][intDCol]==Flint)
        {
            intFlint++;
            arrCraft[intDRow][intDCol]=Player;
        }
        else
        {
            arrCraft[intDRow][intDCol]=arrCraft[intDRow][intDCol]+Player;
        }
        arrCraft[intDRow][intDCol]=arrCraft[intDRow][intDCol]-Player;



        if(arrCraft[intDRow][intDCol]==Empty)
        {
            arrCraft[intPRow][intPCol] = Empty;
            arrCraft[intDRow][intDCol] = Player;
            intPRow = intDRow;
            intPCol = intDCol;
        }
        intNumTurns--;
    }
}



void Display(TwoDarr arrCraft,int intCols, int intRows,int intNumturns,int intSticks,int intFlint,int intLogs)
{
    system("cls");
    for(int r=0; r<intRows; r++)
    {
        for(int c=0; c<intCols; c++)
        {
            cout<<setw(2)<<FEATURES[arrCraft[r][c]]<<"";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"w- Move Up"<<endl;
    cout<<"d- Move Right"<<endl;
    cout<<"e- Right Up"<<endl;
    cout<<"q- Left Up"<<endl;
    cout<<"s- Move Down"<<endl;
    cout<<"c- Craft an axe"<<endl;
    cout<<"g- Craft Fire"<<endl;
    cout<<"a- Move Left"<<endl;
    cout<<"z- Move Left Down"<<endl;
    cout<<"x- Move Right Down"<<endl;
    cout<<endl;
    cout<<"Number of logs collected: "<<intLogs<<endl;
    cout<<"Number of Sticks collected: "<<intSticks<<endl;
    cout<<"Number of Flints collected: "<<intFlint<<endl;
    cout<<"Number of turns Left to nightfall: "<<intNumturns<<endl;

}
}

