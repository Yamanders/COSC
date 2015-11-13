// Name:
// Startup code for COSC2436 Lab 6 on binary trees; Instructor: Thayer

#include <iostream>
#define show_name_value(n) cout<<#n<<"="<<n<<" ";
using namespace std;
#define DEBUGTREE  0 // Set DEBUGTREE 0 or 1 for cout<<status inside class Tree
#define SHOWNODES  0 // Set SHOWNODES 0 or 1 for show_nodes()
#define SHOWTREE   1 // Set SHOWTREE  0 or 1 for show_tree()

typedef char Data;
class Tree {
    public:
        class Node {
            public: // make public so nodes can be created externally of Tree
                Data data=Data();
                Node * left=nullptr;
                Node * right=nullptr;
                Node(Data data) {
                    this->data=data;
                }
                void show_node() const {
                    cout<<" Node: data="<<data<<" left="<<left<<" right="<<right<<"; ";
                }
                void show_data(int depth=0) const {
                    cout<<string(depth*3, ' ')<<data;
                }
        };

        Node *root=nullptr;

        void insert(const Node node) { // prefer to grow tree by filling in each level before starting new level, keep tree flat and wide, "balanced", "fully populated"
            static bool insert_left=true;
                Node *pnewNode= new Node(node);
            if (root==nullptr) { // first node
                if (DEBUGTREE) cout<<"\nTree::insert(node) data="<<pnewNode->data<<" empty root="<<root;
                root=pnewNode;
                return;
            } 
            else {
                Node *pvacancy=root;
                while (pvacancy) {
                    if (pvacancy->left==nullptr) {
                        if (DEBUGTREE){
                            cout<<"\nTree::insert(node) data="<<pnewNode->data<<" found empty left= "<<pvacancy;
                        }
                        pvacancy->left=pnewNode; break; // found open spot on left
                    }
                    else if (pvacancy->right==nullptr) {
                        if (DEBUGTREE) {
                            cout<<"\nTree::insert(node) data="<<pnewNode->data<<" found empty right="<<pvacancy;
                        }
                        pvacancy->right=pnewNode; break; // found open spot on right
                    }
                    else {
                        // Alternate left, right insertion
                        // Here is a simple attempt to maintain a balanced tree. It doesn't quite work,
                        // but works better than always left or always right. A "robust" balanced insert
                        // would have to to perform a depth-first search, looking for the first available vacancy
                        if (insert_left) pvacancy=pvacancy->left;
                        else pvacancy=pvacancy->right;
                        insert_left=!insert_left; // alternate sides
                    }
                }
            }
        }

        void show_nodes() const {
            cout<<"\nTree::show_nodes ";
            if (!root) {
                cout<<"empty"; 
                return;
            }
            else {
                show_nodes_recursive(root);
            }
                cout<<endl;
        }

    void show_tree() const {
        cout<<"\nTree::show_tree ";
        if (!root) {
            cout<<"empty"; 
            return;}
        else {
            cout<<endl;
            show_tree_recursive(root, 0);
        }
    }

    private:
        void show_nodes_recursive(Node * runner) const {
            if (runner) {
                show_nodes_recursive(runner->left);
                runner->show_node();
                show_nodes_recursive(runner->right);
            }
        }

    void show_tree_recursive(Node * runner, int depth) const {
        if (runner) {
            show_tree_recursive(runner->left, depth+1);
            runner->show_data(depth); 
            cout<<endl;
            show_tree_recursive(runner->right, depth+1);
        }
    }

    int height(Node *runner, int depth){

    }
};

// This code makes it easier to control display of debug information for testing.
enum show_t {none_, nodes_, tree_, both_};
void display(show_t show, const Tree::Node &node) {
    if (show==nodes_ or show==both_) node.show_node();
}
void display(show_t show, const Tree &tree) {
    if (show==nodes_ or show==both_) {
        tree.show_nodes();
    }
    if (show==tree_  or show==both_) {
        tree.show_tree();
    }
}

int main() {
    cout<<"start...\n";
  
  // To control amount of feedback, use overloaded function display with indicator show
    show_t show=none_;
    
    if (SHOWNODES) {
        show=nodes_;
    }
    if (SHOWTREE) {
        show=tree_;
    }
    if (SHOWNODES and SHOWTREE) {
        show=both_;
    }

    // Since Tree::Node is public, instances of Node can be created separately and independently of Tree
    // This can be useful for moving entire Nodes between different trees, even into linked lists, etc.
    // Another design choice is to make the data within a Node a template parameter, as done in the Nyhoff textbook.
    Tree::Node n1('A'), n2('B'), n3('C'); // make some independent nodes, outside of tree
    display(show, n1);
    display(show, n2);
    display(show, n3);
    cout<<endl;
    
    Tree tree; // Start with empty tree
    display(show, tree); // starts out empty
    
    // insert nodes: A B C
    tree.insert(n1); display(show, tree);
    tree.insert(n2); display(show, tree);
    tree.insert(n3); display(show, tree);
    
    const int MAX_MORE_NODES = 6;
    char ch='D';
    // Now insert: D E F G H I. show tree after every insert...
    for (int node_count=0; node_count<MAX_MORE_NODES; ++node_count) {
        tree.insert(Tree::Node(ch++)); display(show, tree);
    }

    cout<<"\n...end\n";
}
/* Original startup code output: (Replace with your output, or paste your output below)
start...

Tree::show_tree empty
Tree::show_tree
A

Tree::show_tree
   B
A

Tree::show_tree
   B
A
   C

Tree::show_tree
      D
   B
A
   C

Tree::show_tree
      D
   B
A
      E
   C

Tree::show_tree
      D
   B
      F
A
      E
   C

Tree::show_tree
      D
   B
      F
A
      E
   C
      G

Tree::show_tree
      D
   B
         H
      F
A
      E
   C
      G

Tree::show_tree
      D
   B
         H
      F
         I
A
      E
   C
      G

...end
*/

/* Paste your test output here...

*/
