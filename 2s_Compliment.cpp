#include <cstdlib>
#include <iostream>
#include <cmath>  

#define MAX 8

using namespace std;

int *convertNum(int);
void summation (int[], int[], int, int);

int main()
{
    int input1, input2;
	int *binaryVal1, *binaryVal2;

        cout << "Please enter an integer within that is between -128 ~ 127: ";
        while ((!(cin >> input1)) || ((input1 < -128) || (input1 > 127)))
        {
            cin.clear();        //clear the buffer for the cin
            cin.ignore(1000, '\n');

            cout << "Invalid datatype or number entered was outside the boundaries mentioned. \nPlease enter another integer: " << flush; //error prompt
        } 
            
		binaryVal1 = convertNum(input1);
		/*ptr1 equals the contents of the address of binaryVal1*/
		int *ptr1 = *(&binaryVal1);
				
		/*Converts the value returned by the convertNum funct, 
		which is pointed to by ptr1, to an int[] instead of (int*)[]*/
		int array1[MAX];
		for (int a = 0; a < MAX; ++a)
			array1[a] = *(ptr1+a);
						
        cout << "\n\nPlease enter another number: ";
        while ((!(cin >> input2)) || ((input2 < -128) || (input2 > 127)))
        {
            cin.clear();        //clear the buffer for the cin
            cin.ignore(1000, '\n');

            cout << "Invalid datatype or number entered was outside the boundaries mentioned.\nPlease enter another integer: " << flush; //error prompt              
        }
      
		binaryVal2 = convertNum(input2);
		/*ptr1 equals the contents of the address of binaryVal2*/
		int *ptr2 = *(&binaryVal2);
		
		/* Converts the value returned by the convertNum funct, 
		which is pointed to by ptr, to an int[] instead of (int*)[] */	
		int array2[MAX];
		for (int bb = 0; bb < MAX; ++bb)
			array2[bb] = *(ptr2 + bb);
			
        cout << "\n\nCalculating the total.....\n";
      
        summation(array1, array2, input1, input2);

    cin.get();  
    return 0;
}

int *convertNum(int x)
{
    int origin = x;
    int tmp = x;            			//uses the parameter as a temp value for further calculations
    static const int max = 8;            //max amount of digits for this binary system
    static int num[max] = {0,0,0,0,0,0,0,0};      /* declares an integer array and makes this function able to
									  return an array as a return value	*/
                                    
    if (origin >= 0)
    {    cout <<"\nThe number <"<< origin <<"> has been converted to: ";
      
        for (int i = max-1; i >= 0; --i)//decrement the position of the array pointer
        {
            num[i] = tmp % 2;     //sets the binary digit to the value calculated
            tmp = tmp / 2;          //divides by 2 and set it to the new value of "tmp"
        }                           //End of for loop
        for (int ab = 0; ab <= max-1; ++ab)
            cout << num[ab];
    }
  
    else if (origin < 0)                //checks if the number converted was negative
    {
        int carry = 0;
        int tcsum = 0;
        int pos_tmp = abs(tmp);
      
        for (int ct = max-1; ct >= 0; --ct)//decrement the position of the array pointer
        {
            num[ct] = pos_tmp % 2;     //sets the binary digit to the value calculated
            pos_tmp = pos_tmp / 2;          //divides by 2 and set it to the new value of "tmp"
        }    
      
        cout <<"\nThe absolute value of the <"<<origin<<"> is "<<abs(origin)<<" which in binary is: ";
        for (int f = 0; f < max; ++f)
            cout <<num[f];
      
        cout <<"\n\n1's Compliment of <"<<origin<<"> is: ";
        for (int a = 0; a < max; ++a)   //iterates through the array
        {
            if (num[a] == 1)    //checks if the array counter value = 1          
                num[a] = 0;    //if so, flip the 1 bits to 0
            
            else   //same for if it is 0
                num[a] = 1;    //flip the 0 bits to 1   
        }
      
        for (int foo = 0; foo < max; ++foo)
            cout <<num[foo];
          
          cout <<"\n\n";   

                //Add 1 to the 1's compliment if the array
        tcsum = num[max-1] + 1;        //num[0] is now the last element since the array is in reverse, so num[last] + 1 = the sum of the column

        if (tcsum == 1)         // if the num[0] = 0, so add 1 while there carry bit is currently 0, would make num[0] = 1, now
            num[max-1] = 1;
        
		else if (tcsum == 2)
        {  
            num[max-1] = 0;
            carry = 1;          //set the carry bit to 1
                                
            for (int b = max-2; b >=0 ; --b)  //starting from the end of the binary number, since its read in reverse so last -> first and vice versa
            {
                tcsum = 0;
                tcsum = num[b] + carry;
                num[b] = tcsum % 2;
                carry = tcsum / 2;
            }       
        } 
      
        cout <<"The 2's Compliment of <"<< origin <<"> is: ";
        for (int y = 0; y <= max-1; ++y)
            cout << num[y];
    }

    return *(&num);                                 //this returns whatever binary array whether it is positive or negative
  
}//End of the convertNum Function block

void summation(int b1[], int b2[], int c1, int c2)
{
    int answer = 0;
    int carry = 0;
    static const int max = 8;
    int result[max] = {0,0,0,0,0,0,0,0};
  
    for (int lc = max-1; lc >= 0; --lc)
    {
        int column_sum = 0;
        column_sum = b1[lc] + b2[lc] + carry;
        result[lc] = column_sum % 2;
        carry = column_sum / 2;
    }
	/*if the sign bit of both values are not equal or the sign bits of both values are the same and equal to the sign bit from the result, then Valid*/
    if ((b1[0] != b2[0]) || ((result[0] == b1[0]) && (result[0] == b2[0])))
    {
        answer = c1 + c2;
        cout << "\nSum of " << c1 << " and " << c2 <<" is "<< answer <<".\n";                        
        cout << "Answer in Binary: ";
        for (int i = 0; i < max; ++i)
            cout << result[i];
                  
        cout << "\nDescription: This is a valid output.\n";      
    }
    else
    {
        answer = c1 + c2;
        cout << "\nSum of " << c1 << " and " << c2 <<" is "<< answer <<".\n";           
        cout << "Answer in Binary: N/A\n";
        cout << "Description: Overflow has occurred!!\n\n";  
    }
    return;
}
