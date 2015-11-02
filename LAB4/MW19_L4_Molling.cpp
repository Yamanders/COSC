/* 
AUTHOR: AMANDA MOLLING A17020308
COURSE: COSC 2326.001 FALL 2015 MW19 ; INSTRUCTOR: THAYER
LAB 4: PURPOSE: EVALUATE  POSTFIX EXPRESSIONS USING STL STACK AND 
        USER DEFINED STACK
*/


#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<stack>

using namespace std;
bool testingOFF = true; 
bool DEBUG = !testingOFF;   // I am very lazy....

/* FROM textbook:
postfix expression is received and its value is returned (unless an error
occurred). A stack is used to store operands. 
1. Initialize an empty stack.
2. Repeat the following until the end of the expression is encountered:
a. Get the next token (constant, variable, arithmetic operator) in the postfix expression.
b. If the token is an operand, push it onto the stack. If it is an operator,
then do the following:
i. Pop the top two values from the stack. (If the stack does not contain two items, an error due to a malformed postfix expression has
occurred and evaluation is terminated.)
11. Apply the operator to these two values.
111. Push the resulting value back onto the stack.
3. When the end of the expression is encountered, its value is on top of the stack.
In fact, it must be the only value in the stack and if it is not, an error due to a
malformed postfix expression has occurred.
*/

typedef int StackElementType;

class Stack {
  private:
    int size=0;              // current size of stack (optional, for fast access)
    class Element{
        public:
            StackElementType data;
            Element * next = nullptr;
            Element(){};
            Element(StackElementType data){
                this->data=data;
                this->next=nullptr;
            };
			Element(StackElementType newData, Element* newNext){
				data = newData;
				next = newNext;
			}
    };
  public:
    typedef Element *ElementPointer;
    ElementPointer myTop;   // pointer to dynamic array
    Stack();  // constructor
    Stack(StackElementType value);
    ~Stack(); // destructor
    Stack(const Stack & origStack); // copy constructor
    const Stack & operator=(const Stack & rightHandSide); // assignment operator
    bool is_empty() const; // is it empty? true if empty; false if not empty
    void push(StackElementType item); // assume this always works (could fail if computer out of memory)
    // Two kinds of pop (overloaded), implement both if you have time
    StackElementType pop(); // return (and remove) top element on stack; if stack is empty, return 0 (Risky, but convenient!)
    bool pop(StackElementType &item); // if empty return false; else copy top element on stack into item, remove top element, return true
    //void pop();
    void display(ostream & out) const; // display entire contents of list on one line, separate by spaces
	//void end_of_stack();
    bool evaluate_postfix(string line);
    void clear();
    int returnSize();
};
int Stack::returnSize(){
    int count = 0;
    Element *runner = myTop;
    while(runner){
        count++;
        if(runner->next){
            runner=runner->next;   
        }
        else{
            return count;
        }
    }
    return count;        
}

void Stack::clear(){
    while(!is_empty()){
        pop();
    }
}

/*void Stack::end_of_stack(){
	Element* runner = myTop;
	Element* lastNext = runner;
	while(runner!=nullptr){
		lastNext=runner;
		runner=runner->next;
	}
	cout<<"End of list: "<<(lastNext->next)<<" !\n";
}
*/

ostream & operator<<(ostream & out, const Stack & aStack){
    aStack.display(out); 
    return out;
}; // this can call display() (Avoid duplicate code)
Stack::Stack(){
    myTop=nullptr;
};
Stack::Stack(StackElementType value){ 
    myTop = new Element(value) ;
};

Stack::Stack(const Stack & origStack){ // copy constructor.
    if (!origStack.is_empty()){
        myTop=nullptr;
    }
    else{
        myTop = new Element(origStack.myTop->data, origStack.myTop->next); //make new element using origStack header data and next;
        Element *runner = myTop;    //start runner at the top
        Element *origRunner = origStack.myTop;
        while(runner->next!=nullptr){   //while we are not at the bottom of stack
            origRunner=origRunner->next;    
            runner->next = new Element(origRunner->data, origRunner->next);
            runner=runner->next;
        };
    };
}

/*Stack::Stack(string str, int strLength){
    //Stack newStack;
    //head->data = str[0];
    Element *runner = new Element(str[0]);
    myTop=runner;
    cout<<"my length is "<<strLength;
    for(int i = 1; i<strLength-1;i++){
    //for (int i = strLength - 2; i < 1; i--){
        runner->next=new Element(str[i]);
        runner=runner->next;
        cout<<"stri "<<str[i]<<"i is"<<i<<'\n';
    };
}
*/


