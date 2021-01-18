#include <iostream>
#include <string>

using namespace std;

string toString(char x){
    string s(1,x);
    return s;
}

int rotateLeft (int value, int amount)
{
    //four bit rotate left

    const int OVERFLOW = 0b10000;
        while (amount > 0)
        {
            value = value << 1;
            if (((value & OVERFLOW) == OVERFLOW))
            {
                value = value & 0b1111;  //remove overflow bit
                value = value | 0b0001;  //set the rightmost bit
            }
        amount--;
        }
    return value;
}

int main()
{
    //4bit long because there 4 cylinders
    int inValvesOpen  = 0b0010;  //1 open o                       0 closed x
    int outValvesOpen = 0b0100;  //1 open o                       0 closed x
    int pistonUp      = 0b1010;  //1 is up moving DOWN        T   0 is down mobing UP
    int cylinderFire  = 0b1000;  //1 the spark and combustion *   0 nothing
    //      cylinder     #1234


    for (int i=0; i<5; i++){
        string d1="    1        2        3        4   ";
        string d2="   ___      ___      ___      ___  ";
        string d3=" x|   |x  x|   |x  x|   |x  x|   |x";
        string d4="  |   |    |   |    |   |    |   | ";
        string d5="   ---      ---      ---      ---  ";
        string d6="    ?        ?        ?        ?   ";

        int positionMask = 0b1000; // test with & true of bit on

        for (unsigned int c=0; c<4; c++){  //0 is cylinder 1

            //integer offset
            unsigned int offset = c * 9;

            char stateLabel = 'C';
            signed char inValve = 'x';
            char outValve = 'x';
            char upPiston = ' ';
            char downPiston = 'T';
            char chamber = ' ';


            //check in valve
            if (inValvesOpen & positionMask){
                inValve = 'o';
                stateLabel = 'I';
            }
            else {
                inValve = 'x';
            }
            //check piston
            if (pistonUp & positionMask){
                upPiston = 'T';
                downPiston = ' ';
                if (cylinderFire & positionMask) {
                    chamber = '*';
                    stateLabel = 'P';
                }
            }else {
                upPiston = ' ';
                downPiston = 'T';
            }
            //test out valve
            if (outValvesOpen & positionMask){
                outValve = 'o';
                stateLabel = 'E';
            } else {
                outValve = 'x';
            }

            d3.replace(offset + 1, 1, toString(inValve));
            d3.replace(offset + 3, 1, toString(chamber));
            d3.replace(offset + 4, 1, toString(upPiston));
            d3.replace(offset + 5, 1, toString(chamber));
            d3.replace(offset + 7, 1, toString(outValve));
            d4.replace(offset + 4, 1, toString(downPiston));
            d6.replace(offset + 4, 1, toString(stateLabel));

            positionMask >>= 1 ;
        }

        cout << d1 << endl;
        cout << d2 << endl;
        cout << d3 << endl;
        cout << d4 << endl;
        cout << d5 << endl;
        cout << d6 << endl << endl;

        int bitMask3 = 0b0010;
        int bitMask4 = 0b0001;
        if (cylinderFire & bitMask3){
            cylinderFire = rotateLeft(cylinderFire,1);
            pistonUp = rotateLeft(pistonUp,1);
            inValvesOpen = rotateLeft(inValvesOpen,1);
            outValvesOpen = rotateLeft(outValvesOpen,1);
        }
        else if (cylinderFire & bitMask4){
            cylinderFire = rotateLeft(cylinderFire,3);
            pistonUp = rotateLeft(pistonUp,3);
            inValvesOpen = rotateLeft(inValvesOpen,3);
            outValvesOpen = rotateLeft(outValvesOpen,3);
        }
        else {
            cylinderFire = rotateLeft(cylinderFire,2);
            pistonUp = rotateLeft(pistonUp,2);
            inValvesOpen = rotateLeft(inValvesOpen,2);
            outValvesOpen = rotateLeft(outValvesOpen,2);
        }
    }

    return 0;
}
