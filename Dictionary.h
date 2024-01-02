//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA8
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>

#ifndef DICTIONARY_H_INCLUDE_
#define DICTIONARY_H_INCLUDE_


#define BLACK -1
#define RED 1


// Exported types -------------------------------------------------------------
typedef std::string keyType;  // must be comparable using <, <=, >, >=, ==, !=
typedef int         valType;

class Dictionary{

private:

   // private Node struct
   struct Node{
      // Node fields
      keyType key;
      valType val;
      Node* parent;
      Node* left;
      Node* right;
      int color;
      // Node constructor
      Node(keyType k, valType v);
   };

   // Dictionary fields
   Node* nil;
   Node* root;
   Node* current;
   int   num_pairs;

   // Helper Functions (Optional) ---------------------------------------------

    Node* findKeyhelper(std::string k, Node* ptr) const {
        if (ptr != nil && ptr != nullptr){
            if (ptr->key == k)
                return ptr;
            else{
                if (ptr->key > k)
                    return findKeyhelper(k, ptr->left);
                else
                    return findKeyhelper(k, ptr->right);
            }
        }
        else{
            return nullptr;
        }
    }

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
    std::string inOrderString(Node* R) const{
        std::string s = "";
        if (R == nullptr) {
            return "";
        }

        if (R->left != nil) {
            s += inOrderString(R->left);
        }
        s = s + R->key + " : " + std::to_string(R->val) + "\n";
        if (R->right != nil) {
            s += inOrderString(R->right);
        }
        return s;
    }

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string will consist of keys only, with the order determined by a pre-order
   // tree walk. The keys stored in black Nodes will be appended as "key\n", and
   // the keys stored in red Nodes will be appended as "key (RED)\n". The output 
   // of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
    std::string preOrderString(Node* R) const{
        std::string s = "";
        if (R == nullptr) {
            return "";
        }
        if(R->color == BLACK){
            s += R->key + "\n";
        }else{
            s += R->key + " (RED)\n";
        }

        if (R->left != nil) {
            s += preOrderString(R->left);
        }
        if (R->right != nil) {
            s += preOrderString(R->right);
        }
        return s;
    }

   // BST_insert()
   // Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
    void BST_insert(Node* M){
        Node* Y = nullptr;
        Node* X = root;
        while(X != nullptr){
            Y = X;
            if(M->key < X->key){
                X = X->left;
            }else{
                X = X->right;
            }
        }
        M->parent = Y;
        if(Y == nullptr){
            root = M;
        }else if(M->key < Y->key){
            Y->left = M;
        }else{
            Y->right = M;
        }
        
    }

    Dictionary::Node* copyHelper(Node* R){
        if(R != nullptr && R->key != "NIL"){
            Node* new_root = new Node(R->key, R->val);
            if(R->left != nullptr && R->left->key != "NIL"){
                new_root->left = copyHelper(R->left);
                new_root->left->parent = new_root;
            }
            if(R->right != nullptr && R->right->key != "NIL"){
                new_root->right = copyHelper(R->right);
                new_root->right->parent = new_root;
            }
            return new_root;
        }else{
            return nullptr;
        }
    }

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
    void preOrderCopy(Node* R, Node* N){
        if(R != N &&R != nullptr){
            //BST_insert(R);
            setValue(R->key, R->val);
            preOrderCopy(R->left, N);
            preOrderCopy(R->right, N);
        }
        return;
    }

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R.
    void postOrderDelete(Node* R){
        if(R != nil && R != nullptr){
        //if(R != nil){
        //if(R != nullptr){
            postOrderDelete(R->left);
            postOrderDelete(R->right);
            delete R;
            num_pairs--;
            //remove(R->key);
        }
    }
   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
    Node* search(Node* R, keyType k) const{
        if (R == nil || k == R->key) {
            return R;
        } else if (k < R->key) {
            return search(R->left, k);
        } else {
            return search(R->right, k);
        }
    }

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
    Node* findMin(Node* R){
        if(R != nullptr && R != nil){
            Node* N = R;
            while(N->left != nullptr && N->left != nil){
                N = N->left;
            }
            return N;
        }else{
            return nullptr;
        }
    }

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
    Node* findMax(Node* R){
        if(R != nullptr && R != nil){
            Node* N = R;
            while(N->right != nullptr && N->right != nil){
                N = N->right;
            }
            return N;
        }else{
            return nullptr;
        }
    }

