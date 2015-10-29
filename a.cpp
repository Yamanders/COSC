/* 
AUTHOR: AMANDA MOLLING A17020308
COURSE: COSC 2326.001 FALL 2015 MW19 ; INSTRUCTOR: THAYER
LAB 3: PURPOSE: INDEPENDENTLY BUILD LIST, STACK, QUEUE.
*/

// New List function
#include <iostream>
using namespace std;

typedef char DataType;

class List {
    public:
	class Element {
 		public:
        DataType data;
 		Element *next = nullptr;;
			Element(){
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
		~List();
        void insert(DataType);
        //void insert_at_beginning(DataType data); //not needed for list... I just wrote it for good pointer practice because I needed more practice.
        //void insert_in_sorted_position(DataType); //Explicitely named. insert() does this function, because requirements of assignment.
        //void sort();
        void insert_at_bottom(DataType); //for putting things at end of list (like a queue)
        bool is_empty();
        const List & operator=(const List & rightHandSide);
        void remove(int position);
        void display(ostream & out ) const;
        void end_of_list();
};

void List::end_of_list(){
	Element* runner = head;
	Element* lastNext = runner;
	while(runner!=nullptr){
		lastNext=runner;
		runner=runner->next;
	}
	cout<<"End of list: "<<(lastNext->next)<<" !\n";
}











List::List(){
	head = nullptr;
}

List::List(DataType val){
	head = new Element(val);
}

List::~List(){
    Element *currPtr = head;
	Element *nextPtr;
    while(currPtr!=0){
        nextPtr=currPtr->next;
        delete currPtr;
        currPtr=nextPtr;
    }
}

/*
Stack::~Stack(){
    ElementPointer currPtr = myTop, nextPtr;
    while(currPtr!=0){
        nextPtr = currPtr->next;
        delete currPtr;
        currPtr = nextPtr;
    }
}
*/
ostream & operator<<(ostream & out, const List &alist){
    alist.display(out);
    return out;
};

void List::display(ostream & out) const{
    Element *runner = head;
    int count = 1;
    while(runner){
        out << runner->data<<" ";
        count++;
        runner=runner->next;
    }   
}

const List & List::operator=(const List & rightHandSide){
    while(head!=nullptr){
        remove(0);
    }
    Element *runner = rightHandSide.head;
    while(runner!=nullptr){
        insert(runner->data);
        runner=runner->next;
    }
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

void List::remove(int position){
    Element *runner = head;
    Element *prev_runner = head;
    int temp;
    for(int link_position = 0; link_position<position; link_position++){
        if(runner==nullptr){
            cout<<"List is empty or index does not exist.\n";
            return;
        }
        else{
            prev_runner = runner;
            runner=runner->next;
        }
        temp = link_position;
    }
    prev_runner->next=runner->next;
    delete runner;
};




/*void List::insert(DataType data){// insert at beginning of list
    Element *newElement = new Element(data);
    newElement->next = head;
    head=newElement;//
}
*/
void List::insert(DataType data){	//This puts sorted data in...
//void List::insert_in_sorted_position(DataType data){
    Element *newElement = new Element(data);
    Element *runner=head;
    Element *previous=runner;
    while(runner!=nullptr){ 
        if(  (runner->data) < data){  //if the next data is smaller than our newdata, keep going down the list
            if(runner->next!=nullptr){//we have more to check.
                previous = runner;  //record our current runner address.
                runner=runner->next;    //go to the next element.
            }
            else{//we are at the bottom and runner->next is nullptr.
                //cerr<<"insertingdata2 "<<data<<endl;
                runner->next=newElement; //we stick this element at the end.
                return;// we are done.
            }
        }
        else{ //runner value is greater than or equal to, so stick our newElement in front of it....
           newElement->next=runner;
            //if(previous==head) //we have to set head to the beginning.
            if(runner==head)
                {head = newElement;head->next=runner;}
            else//we have to tell the previous element where to point to.
                {previous->next=newElement;}
            return;
        };
    }
    if(head==nullptr){  //empty list. Just add. :)
        head = newElement;  //now we have one element.
    }
};

//If you want to insert data at end by default, here's 
//where you can do it. Just change the name or use the other
//call. I think it makes more sense to have a list
//that is in the order that you send something to the list,
//but I can see how the other interpretaion would be valid.


void List::insert_at_bottom(DataType data){
//void List::insert(DataType data){
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
        head = newElement;
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




//////////////////////////////////////////////////////////////////////////////////////////////////////
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
	void end_of_stack();
};




void Stack::end_of_stack(){
	Element* runner = myTop;
	Element* lastNext = runner;
	while(runner!=nullptr){
		lastNext=runner;
		runner=runner->next;
	}
	cout<<"End of list: "<<(lastNext->next)<<" !\n";
}


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
    //cerr<<"copyconstruct\n"<<myTop;
    if (origStack.myTop==nullptr){
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
    //display(cout);
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
// Warning: These "codes" for operators could get "mixed up" with operands, so be careful!



void evaluate(Stack &stack) {
  // pop 3 items from stack, expected in postfix order
  // evaluate the expression, push the result. Example: 1+2 (infix) is 12+ (postfix)
  // push operation=+, push A=1, push B=2   call evaluate()
  // pop B=2, pop A=1, pop operation=add; result=1+2=3, push result
  StackElementType A, B, operation, result;
  if (stack.is_empty()) return; // stop right here!
  if (stack.pop(B) and stack.pop(A) and stack.pop(operation)) { // expect 3 items on stack
    /*switch (operation) {
      add:       result=A+B; break;
      subtract:  result=A-B; break;
      multiply:  result=A*B; break;
      divide:    result=A/B; break;
      default:   result=0;   break; // invalid operation
    */
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
void Stack::display(ostream & out) const{
    Element *runner = myTop;

    int count = 1;
    while(runner){
        //cerr<<"@@@@@";
        //out << "Stack Element " << count<<" "<<
        out <<runner->data<<" ";
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



int main(){  // main is done for you. You should not have to modify main.
  cout<<"COSC 2436 Lab 3\n";

  // If desired, you may add extra cout statements to better format the output.
  // While developing class List and Stack, COMMENT OUT any test code you are not ready for!

  // Test class List...
  cout<<"Testing class List\n";
  List listA, listB;
  listA.insert('C'); listA.insert('O'); listA.insert('S'); listA.insert('C');
  listA.insert('2'); listA.insert('4'); listA.insert('3'); listA.insert('6');
  cout<<"listA: " << listA <<endl; // sorted list is expected
  listB=listA; // make a complete copy
  cout<<"listB: " << listB <<endl; // should be same as listA

  List listC=listB; // construct a new list, initialize with previous list
  listC.insert('_'); listC.insert('Z'); listC.insert('Y'); listC.insert('X');
  cout<<"listC: " << listC <<endl;

  for (int position=1; position<4; ++position) {
    listC.remove(position);
    cout<<"listC: " << listC <<endl;
  }
	listA.end_of_list();
	listB.end_of_list();
	listC.end_of_list();
	
  // Test class stack...
  cout<<"\nTesting class Stack\n";
  Stack stackA, stackB;
  stackA.push('C'); stackA.push('O'); stackA.push('S'); stackA.push('C');
  stackA.push('2'); stackA.push('4'); stackA.push('3'); stackA.push('6');
  cout<<"stackA: " << stackA <<endl;
  stackB=stackA; // make a complete copy
  cout<<"stackB: " << stackB <<endl;
	stackA.end_of_stack();
	stackB.end_of_stack();
	//stackC.end_of_stack();
	
  Stack stackC=stackB; // construct a new stack, initialize with previous stack
  stackC.push('_'); stackC.push('Z'); stackC.push('Y'); stackC.push('X');
  cout<<"stackC: " << stackC <<endl;

  cout<<"Popping all of stackB: ";
  while (!stackB.is_empty()) { // test pop()
    cout<<stackB.pop()<<"  ";
  }
  cout<<endl;

  cout<<"Popping all of stackC: ";
  StackElementType item;
  while (stackC.pop(item)) { // test bool pop(StackElementType &)
    cout<<item<<"  ";
  }
  cout<<endl;

  Stack stackD=stackC; // expect stackC, stackD to be empty
  stackD.push(add); stackD.push(1); stackD.push(10); // 1+10
  cout<<"stackD: "<< stackD; evaluate(stackD);
  cout<<" evaluates to: " << stackD.pop() << endl; // expect 11

  stackD.push(subtract); stackD.push(44); stackD.push(22); // 44-22
  cout<<"stackD: "<< stackD; evaluate(stackD);
  cout<<" evaluates to: " << stackD.pop() << endl; // expect 22

  stackD.push(multiply); stackD.push(11); stackD.push(3); // 11*3
  cout<<"stackD: "<< stackD; evaluate(stackD);
  cout<<" evaluates to: " << stackD.pop() << endl; // expect 33

  stackD.push(divide); stackD.push(440); stackD.push(10); // 440/10
  cout<<"stackD: "<< stackD; evaluate(stackD);
  cout<<" evaluates to: " << stackD.pop() << endl; // expect 44
//	cout<<"End of A:"<<

  cout<<"\nGoodbye!\n";
}

/* Partial sample output from a previous solution, your output will look similar.
Testing class List
listA: 2 3 4 6 C C O S
listB: 2 3 4 6 C C O S
listC: 2 3 4 6 C C O S X Y Z _
listC: 2 4 6 C C O S X Y Z _
listC: 2 4 C C O S X Y Z _
listC: 2 4 C O S X Y Z _

Testing class Stack
stackA: <top> 54 51 52 50 67 83 79 67 <bottom>
stackB: <top> 54 51 52 50 67 83 79 67 <bottom>
stackC: <top> 88 89 90 95 54 51 52 50 67 83 79 67 <bottom>
Popping all of stackB: 54  51  52  50  67  83  79  67
Popping all of stackC: 88  89  90  95  54  51  52  50  67  83  79  67
stackD: <top> 10 1 0 <bottom> evaluates to: 11
stackD: <top> 22 44 1 <bottom> evaluates to: 22
stackD: <top> 3 11 2 <bottom> evaluates to: 33
stackD: <top> 10 440 3 <bottom> evaluates to: 44
*/

/* paste your testing results here...

*/

