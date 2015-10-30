#include <iostream>
#include <iomanip>
#include <assert.h>
#include <fstream>
#include <cstring>
#include <typeinfo>
#include <math.h>

using namespace std;

enum sign_t{pos, neg}; // define a new datatype, sign_t, for Fraction

class Fraction {
	private:	 // better: keep private to avoid corruption
		sign_t sign;       // can ONLY be pos or neg Fraction();
		unsigned num, den; // numerator, denominator
		
	public:
		Fraction(sign_t in_sign, unsigned in_num, unsigned in_den=1){ // if no denominator, use 1
			sign=in_sign;
			num=in_num;
			den=in_den;
		}
		
		Fraction(string i = ""){  // If I redid the program, I would change string i to string strFrac
				/*  Algorithm to :
						parse i up fracBarLocation
						split and send first half to first part of Fraction class (fNumeratorA)
						split and send second half to second part of Fraction class (fDenomA)
				*/
					
			if(i == ""){
				sign=pos;
				num=1;
				den=1;
			}
			else{

				if ( i.find('-') == 0){	 // Check sign -- if '-' is first char of string i, then neg; (none of txt file has this, but could to know.
					sign = neg;
					cout << "found negative #";
				}
			
				else 
					sign = pos;
			
				int fracBarLocation = i.find('/');		// raw output of find returns garbage if not cast, -1 if cast to int.
				string fracNumeratorA(i);              //Make a copy of i to parse
				string fracDenomA(i);
				if (fracBarLocation>(-1)){
					fracNumeratorA.erase(fracBarLocation, i.length() - fracBarLocation); //remove the second half of fraction A so that only the numerator part remains
					fracDenomA.erase(0, i.length() - fracBarLocation);	//remove the first have of fraction A so that only the denominator part remains
				}
				else{
					//The fraction here doesn't have a '/' so I assume it is an integer.
					//Further error checking could find this to be something else 
					//and exit, but that is for a more advanced program.
					fracNumeratorA = i;
					fracDenomA = "1";     //Send a 1 to the denom in order to not have to change our Fraction class much.
				}			
				num = stoi(fracNumeratorA);
				den = stoi(fracDenomA);
				//Fraction (pos, stoi(fracNumeratorA), stoi(fracDenomA));				//Since fracNum and fracDen were streamed as a string, 
				//use stoi to convert to int.
			}
		}
		void reduce(){
			if (fmod(num, den) == 0){ //evenly divisible, so divide
				num = num/den;
				den = 1;	
			}
			else{
				for (int i = den; i > 1; i--){ //check if divisible by GCF
					if ( (fmod(num, i) == 0) && (fmod(den, i) == 0) ){
						num /= i; //divide both and store
						den /= i;
						break; //if gcf found, no need to find smaller gcf, we are done.
					}
				}
			}
		}
		
		void show() const { // getter should be const!
			if (sign==neg) cout<<'-';
			if (den == 1) 
				cout << num;
			else 
				cout<<num<<'/'<<den;
		}
		
		string writeToFile()  const{
			if (den == 1) 
				if (sign==neg)
					return "-" + to_string(num);
				else
					return to_string(num);
			else 
				if (sign==neg)
					return ( "-" + to_string(num) + '/' + to_string(den) );
				else
					return (to_string(num) + '/' + to_string(den) );
		}
    friend Fraction add(Fraction a, Fraction b);
    friend Fraction subtract(Fraction a, Fraction b);
    friend Fraction multiply(Fraction a, Fraction b);
    friend Fraction divide(Fraction a, Fraction b);
	friend ostream &operator<<(ostream &output, Fraction &a){
		output << a.writeToFile();
		return output;
	}
	
	friend istream &operator>>(istream &input, Fraction &ab){
		string i;
		input >> i;
		ab = Fraction(i);
		return input;
	}   	
};



Fraction operator+(Fraction a, Fraction b) {
	return add(a, b);
}

Fraction operator-(Fraction a, Fraction b){
	return subtract(a,b);
}

