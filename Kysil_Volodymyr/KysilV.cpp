using namespace std;

template <class T>
struct node{
    node<T> * parent, left, right;
    T data;

    node(T elem = 0, node<T> *a = 0){
        parent = a;
        left = 0;
        right = 0;
        data = elem;
        }
};

template<class T>
class tree{

    node<T> *root;

public:

    tree(){root = 0;}

    int insert_element(T elem);
    //int delete_element(node<T> * elem);
    node<T>* search(T elem);
    void inOrder(node<T> * elem = 0);

    node<T>* next(node<T> * elem);
    node<T>* prev(node<T> * elem);
};

template<class T>
int tree<T>::insert_element(T elem){

    if( root == 0 ){
        root = new node<T>(elem);
        return 0;
    }

    for( node<T>* curr = root; ; )
        if( curr->data < elem ){

            if( curr->right != 0 )curr = curr->right;
            else{
                curr->right = new node<T>(elem, curr);
                return 0;
            }

        }else
        if( curr->data > elem ){
            if( curr->left != 0 )curr = curr->left;
            else{
                curr->left = new node<T>(elem, curr);
                return 0;
            }
        }else return 1;

    return 1;
}
/*
template<class T>
int tree<T>::delete_element(node<T> * elem){

    node<T> * left = elem->left, right = elem->right;

    if( right != 0 ){
        node<T> * curr = right;
    for( ; curr->left!=0; curr = curr->left );

    curr->left = left;
    left->parent = curr->left;

    }else if( left != 0 ){

    right = left;

    }else{

    }


}
*/
template<class T>
node<T>* tree<T>::search(T elem){

       for( node<T>* curr = root; ; )
        if( curr->data < elem ){
            if( curr->right != 0 )curr = curr->right;
            else return 0;
        }else
        if( curr->data > elem ){
            if( curr->left != 0 )curr = curr->left;
            else return 0;
        }else return curr;

    return 0;
}

template<class T>
node<T>* tree<T>::next(node<T> * elem){
    node<T>* ret = elem;

    if ( elem->right == 0 ){
        if( elem->parent != 0 && elem->parent->left == elem ){ return elem->parent; }
        else return this;
    } else for ( ret = ret->right; ret->left != 0; ret = ret->left );

    return ret;
}

template<class T>
node<T>* tree<T>::prev(node<T> * elem){
    node<T>* ret = elem;

    if ( elem->left == 0 ){
        if( elem->parent != 0 && elem->parent->right == elem ){ return elem->parent; }
        else return this;
    } else for( ret = ret->left; ret->right != 0; ret = ret->right );

    return ret;
}


int main(){


    return 0;
}