Stack::~Stack(){
    ElementPointer currPtr = myTop, nextPtr;
    while(currPtr!=0){
        nextPtr = currPtr->next;
        delete currPtr;
        currPtr = nextPtr;
    }
}
void Stack::push(StackElementType item){
    ElementPointer newElement = new Element(item);
    newElement->next = myTop;
    myTop=newElement;
};

StackElementType Stack::pop(){
    StackElementType topData=myTop->data;
    Element *runner = myTop;
    myTop = myTop->next;
    delete runner;
    return topData;
};

bool Stack::pop(StackElementType &item){  // if empty return false; else copy top element on stack into item, remove top element, return true
    bool popped = false;
    if( is_empty() ) {
        popped=false;
    }
    else{
        Element *runner = myTop;
        item=myTop->data;
        if(myTop!=nullptr){
            myTop = myTop->next;
            delete runner;
            popped=true;
        }
    }
    return popped;
}



const Stack & Stack::operator=(const Stack & rightHandSide){
    while(myTop!=nullptr){  //Deallocate all of the data BEFORE we start adding
        pop();
    };
    Element *right_runner = rightHandSide.myTop; 
    Element *runner = new Element(right_runner->data, right_runner->next);
    myTop = runner;
    while(runner->next!=nullptr){
        right_runner=right_runner->next;        
        runner->next = new Element(right_runner->data, right_runner->next);
        runner=runner->next;
    }
    return *this;
}

enum operation_t {add, subtract, multiply, divide}; // create "codes" for operators

void evaluate(Stack &stack) {
  // pop 3 items from stack, expected in postfix order
  // evaluate the expression, push the result. Example: 1+2 (infix) is 12+ (postfix)
  // push operation=+, push A=1, push B=2   call evaluate()
  // pop B=2, pop A=1, pop operation=add; result=1+2=3, push result
  StackElementType A, B, operation, result;
  if (stack.is_empty()) return; // stop right here!
  if (stack.pop(B) and stack.pop(A) and stack.pop(operation)) { 
    switch (operation) {            // switch does not work unless you add case....
      case add:       result=A+B; break;
      case subtract:  result=A-B; break;
      case multiply:  result=A*B; break;
      case divide:    result=A/B; break;
      default:   result=0;   break; // invalid operation
    }
    stack.push(result);
  }
}

bool isAllDigits(string str){   //check if entire string is digits (I am checking if this is a valid number)
    for(int i = 0; i < str.length(); i++){
        if(!isdigit(str[i])){
            return false;
        }
    }
    return true;
}

bool Stack::evaluate_postfix(string line){
    if(line==""){//Stop right there.
        return false; 
    }
    bool validExpression = true; //Can I get a result?
    stringstream ss;//crunch the spaces.
    ss<<line;
    string phrase;  //this is a part of line ie. 9 or 57 or +
    StackElementType dataA=0;   //temp values for calculating.
    StackElementType dataB=0;
    int result;
    while(ss>>phrase){
        //is phrase all digits or one of the fours symbols, with length==1?
        if( (isAllDigits(phrase))|| (phrase[0]=='+') ||( phrase[0]=='-') ||(phrase[0]=='*')
            ||(phrase[0]=='/') && (phrase.length()==1)){
            switch(phrase[0]){
                case '+':       if( pop(dataA) and pop(dataB)){ 
                                    result=dataA+dataB; push(result);
                                }
                                else{
                                    return false;
                                }
                                if(DEBUG){  cerr<<"result is "<<result; }
                                break;  
                case '-':       if( pop(dataA) and pop(dataB)){ 
                                    result=dataB-dataA; 
                                    push(result);
                                }
                                else{   
                                    return false;
                                }
                                if(DEBUG){  cerr<<"result is "<<result; }
                                break;         
                case '*':       if( pop(dataA) and pop(dataB)){ 
                                    result=dataA*dataB; push(result);
                                }
                                else{
                                    return false;
                                }
                                if(DEBUG){  cerr<<"result is "<<result; }
                                break;  
                case '/':       if( pop(dataA) and pop(dataB)){ 
                                    result= dataB/dataA; push(result);
                                }
                                else return false;
                                if(DEBUG){ 
                                    cerr<<"result is "<<result; 
                                }
                                break;  
                default:        push( stoi(phrase) );  
                                if(DEBUG){
                                    cerr<<"pushing "<< stoi(phrase);
                                }
                                break;
            };
        }
        else{
            validExpression=false;  //we encountered some sort of symbol that we didn't like.(=, &, etc)
            return validExpression;
        };
    };
    if(returnSize()!=1){    //we didn't use all of the numbers pushed on the stack (num. operands> num.operators - 1)
        validExpression=false;
    };
    return validExpression;
}
void Stack::display(ostream & out) const{
    Element *runner=myTop;
    //out<<"<top> ";    //Didn't need to specify top and bottom.
    int count=1;
    while(runner){
        out<<runner->data<<" ";
        count++;
        if(runner->next == nullptr) break;
        else{
            runner=runner->next;
        }
    }
    //out<<"<bottom> ";
}

