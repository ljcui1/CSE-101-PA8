//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA8
//
//-----------------------------------------------------------------------------

    #include<iostream>
    #include<string>
    #include<stdlib.h>

    #include "Dictionary.h"

    Dictionary::Node::Node(keyType k, valType v){
        key = k;
        val = v;
        color = RED;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }


    // Class Constructors & Destructors ----------------------------------------
    
    // Creates new Dictionary in the empty state. 
    Dictionary::Dictionary(){
        nil = new Node("NIL", -1);
        //nil = nullptr;
        nil->parent = nullptr;
        nil->left = nil;
        nil->right = nil;
        nil->color = BLACK;
        root = nullptr;
        current = nullptr;
        num_pairs = 0;
    }

    // Copy constructor.
    Dictionary::Dictionary(const Dictionary& D){
        nil = new Node("NIL", -1);
        //nil = nullptr;
        nil->parent = nullptr;
        nil->left = nil;
        nil->right = nil;
        nil->color = BLACK;
        root = nullptr;
        num_pairs = 0;
        current = nullptr;

        if(D.root != NULL){
            root = copyHelper(D.root);
            num_pairs = D.num_pairs;
        }

        //preOrderCopy(D.root, D.nil);
    }

    // Destructor
    Dictionary::~Dictionary(){
        clear();
        delete nil;
        nil = nullptr;
        current = nullptr;
        root = nullptr;
    }


    // Access functions --------------------------------------------------------

    // size()
    // Returns the size of this Dictionary.
    int Dictionary::size() const{
        return num_pairs;
    }


    // contains()
    // Returns true if there exists a pair such that key==k, and returns false
    // otherwise.
    bool Dictionary::contains(keyType k) const{
        Node* N = findKeyhelper(k, root);
        if (N != nil && N != nullptr){
            return true;
        }else{
            return false;
        }
    }

    // getValue()
    // Returns a reference to the value corresponding to key k.
    // Pre: contains(k)
    valType& Dictionary::getValue(keyType k) const{
        if(contains(k) == false){
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
        }
        Node* A = search(this->root, k);
        return A->val;
    }

    // hasCurrent()
    // Returns true if the current iterator is defined, and returns false 
    // otherwise.
    bool Dictionary::hasCurrent() const{
        if(current == nil || current == nullptr){
            return false;
        }else{
            return true;
        }
    }

    // currentKey()
    // Returns the current key.
    // Pre: hasCurrent() 
    keyType Dictionary::currentKey() const{
        if(hasCurrent() == false ){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
        }
        return current->key;
    }

    // currentVal()
    // Returns a reference to the current value.
    // Pre: hasCurrent()
    valType& Dictionary::currentVal() const{
        if(hasCurrent() == false ){
        throw std::logic_error("Dictionary: currentVal(): current undefined");
        }
        return current->val;
    }


    // Manipulation procedures -------------------------------------------------

    // clear()
    // Resets this Dictionary to the empty state, containing no pairs.
    void Dictionary::clear(){
        postOrderDelete(root);
        root = nullptr;
        current = nullptr;
    }

    // setValue()
    // If a pair with key==k exists, overwrites the corresponding value with v, 
    // otherwise inserts the new pair (k, v).
    void Dictionary::setValue(keyType k, valType v){
        Node* Y = nil;
        Node* X = root;
        while(X != nullptr && X != nil){
            Y = X;
            if(k == X->key){
                X->val = v;
                return;
            }else if(k < X->key){
                X = X->left;
            }else{
                X = X->right;
            }
        }
        Node* Z = new Node(k, v);
        Z->parent = Y;
        if(Y == nil){
            root = Z;
        }else if(Z->key < Y->key){
            Y->left = Z;
        }else{
            Y->right = Z;
        }
        Z->left = nil;
        Z->right = nil;
        Z->color = RED;
        RB_InsertFixUp(Z);
        num_pairs++;
        
    }

    // remove()
    // Deletes the pair for which key==k. If that pair is current, then current
    // becomes undefined.
    // Pre: contains(k).
    void Dictionary::remove(keyType k){
        Node* Z = search(root, k);
        if(Z == nil || Z == nullptr){
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
        }
        
        RB_Delete(Z);

        if(Z == current){
            current = nil;
        }
        if(Z->parent != nullptr){
            if(Z->parent != nil && Z->parent->right == Z){
                Z->parent->right = nil;
            }else if(Z->parent != nil && Z->parent->left == Z){
                Z->parent->left = nil;
            }
        }
        
        delete Z;
        num_pairs--;
    }

    // begin()
    // If non-empty, places current iterator at the first (key, value) pair
    // (as defined by the order operator < on keys), otherwise does nothing. 
    void Dictionary::begin(){
        if(num_pairs > 0){
            current = findLeftMostPrivate(root);
        }
    }

    // end()
    // If non-empty, places current iterator at the last (key, value) pair
    // (as defined by the order operator < on keys), otherwise does nothing. 
    void Dictionary::end(){
        if(num_pairs > 0){
            current = findRightMostPrivate(root);
        }
    }

    // next()
    // If the current iterator is not at the last pair, advances current 
    // to the next pair (as defined by the order operator < on keys). If 
    // the current iterator is at the last pair, makes current undefined.
    // Pre: hasCurrent()
    void Dictionary::next(){
        if(hasCurrent() == false ){
        throw std::logic_error("Dictionary: next(): current undefined");
        }
        current = findNext(current);
    }

    // prev()
    // If the current iterator is not at the first pair, moves current to  
    // the previous pair (as defined by the order operator < on keys). If 
    // the current iterator is at the first pair, makes current undefined.
    // Pre: hasCurrent()
    void Dictionary::prev(){
        if(hasCurrent() == false ){
        throw std::logic_error("Dictionary: prev(): current undefined");
        }
        current = findPrev(current);
    }


    // Other Functions ---------------------------------------------------------

    // to_string()
    // Returns a string representation of this Dictionary. Consecutive (key, value)
    // pairs are separated by a newline "\n" character, and the items key and value 
    // are separated by the sequence space-colon-space " : ". The pairs are arranged 
    // in order, as defined by the order operator <.
    std::string Dictionary::to_string() const{
        //Dictionary D = *this;
        return inOrderString(root);
    }

    // pre_string()
    // Returns a string consisting of all keys in this Dictionary. Consecutive
    // keys are separated by newline "\n" characters. The key order is given
    // by a pre-order tree walk.
    std::string Dictionary::pre_string() const{
        //Dictionary D = *this;
        return preOrderString(root);
    }

    // equals()
    // Returns true if and only if this Dictionary contains the same (key, value)
    // pairs as Dictionary D.
    bool Dictionary::equals(const Dictionary& D) const{
        return to_string() == D.to_string();
    }


    // Overloaded Operators ----------------------------------------------------
    
    // operator<<()
    // Inserts string representation of Dictionary D into stream, as defined by
    // member function to_string().
    std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
        return stream << D.to_string();
    }

    // operator==()
    // Returns true if and only if Dictionary A equals Dictionary B, as defined
    // by member function equals(). 
    bool operator==( const Dictionary& A, const Dictionary& B ){
        return A.equals(B);
    }

    // operator=()
    // Overwrites the state of this Dictionary with state of D, and returns a
    // reference to this Dictionary.
    Dictionary& Dictionary::operator=( const Dictionary& D ){
        if(this != &D){
            Dictionary temp = D;
            std::swap(nil, temp.nil);
            std::swap(root, temp.root);
            std::swap(current, temp.current);
            std::swap(num_pairs, temp.num_pairs);
        }

        return *this;
    }


