/*
AUTHOR: AMANDA MOLLING;
COURSE: COSC 2326.001 FALL 2015 MW19;
INSTRUCTOR: THAYER;
program 1: 0 PURPOSE: EXPLORE THE REPRESENTATION OF 
						CHARACTER, INTEGER AND 
						FLOATING-POINT DATA 


*/
#include<iostream>
#include<cmath>
#include<bitset>

//Create union for float because bitwise operators can only be applied to itegral data types (char, short, int, long, etc)
union Float{
	int intView;
	float floatView;
};

void printChar(char);

void printShort(short);

void printFloat(Float);



int main() {
	int userSelection = 1;
	std::cout <<"Menu:" << std::endl;
	std::cout <<"	0 - Exit \n";
	std::cout <<"	1 - Print the binary representation of a character\n";
	std::cout <<"	2 - Print the binary representation of a short integer \n";
	std::cout <<"	3 - Print the binary represenation of a float \n\n";
	std::cout<<"	4 - Print the binary representation of a character (bitset)\n";
	std::cout<<"	5 - Print the binary representation of a short (bitset)\n";
	std::cout<<"	6 - Print the binary representation of a float (bitset)\n\n";	
	
	while(userSelection){

		std::cout <<"Enter your choice: \n\n"; 
		std::cin >> userSelection;
		std::cout << std::endl;
					
		if (userSelection==1){
			//printchar
			char c;
			std::cout << "Enter a character: ";
			std::cin >> c;
			std::cout<<"\nThe (character) binary representation for " << c << " is: ";
			printChar(c);
		}
		if (userSelection==2){
			//print short
			short s;
			std::cout << "Enter short integer value: ";
		//	std::cin >> s;
			
			while(!(std::cin >> s) )
			{
				std::cout << "Integer, please! \n" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000000, '\n');
				std::cout << "Enter short integer value: ";
			}			
			std::cout<<"\nThe (short int) binary representation for " << s << "  is: ";
			printShort(s);
		}
		if (userSelection==3){
			//print float
			Float f;
			std::cout << "Enter a float: ";
	//		std::cin >> f.floatView;
			while(!(std::cin >> f.floatView) ){
				std::cout << "\nNumeric, please! \n" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000000, '\n');
				std::cout << "Enter a float: ";
			}		
			std::cout<<"\nThe (float) binary representation for " << f.floatView << " is: ";		
			printFloat(f);
		}
		if (userSelection==4){
			char bitChar;
			std::cout << "Enter a character: ";
			while( !(std::cin >> bitChar ) ){
				std::cout << "\nSingle character value, please! \n" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000000, '\n');
				std::cout << "Enter a character: ";
			}
			
			std::bitset<8> a(bitChar);

			std::cout<<"\nThe (character, bitset) binary representation for " << bitChar << " is: " << a << "\n";		
		}
		if (userSelection==5){
			short bitShort;
			std::cout << "Enter a short int: ";
			while( !(std::cin >> bitShort ) ){
				std::cout << "\nSingle int value, please! \n" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000000, '\n');
				std::cout << "Enter a character: ";
			}
			
			std::bitset<16> a(bitShort);

			std::cout<<"\nThe (short, bitset) binary representation for " << bitShort << " is: " << a << "\n";		
			
		}
		if (userSelection==6){
			Float bitFloat;
			std::cout << "Enter a float: ";
			while( !(std::cin >> bitFloat.floatView ) ){
				std::cout << "\nFloat value, please! \n" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000000, '\n');
				std::cout << "Enter a float: ";
			}
			
			std::bitset<32> a(bitFloat.intView);

			std::cout<<"\nThe (float, bitset) binary representation for " << bitFloat.floatView << " is: " << a << "\n";		

		}
		std::cout<<"\n\n";
		
	}
}


void printChar(char c){
	char sizeChar;
	unsigned int mask = pow( 2 , (sizeof(sizeChar) * 8 - 1)) - 0;
	for (int counter = (sizeof(sizeChar) * 8 - 1); counter >= 0; counter--){
		if ( (mask & c) != 0){
			std::cout << "1";
		//	std::cout << mask;
		}
		else{
			std::cout << "0";
		}
		if (counter % 4 == 0){
			std::cout<<" ";
		}
		mask = mask >> 1;
	}
};

void printShort(short s){
	short sizeShort;
	unsigned int mask = pow( 2 , (sizeof(sizeShort) * 8 - 1)) - 0;
	for (int counter = (sizeof(sizeShort) * 8 - 1); counter >= 0; counter--){
		if ( (mask &s) != 0){
			std::cout << "1";
		//	std::cout << mask;
		}
		else{
			std::cout << "0";
		}
		if (counter % 4 == 0){
			std::cout<<" ";
		}
		mask = mask >> 1;
	}
};


void printFloat(Float f){
	Float sizefloat;
	unsigned int mask = pow( 2 , (sizeof(sizefloat.intView) * 8 - 1)) - 0;
	for (int counter = (sizeof(sizefloat.intView) * 8 - 1); counter >= 0; counter--){
		if ( (mask &f.intView) != 0){
			std::cout << "1";
		//	std::cout << mask;
		}
		else{
			std::cout << "0";
		}
		if (counter % 4 == 0){
			std::cout<<" ";
		}
		mask = mask >> 1;
	}
};


/* 

Questions:

1. From the result of -115,
we can see that -115 is stored
in two' complement notation.

2. For 1.115, the binary is represented as 
0011 1111 1000 1110 1011 1000 0101 0010

This is one bit for sign, followed by 8 bits for the whole numbers and 
23 bits for the mantissa.

so we have 0 = positive,
			0111 1111 	.	0001 1101 0111 0000 1010 010
		 			1	.  1/16 + 1/32 + 1/64 + 2^-256 + 2^-1024 + 2^-2048 + 2^-4096 + 2^-13107 + 2^-524288 + 2^-2097152

OUTPUT: 

Menu:
        0 - Exit
        1 - Print the binary representation of a character
        2 - Print the binary representation of a short integer
        3 - Print the binary represenation of a float

        4 - Print the binary representation of a character (bitset)
        5 - Print the binary representation of a short (bitset)
        6 - Print the binary representation of a float (bitset)

Enter your choice:

1

Enter a character: C

The (character) binary representation for C is: 0100 0011

Enter your choice:

2

Enter short integer value: 115

The (short int) binary representation for 115  is: 0000 0000 0111 0011

Enter your choice:

2

Enter short integer value: -115

The (short int) binary representation for -115  is: 1111 1111 1000 1101

Enter your choice:

3

Enter a float: 1.115

The (float) binary representation for 1.115 is: 0011 1111 1000 1110 1011 1000 01
01 0010

*/