bool Stack::is_empty() const{
    Element *runner = myTop;
    if(!runner)
        return true;
    else
        return false;
}

//evaluate postFix using STL.
int eval_postfix(string line){
    if(line==""){   
        throw "Empty line";
    };
    stack<StackElementType> myStack;
    StackElementType dataA;
    StackElementType dataB;
    int result; 
    stringstream ss;
    ss<<line;
    string phrase;
    while(ss>>phrase){
        if(DEBUG){  cout<<"phrase is "<<phrase<<endl; }
        if( isAllDigits(phrase)){
            myStack.push( stoi(phrase));
        }
        else if( (phrase.length()==1) && ( (phrase[0] == '+')||(phrase[0]=='-')||(phrase[0]=='*')||(phrase[0]=='/') ) ){
            switch(phrase[0]){
                case '+':       //if( dataA = myStack.top() and (myStack.pop(); dataB=myStack.top()) ) { result=dataA+dataB; myStack.push(result);}
                                if( (myStack.size()>1) ){
                                    dataA = myStack.top(); myStack.pop(); dataB=myStack.top(); myStack.pop(); 
                                    result = dataA+dataB; myStack.push(result);
                                }
                                else throw "Invalid";
                                if(DEBUG){  cerr<<"result is "<<result; }
                                break;  
                case '-':       //if( myStack.pop(dataA) and pop(dataB)){ result=dataB-dataA; push(result);}
                                if(myStack.size()>1){
                                    dataA = myStack.top(); myStack.pop(); dataB=myStack.top(); myStack.pop(); 
                                    result = dataB-dataA; myStack.push(result);
                                }
                                else throw "Invalid";
                                if(DEBUG){  cerr<<"result is "<<result; }
                                break;         
                case '*':       //if( pop(dataA) and pop(dataB)){ result=dataA*dataB; push(result);}
                                if(myStack.size()>1){
                                    dataA = myStack.top(); myStack.pop(); dataB=myStack.top(); myStack.pop(); 
                                    result = dataA*dataB; myStack.push(result);
                                }
                                else throw "Invalid";
                                if(DEBUG){  cerr<<"result is "<<result; }
                                break; 
                case '/':       //if( pop(dataA) and pop(dataB)){ result= dataB/dataA; push(result);}
                                if(myStack.size()>1){
                                    dataA = myStack.top(); myStack.pop(); dataB=myStack.top(); myStack.pop(); 
                                    result = dataB/dataA; myStack.push(result);
                                }
                                else throw "Invalid";
                                if(DEBUG){  cerr<<"result is "<<result; }
                                break;         
            }
        }
        else{   //encountered some sort of other char ($,^, =, etc)
            throw "Expression not valid\n";
        }
    }
    if(DEBUG){cerr<<"returning.\n";}    //what's on the stack?
    return myStack.top();
}