    Node* findLeftMostPrivate(Node* ptr){
        if(ptr == nullptr){
            return nullptr;
        }else{
            if(ptr->left != nullptr && ptr->left != nil){
                return findLeftMostPrivate(ptr->left);
            }else{
                return ptr;
            }
        }
    }

    Node* findRightMostPrivate(Node* ptr){
        if(ptr == nullptr){
            return nullptr;
        }else{
            if(ptr->right != nullptr && ptr->right != nil){
                return findRightMostPrivate(ptr->right);
            }else{
                return ptr;
            }
        }
    }


   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
    Node* findNext(Node* N){
        if(N == nil){
            return nil;
        }
        if(N->right != nil && N->right != nullptr){
            return findMin(N->right);
        }
        Node* M = N->parent;
        while(M != nil && N == M->right && M != nullptr){
            N = M;
            M = M->parent;
        }
        return M;
    }

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
    Node* findPrev(Node* N){
        if(N == nil){
            return nil;
        }
        if(N->left != nil && N->left != nullptr){
            return findMax(N->left);
        }
        Node* M = N->parent;
        while(M != nil && N == M->left && M != nullptr){
            N = M;
            M = M->parent;
        }
        return M;
    }

    // transplant()
    //helper function for remove()
    void transplant(Node* A, Node* B){
        if(A->parent == nil){
            this->root = B;
        }else if(A == A->parent->left){
            A->parent->left = B;
        }else{
            A->parent->right = B;
        }
        if(B != nil){
            B->parent = A->parent;
        }
    }

   // RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
    void LeftRotate(Node* N){
        //set y
        Node* Y = N->right;

        //turn y's left subtree into n's right subtree
        N->right = Y->left;
        if(Y->left != nil){
            Y->left->parent = N;
        }

        //link y's parent to n
        Y->parent = N->parent;
        if(N->parent == nil){
            root = Y;
        }else if(N == N->parent->left){
            N->parent->left = Y;
        }else{
            N->parent->right = Y;
        }

        //put n on y's left
        Y->left = N;
        N->parent = Y;

    }

   // RightRotate()
    void RightRotate(Node* N){
        //set y
        Node* Y = N->left;

        //turn Y's right subtree into N's left subtree
        N->left = Y->right;
        if(Y->right != nil){
            Y->right->parent = N;
        }

        //link y's parent to n
        Y->parent = N->parent;
        if(N->parent == nil){
            root = Y;
        }else if(N == N->parent->right){
            N->parent->right = Y;
        }else{
            N->parent->left = Y;
        }

        //put n on y's right
        Y->right = N;
        N->parent = Y;
    }

   // RB_InsertFixUP()
    void RB_InsertFixUp(Node* N){
        if (N != root) {
            while(N->parent != nullptr && N->parent->color == RED){
                if(N->parent == N->parent->parent->left){
                    Node* Y = N->parent->parent->right;
                    if(Y != NULL && Y->color == RED){
                        N->parent->color = BLACK;
                        Y->color = BLACK;
                        N->parent->parent->color = RED;
                        N = N->parent->parent;
                    }else{
                        if(N == N->parent->right){
                            N = N->parent;
                            LeftRotate(N);
                        }
                        N->parent->color = BLACK;
                        N->parent->parent->color = RED;
                        RightRotate(N->parent->parent);
                    }
                }else{
                    Node* Y = N->parent->parent->left;
                    if(Y != NULL && Y->color == RED){
                        N->parent->color = BLACK;
                        Y->color = BLACK;
                        N->parent->parent->color = RED;
                        N = N->parent->parent;
                    }else{
                        if(N == N->parent->left){
                            N = N->parent;
                            RightRotate(N);
                        }
                        N->parent->color = BLACK;
                        N->parent->parent->color = RED;
                        LeftRotate(N->parent->parent);
                    }
                }
            }
        }
        root->color = BLACK;
    }

