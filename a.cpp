

// New List function
#include <iostream>
using namespace std;

typedef int DataType;

class List {
    public:
	class Element {
 		public:
        DataType data;
 		Element *next;

			Element(){
				next = nullptr;
			}
			Element(DataType newData, Element* newNext){
				data = newData;
				next = newNext;
			}
			Element(DataType newData){
				data = newData;
				next=nullptr;
			}
	};
	Element *head;
	public:
		List();
		List(DataType val);
		List(const List & origList); //copy constructor (that is,  construct a new list identical to a another list.)
	//	~List();
        void insert(DataType);
        void insert_at_end(DataType data);
        void display(ostream & out ) const;
        bool is_empty();
        const List & operator=(const List & rightHandSide);
};

ostream & operator<<(ostream & out, const List &alist){
    alist.display(out);
    return out;
};

void List::display(ostream & out) const{
    Element *runner = head;
    int count = 1;
    while(runner){
        out << "\nElement " << count<<" "<<runner->data;
        count++;
        runner=runner->next;
    }   
}



const List & List::operator=(const List & rightHandSide){
    //cerr<<"Entering overloaded assignment \n";
    //List newList;
    while(head!=nullptr){
        //remove();
    }

    //newList.head = rightHandSide.head;
    //Element *runner;
    Element *runner = rightHandSide.head;
    while(runner!=nullptr){
        //Element *tempNode = new Element;
        //cerr<<"transferring runner data " << runner->data <<"\n";
        insert_at_end(runner->data);
        runner=runner->next;
    }
    //head=runner?? Check this later...
    return *this;
}
List::List(const List & origList){
    head = origList.head;
    Element *runner = head;
    while(runner->next!=nullptr){
        if(runner==origList.head);
        if(runner->next == nullptr){
        }
        else runner=runner->next;
    };
}
List::List(){
	head = nullptr;
}

List::List(DataType val){
	head = new Element(val);
}
/*List::~List(){
    Element *runner = head;
    cerr<<"deconstruct ";
    while(runner !=0){
       // Element *runner = runner->;
        Element *next = runner->next;
        //head = runner->next;
        delete runner;
        runner = next;
    }
}
*/
void List::insert(DataType data){//at beginning
    Element *newElement = new Element(data);
    newElement->next = head;
    head=newElement;//here's my problem...
}
void List::insert_at_end(DataType data){
    Element *newElement = new Element(data);
    Element *runner = head;
    Element *previous=runner;
    if (head != nullptr){
        while(runner->next!=nullptr){
            previous = runner;
            runner=runner->next;
        }
        runner->next = newElement;
    }
    else{
        runner = newElement;
        head = runner;
    }
};



bool List::is_empty(){
    bool is_empty;
    Element *runner = head;
    if(runner==nullptr)
        is_empty = true;
    else
        is_empty=false;

    return is_empty;
    }

typedef int StackDataType;

class Stack {
  private:
    int size=0;              // current size of stack (optional, for fast access)
    class Element{
        public:
            StackDataType data;
            Element * next = nullptr;
            Element(StackDataType data){
                this->data=data;
                this->next=nullptr;
            };
    };
  public:
    typedef Element *ElementPointer;
    ElementPointer myTop;   // pointer to dynamic array
    Stack();  // constructor
    Stack(StackDataType value);
    //~Stack(); // destructor
    Stack(const Stack & origStack); // copy constructor
    const Stack & operator=(const Stack & rightHandSide); // assignment operator
    bool is_empty() const; // is it empty? true if empty; false if not empty
    void push(StackDataType item); // assume this always works (could fail if computer out of memory)
    // Two kinds of pop (overloaded), implement both if you have time
    StackDataType pop(); // return (and remove) top element on stack; if stack is empty, return 0 (Risky, but convenient!)
    bool pop(StackDataType &item); // if empty return false; else copy top element on stack into item, remove top element, return true
    //void pop();
    void display(ostream & out) const; // display entire contents of list on one line, separate by spaces
};


ostream & operator<<(ostream & out, const Stack & aStack){
    aStack.display(out); 
    return out;
}; // this can call display() (Avoid duplicate code)
Stack::Stack(){
    myTop=nullptr;
};
Stack::Stack(StackDataType value){ 
    myTop = new Element(value) ;
};

Stack::Stack(const Stack & origStack){ // copy constructor.
    //cerr<<"copyconstruct\n"<<myTop;
    myTop = origStack.myTop;
    Element *runner = myTop;
    while(runner->next!=nullptr){
        if(runner==origStack.myTop);
        if(runner->next == nullptr){
        }
        else runner=runner->next;
    };
}


void Stack::push(StackDataType item){
    ElementPointer newElement = new Element(item);
    newElement->next = myTop;
    myTop=newElement;
};

StackDataType Stack::pop(){
    StackDataType topData=myTop->data;
    Element *runner = myTop;
    myTop = myTop->next;
    delete runner;
    return topData;
  };