Fraction operator*(Fraction a, Fraction b){
	return multiply(a, b);
}

Fraction operator/(Fraction a, Fraction b){
	return divide(a, b);
}

Fraction add(Fraction a, Fraction b) {
	unsigned bottom=a.den*b.den; // common denomominator
	unsigned top = a.num*b.den+a.den*b.num;
	sign_t new_sign=pos;
	if (a.sign != b.sign) new_sign=neg;
	Fraction answer(new_sign, top, bottom);
	return answer;
}

Fraction subtract(Fraction a, Fraction b){
	sign_t new_sign=pos;
	unsigned bottom = a.den*b.den;
	unsigned top;
	if ( ( (a.num *b.den) > (b.num * a.den) ) && (a.sign == pos) ) 
		top = a.num*b.den-a.den*b.num;
	else if ( (a.num * b.den) < (b.num * a.den) ) {
		top = a.den*b.num-a.num*b.den;
		new_sign = neg;
	}
	else if ( (a.num * b.den) == (b.num * a.den)){
		Fraction answer(pos, 0, 0);
	}
	Fraction answer(new_sign, top, bottom);
	return answer;
}
Fraction multiply(Fraction a, Fraction b){	
	sign_t new_sign=pos;
	if(a.sign!=b.sign) new_sign = neg;
	unsigned bottom = (a.den)*(b.den);
	unsigned top = (a.num)*(b.num);
	Fraction answer(new_sign, top, bottom);
	return answer;
}

Fraction divide(Fraction a, Fraction b){
	sign_t new_sign = pos;
	if(a.sign!=b.sign) new_sign = neg;
	unsigned bottom = (a.den * b.num);
	unsigned top = a.num*b.den;
	Fraction answer(new_sign, top, bottom);
	return answer;
}

Fraction do_op(char op, Fraction a, Fraction b){
	switch(op){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
	}
}


int main(){
	
	// --- Input Section ---
	string fileDefaultName = "fractions.txt";
	string fileName;
	cout<<"Name of input file please... \n";
	getline(cin, fileName);
	if(fileName.rfind(".txt") > 10000) fileName.append(".txt"); 
	ifstream fileIn;
	fileIn.open(fileName);
	if (fileIn.fail()){
		fileIn.close();
		cerr << "No appropriate data name, using default as " ;
		cerr << fileDefaultName << "\n"; 
		fileName = fileDefaultName;
		fileIn.open(fileName);
		if(fileIn.fail()){
			fileIn.close();
			cerr << "TestData.txt does not exist and no other file name given. Aborting. \n";
			exit(1);
		}
	}
	
	// --- Output Section ---
	// Output name needs to be MW19_L2_Molling_filename_output.txt

	string outFileName= "MW19_L2_Molling_";
	outFileName.append(fileName.erase(fileName.rfind(".txt"), 4));
	outFileName.append("_output.txt");
	
	cout << "Output file name is " << outFileName << "\n\n";
	ofstream outFile;
	outFile.open(outFileName);
	Fraction fA = Fraction(); 
	Fraction fB = Fraction(); 
	char operate;
	while( !(fileIn.eof())){
		fileIn>>fA;
		fileIn>>operate;
		fileIn>>fB;
		Fraction result = do_op(operate, fA, fB);
		result.reduce();
		cout << fA << " " << operate <<" " << fB << " " << "=" << " " << result << "\n";
		outFile << fA <<" " << operate <<" " << fB << " " << "=" << " " << result;
		outFile << "\n";

 	}
 	
 	cout << "\nProcessed file \n";
 	fileIn.close();
 	outFile.close();
 	
}

/* Sample output

Name of input file please...
CopyTestData
Output file name is MW19_L2_Molling_CopyTestData_output.txt

7/8 - 12/13 = -5/104
10 - 22 = -12
20 * 1/2 = 10
3/4 - 8 = -29/4
2/3 + 3/4 = 17/12
1/2 * 4/5 = 2/5
7/8 - 1/3 = 13/24
10 + 5 = 15
999 + 1 = 1000

Processed file

*/