   // RB_Transplant()
    void RB_Transplant(Node* u, Node* v){
        if(u->parent == nullptr){
            return;
        }
        if(u->parent == nil){
            root = v;
        }else if(u == u->parent->left){
            u->parent->left = v;
        }else{
            u->parent->right = v;
        }
        if(v != nullptr){
            v->parent = u->parent;
        }
    }

   // RB_DeleteFixUp()
    void RB_DeleteFixUp(Node* N){
        if(N != nullptr){
            while(N != root && N->color == BLACK){
                if(N == N->parent->left){
                    Node* W = N->parent->right;
                    if(W->color == RED){
                        W->color = BLACK;
                        N->parent->color = RED;
                        LeftRotate(N->parent);
                        W = N->parent->right;
                    }
                    if(W->left->color == BLACK && W->right->color == BLACK){
                        W->color = RED;
                        N = N->parent;
                    }else{
                        if(W->right->color == BLACK){
                            W->left->color = BLACK;
                            W->color = RED;
                            RightRotate(W);
                            W = N->parent->right;
                        }
                        W->color = N->parent->color;
                        N->parent->color = BLACK;
                        W->right->color = BLACK;
                        LeftRotate(N->parent);
                        N = root;
                    }
                }else{
                    Node* W = N->parent->left;
                    if(W->color == RED){
                        W->color = BLACK;
                        N->parent->color = RED;
                        RightRotate(N->parent);
                        W = N->parent->left;
                    }
                    if(W->right->color == BLACK && W->left->color == BLACK){
                        W->color = RED;
                        N = N->parent;
                    }else{
                        if(W->left->color == BLACK){
                            W->right->color = BLACK;
                            W->color = RED;
                            LeftRotate(W);
                            W = N->parent->left;
                        }
                        W->color = N->parent->color;
                        N->parent->color = BLACK;
                        W->left->color = BLACK;
                        RightRotate(N->parent);
                        N = root;
                    }
                }
            }
            N->color = BLACK;
        }
        
    }

   // RB_Delete()
    void RB_Delete(Node* N){
        Node* Y = N;
        Node* X = nullptr;
        int y_original_color = Y->color;
        if(N->left == nil){
            X = N->right;
            RB_Transplant(N, N->right);
        }else if(N->right == nil){
            X = N->left;
            RB_Transplant(N, N->left);
        }else if(N->right == nullptr){
            return;
        }else{
            Y = findMin(N->right);
            y_original_color = Y->color;
            X = Y->right;
            if(Y->parent == N){
                X->parent = Y;
            }else{
                RB_Transplant(Y, Y->right);
                Y->right = N->right;
                Y->right->parent = Y;
            }
            RB_Transplant(N, Y);
            Y->left = N->left;
            Y->left->parent = Y;
            Y->color = N->color;
        }
        if(y_original_color == BLACK){
            RB_DeleteFixUp(X);
        }
    }


public:

   // Class Constructors & Destructors ----------------------------------------
   
   // Creates new Dictionary in the empty state. 
   Dictionary();

   // Copy constructor.
   Dictionary(const Dictionary& D);

   // Destructor
   ~Dictionary();


   // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
   int size() const;

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool contains(keyType k) const;

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& getValue(keyType k) const;

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool hasCurrent() const;

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType currentKey() const;

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& currentVal() const;


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void clear();

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void setValue(keyType k, valType v);

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void remove(keyType k);

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void begin();

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void end();

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void next();

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void prev();


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string to_string() const;

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. The key order is 
   // given by a pre-order tree walk. The keys stored in black Nodes will appear in
   // the returned string as "key\n", and the keys stored in red Nodes will appear 
   // as "key (RED)\n".  The output of this function is demonstrated in 
   // /Examples/pa8/DictionaryClient-out.
   std::string pre_string() const;

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool equals(const Dictionary& D) const;


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   friend std::ostream& operator<<( std::ostream& stream, Dictionary& D );

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   friend bool operator==( const Dictionary& A, const Dictionary& B );

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& operator=( const Dictionary& D );

};


#endif