bool Stack::pop(StackDataType &item){
    bool popped = false;
    cerr<<"pop start\n";
    if( is_empty() ) {
        cerr<<"is_empty; exit pop";
        popped=false;
    }
    else{
        cerr<"is not empty; pop and store";
        Element *runner = myTop;
        item=myTop->data;
        if(myTop->next!=nullptr){
            myTop = myTop->next;
            delete runner;
            popped=true;
        }
    }
}
 // if empty return false; else copy top element on stack into item, remove top element, return true




const Stack & Stack::operator=(const Stack & rightHandSide){
    while(myTop!=nullptr){  //Deallocate all of the data BEFORE we 
        //cerr<<"myTopp: "<<myTop->data<<" !=null, so pop\n";
        pop();
    };
    
    Element *runner = rightHandSide.myTop;  
    while(runner!=nullptr){
        push(runner->data);
        runner=runner->next;
    }
    return *this;
}

enum operation_t {add, subtract, multiply, divide}; // create "codes" for operators
// Warning: These "codes" for operators could get "mixed up" with operands, so be careful!

/*Stack operator+(const Stack stackA, cost Stack stackB){
       
}
*/

void evaluate(Stack &stack) {
  // pop 3 items from stack, expected in postfix order
  // evaluate the expression, push the result. Example: 1+2 (infix) is 12+ (postfix)
  // push operation=+, push A=1, push B=2   call evaluate()
  // pop B=2, pop A=1, pop operation=add; result=1+2=3, push result
  StackDataType A, B, operation, result;
  if (stack.is_empty()) return; // stop right here!
  if (stack.pop(B) and stack.pop(A) and stack.pop(operation)) { // expect 3 items on stack
    switch (operation) {
      add:       result=A+B; break;
      subtract:  result=A-B; break;
      multiply:  result=A*B; break;
      divide:    result=A/B; break;
      default:   result=0;   break; // invalid operation
    }
    stack.push(result);
  }
}



void Stack::display(ostream & out) const{
    Element *runner = myTop;
    int count = 1;
    while(runner){
        out << "Stack Element " << count<<" "<<runner->data<<" ";
        count++;
        if(runner->next == nullptr) break;
        else{
            runner=runner->next;
        }
    }
}


bool Stack::is_empty() const{
    bool is_empty;
    Element *runner = myTop;
    if(runner==nullptr)
        is_empty = true;
    else
        is_empty=false;

    return is_empty;
}

int main(){
    /*
	//cerr<<"yup\n";
	List listA, listB;
    //listA.insert('C'); listA.insert('O'); listA.insert('S'); listA.insert('C');
    //listA.display();
    //cout << "List empty? " << listA.is_empty() <<"\n";
    //listA.insert_at_end(10); listA.insert_at_end(20); listA.insert_at_end(30);
    listA.insert(10); listA.insert(20); listA.insert_at_end(5);
    cout <<"\nlistA display ";(listA.display(cout));
    listB=listA;
    cout<<"\nlistB display";listB.display(cout);
    List listC=List(listA);
    //cout<<"\n\nlistC display "; (listC.display());
    //~listA(listA);
   // ~listB(); ~listC();
    cout<<"\nListC "<<listC<<endl<<endl<<endl<<endl;
    */
    Stack stackA;
    Stack stackB;
    stackA.push('C'); stackA.push('O'); stackA.push('S'); stackA.push('C');
    cout<<"stackA "; stackA.display(cout);
    cout<<"\n";
    stackB.push('C'); stackB.push('B'); stackB.push('F'); stackB.push('G');
    stackB.display(cout);
    stackB=stackA; // make a complete copy
    cout<<"Copied stackB from stackA: " << stackB <<endl;
    Stack stackC=stackB; 
    cout<<"Stackc "<<stackC<<"\n";
    // construct a new stack, initialize with previous stack
 stackC.push('_'); stackC.push('Z'); stackC.push('Y'); stackC.push('X');
  cout<<"stackC after pushing: " << stackC <<endl;
 
  cout<<"Popping all of stackB: ";
  while (!stackB.is_empty()) { // test pop()
    stackB.pop();
    cout<<"stackB after pop \n "<<stackB<<"\n ";
  }
  cout<<endl;
  
  cout<<"Popping all of stackC: ";
  StackDataType item;
  for (int i = 0; i<10; i++){
  	(stackC.pop(item));  // test bool pop(StackElementType &)
	  
    //cout<<item<<"  ";
  };
  cout<<endl;
  
  Stack stackD=stackC; // expect stackC, stackD to be empty
  stackD.push(add); stackD.push(1); stackD.push(10); evaluate(stackD); // 1+10
  cout<<"stackD: "<< stackD << " evaluates to: " << stackD.pop() << endl; // expect 11
  
  stackD.push(subtract); stackD.push(44); stackD.push(22); evaluate(stackD); // 44-22
  cout<<"stackD: "<< stackD << " evaluates to: " << stackD.pop() << endl; // expect 22
  
  stackD.push(multiply); stackD.push(11); stackD.push(3); evaluate(stackD); // 11*3
  cout<<"stackD: "<< stackD << " evaluates to: " << stackD.pop() << endl; // expect 33
  
  stackD.push(divide); stackD.push(440); stackD.push(10); evaluate(stackD); // 440/10
  cout<<"stackD: "<< stackD << " evaluates to: " << stackD.pop() << endl; // expect 44
/* */
};





