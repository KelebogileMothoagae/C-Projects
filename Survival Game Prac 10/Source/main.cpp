#include <iostream>
#include "libSurvival.h"
using namespace std;
using namespace RecipeSpace;
int main(int argc,char**argv)
{
    srand(time(nullptr));
     int intStatus=RUNNING;
     bool blnWon=false;
     bool blnFire=false;
    int intRows = ConvToInt(argv[1]);
    int intCols = ConvToInt(argv[2]);
    int intBushesChance = ConvToInt(argv[3]);
    int intNumTrees = ConvToInt(argv[4]);
    int intNumFlintStones = ConvToInt(argv[5]);
    int intNumTurns = ConvToInt(argv[6]);

    bool blnContinue = true;
    char chInput = '\0';
    TwoDarr arrCraft = AllocMem(intRows,intCols,intBushesChance,intNumTrees,intNumFlintStones,intNumTurns);
    int intSticks =0;
    int intFlint =0;
    int intLogs=0;



    if(argc!=7)
    {
        cerr<<"Incorrect Number of arguments Specified";
        exit(ERR_ARG);
    }


    do
    {
        //Display
        Display(arrCraft,intCols,intRows,intNumTurns,intSticks,intFlint,intLogs);
        cin>>chInput;
        chInput=tolower(chInput);
        //Movement of the player
        switch(chInput)
        {
        case 'w':
        case 's':
        case 'a':
        case 'c':
        case 'q':
        case 'g':
        case'e':
            case'z':
        case'x':
        case 'd':
        {
            MovePlayer(arrCraft,intCols,intRows,intNumTurns,intSticks,intFlint,chInput);
            break;
        }
        case 'f':
        {
            blnContinue=false;
            cout<<"Program terminated....."<<endl;
            break;
        }

        }

        intStatus= EndGame(arrCraft,intRows,intCols,intNumTurns);
        if(intStatus!=RUNNING)
            {
                blnContinue = false;
            }

}
while(blnContinue);
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
 if(blnWon)
        {
            cout<<"You Won!!!!!!!!"<<endl;
        }else if(blnFire)
        {
            cout<<"You Won (You were able to create Fire)"<<endl;

        }
Deallocate(arrCraft,intRows);

return 0;
}