int main(){
    char input;
    string lineIn;
    string postInputStr;
    Stack myStack;
    cout<<"Welcome to the postfix expression evaluator! You may:\n"
    "enter a single expression, enter a filename with many expressions \n"
    "(one per line), or quit at any time. Please begin.\n";
   
    while(input!='q'){
        cout<<"\ne)xpression; f)ilename; s)TL implementation(file) q)uit. Your option? \n";
        getline(cin, lineIn);
        input=lineIn[0];
        if(input=='f'){
            string fileDefaultName="postfix_test_data.txt";// just in case your filename isn't valid.
            string fileName;
            ifstream inFile;
            if(testingOFF){ 
                cout<<"Enter filename\n";
                getline(cin,fileName);
                cout<<"\n";
                unsigned int txtPos = fileName.find(".txt");//index of .txt
                if( txtPos>1000){//not found.
                    string suffix = ".txt";
                    fileName.append(suffix);//append
                }
                inFile.open(fileName);
                if(inFile.fail()){
                    cout<<"No file by that name could be open.\nUsing default name "<<fileDefaultName<<"\n\n";
                    fileName="postfix_test_data.txt";
                    inFile.open(fileName);
                    if(inFile.fail()){   //Default couldn't be opened either.                    
                        cerr<<"Failed to open file. \n";

                    }
                }
            } 
            else{
                inFile.open(fileDefaultName);  //if testing, just use default File name.
            }                       
            while( !(inFile.eof())){
                getline(inFile,postInputStr);
                if( myStack.evaluate_postfix(postInputStr) ){ //if the expression evaluates properly, otherwise skip it.
                    cout<<postInputStr;
                    cout<<" evaluates to ";
                    myStack.display(cout);
                    cout<<"\n";
                    //cout<<"\n MyStack size "<<myStack.returnSize();
                    
                }
                myStack.clear();
            }
        }
        else if(input=='e'){
            cout<<"Enter postfix/RPN expression: ";
            if(testingOFF){
                getline(cin,postInputStr); 
            }
            else{ 
                postInputStr="20 30 40 + *"; cerr<<"postInputSt " <<postInputStr<<"\n"; 
            }
            
            if( myStack.evaluate_postfix(postInputStr) ){ //if the expression evaluates properly.
                cout<<postInputStr;
                cout<<" evaluates to ";
                myStack.display(cout);
                cout<<"\n";
                //cout<<"\n MyStack size "<<myStack.returnSize();
            }
            else{
                cout<<"Expression not valid.\n";                        
            }
            myStack.clear();
        }
        else if(input=='s'){
            stack<StackElementType> mySTLstack;
            string fileDefaultName="postfix_test_data.txt";
            string fileName;
            ifstream inFile;
            if(testingOFF){ 
                cout<<"Enter filename\n";
                getline(cin,fileName);
                cout<<"\n";
                unsigned int txtPos = fileName.find("txt");
                if( txtPos>1000){
                    string suffix = ".txt";
                    fileName.append(suffix);
                }
                inFile.open(fileName);
                if(inFile.fail()){
                    cout<<"No file by that name could be open.\nUsing default name "<<fileDefaultName<<"\n\n";
                    fileName="postfix_test_data.txt";
                    inFile.open(fileName);
                    if(inFile.fail()){                       
                        cerr<<"Failed to open file. \n";

                    }
                }
            } 
            else{
                inFile.open(fileName);
            }                       
            while( !(inFile.eof())){
                getline(inFile,postInputStr);
                
                try { //learned how to do this! :)
                    int result = eval_postfix(postInputStr);
                    cout<<postInputStr;
                    cout<<" evaluates to "<<result;
                    //mySTLstack.display(cout);
                    cout<<"\n";
                    //cout<<"\n MyStack size "<<myStack.returnSize();
                } 
                catch(...){
                    //directions unclear as to whether to ignore an invalid line or to print it, this does work though.
                   // cout<<"Not a valid expression.\n";
                }; 

            }
        }            
    
    }
    
}

/*output

Welcome to the postfix expression evaluator! You may:
enter a single expression, enter a filename with many expressions
(one per line), or quit at any time. Please begin.

e)xpression; f)ilename; s)TL implementation(file) q)uit. Your option?
s
Enter filename


No file by that name could be open.
Using default name postfix_test_data.txt

9 2 1 + / 4 * evaluates to 12
2 3 + evaluates to 5
20 30 40 + * evaluates to 1400
5 3 + 2 /  evaluates to 4
123 evaluates to 123
80 9 + evaluates to 89
1000 200 30 4 + + + evaluates to 1234
6 4 2 1 * / * evaluates to 12
3 1 * 8 + 2 * 11 / evaluates to 2
8 5 3 + 2 / evaluates to 4
1000 200 30 4 - - -  evaluates to 826
10 20 30 40 evaluates to 40
1 2 3 4 + + + evaluates to 10

e)xpression; f)ilename; s)TL implementation(file) q)uit. Your option?
f
Enter filename


No file by that name could be open.
Using default name postfix_test_data.txt

9 2 1 + / 4 * evaluates to 12
2 3 + evaluates to 5
20 30 40 + * evaluates to 1400
5 3 + 2 /  evaluates to 4
123 evaluates to 123
80 9 + evaluates to 89
1000 200 30 4 + + + evaluates to 1234
6 4 2 1 * / * evaluates to 12
3 1 * 8 + 2 * 11 / evaluates to 2
1000 200 30 4 - - -  evaluates to 826
1 2 3 4 + + + evaluates to 10

e)xpression; f)ilename; s)TL implementation(file) q)uit. Your option?
e
Enter postfix/RPN expression: 10 20 +
10 20 + evaluates to 30

e)xpression; f)ilename; s)TL implementation(file) q)uit. Your option?
e
Enter postfix/RPN expression: 10 =
Expression not valid.

e)xpression; f)ilename; s)TL implementation(file) q)uit. Your option?
10 20 30

e)xpression; f)ilename; s)TL implementation(file) q)uit. Your option?
e
Enter postfix/RPN expression: 10 20 30
Expression not valid.

e)xpression; f)ilename; s)TL implementation(file) q)uit. Your option?
q


*/
