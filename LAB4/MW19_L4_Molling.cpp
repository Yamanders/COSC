#include <iostream>
#include<string>
#include<fstream>
using namespace std;
bool testingOFF = false;

/* postfix expression is received and its value is returned (unless an error
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
    void evaluate_postfix(string line);
};




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

void Stack::evaluate_postfix(string line){//Stack &stack){
    //if (stack.is_empty()) return; // stop right here!
    if(line=="")    return;
    Stack myStack = Stack();
    int result;
    for(int i = 0; i<line.length(); i++){
        if( (line[i]) ){ //if this char isn't a white space.
            switch(line[i]){
                case add: result=myStack.pop()+myStack.pop();   break;  
                case subtract: result=myStack.pop()+myStack.pop();   break;        
                case multiply: result=myStack.pop()+myStack.pop();   break;
                case divide: result=myStack.pop()+myStack.pop();   break;
                default:    push(line[i]);  break;
            }
            push(result);
        }
    }   
}
void Stack::display(ostream & out) const{
    Element *runner = myTop;
    out<<"<top> ";
    int count = 1;
    while(runner){
        out <<runner->data<<" ";
        count++;
        if(runner->next == nullptr) break;
        else{
            runner=runner->next;
        }
    }
    out<<"<bottom> ";
}

bool Stack::is_empty() const{
    Element *runner = myTop;
    if(!runner)
        return true;
    else
        return false;
}



int main(){
    char input;
    string postInputStr;
    Stack myStack;
    /*cout<<"Welcome to the postfix expression evaluator! You may:"
    "enter a single expression, enter a filename with many expressions 
    "(one per line), or quit at any time. Please begin.\n";
    
*/
    while(input!='q'){
        cout<<"e)xpression; f)ilename; q)uit. Your option? \n";
        cin>>input;
        if(input=='f'){
            string fileName;
            if(testingOFF){ 
                cout<<"Enter filename\n";
                cin>>fileName;
                unsigned int txtPos = fileName.find("txt");
                if( txtPos>1000){
                    string suffix = "txt";
                    fileName.append(suffix);
                }
            }
            else{
                fileName="postfix_test_data.txt";
            }
                     
            ifstream inFile;
            inFile.open(fileName);
            if(inFile.fail()){   
                cerr<<"Failed to open file. \n";
            }
            else{
                while( !(inFile.eof())){
                    getline(inFile,postInputStr);
                    //make line into stack. Check if valid postfix now or at evaluation? Let's try
                    //at evaulation.
                    //Stack newStack = Stack(postInputStr, postInputStr.length());
                    //cout <<"evaluates to: "<<evaluate(newStack);
                    myStack.evaluate_postfix(postInputStr);
                    cout<<"\n"<<postInputStr;
                    cout<<" evaluates to "<<myStack<<"\n";
                }
            }
        }
        else if(input=='e'){
            if(testingOFF) cin>>input;
            else input = 'e';
            
            cout<<"Enter postfix expression: ";
            if(testingOFF)  cin>>postInputStr;
            else postInputStr="20 30 40 + *";
        }
        else if(input=='q'){       
            break;
        };
            
    //cout<<"The value of the expression is: "<<evaluate(postInputStr)<<endl;
    
    }
}
