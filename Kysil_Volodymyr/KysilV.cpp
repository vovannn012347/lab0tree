#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

template <class T>
struct node{
    node<T> *parent, *left, *right;
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

    tree(){ root = 0; }

    int insert_element(T elem);
    node<T>* delete_element(node<T> * elem);
    node<T>* search(T elem);
    void inOrder(node<T> * elem = 0);

    node<T>* next(node<T> * elem);
    node<T>* prev(node<T> * elem);
    node<T>* getRoot(){ return root;}
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

template<class T>
node<T> * tree<T>::delete_element(node<T> * elem){

    node<T> * left = elem->left, right = elem->right, parent = elem->parent;

    if( 0 == right ){//swapping if right is null
        right = left; //if left is not null then right is something
        left = 0;
    }

    if( 0 == parent ){//then elem is root
        root = right;
    }else{//not root
        if( parent -> right == elem ){//modifying parent
            parent -> right = right;
        }else parent -> left = right;
    }

    if( 0 != right ){//if any node exists
        right->parent = parent;

        if( 0 != left ){//if left exists
            for(;0 != right -> left; right = right -> left );//stepping in left side of right

            left -> parent = right;
            right -> left = left;
        }
    }

    return elem;
}

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
    //crappy code
    if ( ret->right == 0 ){
        if( ret->parent != 0 && ret->parent->data > ret->data ){
                return ret->parent;
        }else{
            for(;ret->parent != 0 && ret->parent->data < ret->data; ret = ret->parent);
            return ret->parent;
        }
    }else for ( ret = ret->right; ret->left != 0; ret = ret->left );

    return ret;
}

template<class T>
node<T>* tree<T>::prev(node<T> * elem){
    node<T>* ret = elem;
    //crappy code
    if ( ret->left == 0 ){
        if( ret->parent != 0 && ret->parent->data < ret->data){
            return ret->parent;
        }else{
            for(;ret->parent != 0 && ret->parent->data > ret->data; ret = ret->parent);
            return ret->parent;
        }
    }else for( ret = ret->left; ret->right != 0; ret = ret->right );

    return ret;
}

struct Student{

    char name[40], surname[40], card[17];
    int course, gender;
    int bithday, bithmonth, bithyear;

    void enterName( char * str1, char * str2 ){
        strcpy( name, str1 );
        strcpy( surname, str2);
    }

    void cardEnter( long long int a ){
        for( int i = 0; i < 16; i++ ){
            card[15-i] = a%10 + '0';
            a /= 10;
        }

        card[16] = '\0';
    }

    void cardEnter( char * a ){
        for( int i = 0; i < 16; i++ )card[i] = a[i];
        card[16] = '\0';
    }

    void enterData( int arg1, int arg2, char* bith ){

        course = arg1;
        gender = arg2;

        bithday = atoi(strtok(bith, ".,/ \0"));
        bithmonth = atoi(strtok(0, ".,/ \0"));
        bithyear = atoi(strtok(0, ".,/ \0"));
    }

    void print(){
        printf( "%s %s\n", name, surname );
        printf( "%s %d.%d.%d course %d\n", gender == 1 ? "male" : "female",bithday, bithmonth, bithyear, course );
        printf( "%s\n", card );
    }

    bool operator<(Student a){

        if( bithyear < a.bithyear )return 1;
        if( bithmonth < a.bithmonth )return 1;
        if( bithday <= a.bithday )return 1;

        return 0;
    }

    bool operator>(Student a){
        if( bithyear > a.bithyear )return 1;
        if( bithmonth > a.bithmonth )return 1;
        if( bithday >= a.bithday )return 1;

        return 0;
    }
};

void postOrder( node<Student> * root ){

    if( 0 != root ){
        postOrder( root -> left );
        postOrder( root -> right );
        root -> data.print();
    }

}
void inOrder( node<Student> * root ){

    if( 0 != root ){
        inOrder( root -> left );
        root -> data.print();
        inOrder( root -> right );
    }

}
void preOrder( node<Student> * root ){

    if( 0 != root ){
        root -> data.print();
        preOrder( root -> left );
        preOrder( root -> right );
    }

}

int main(){

    tree<Student> list;

    FILE *f = fopen("input.txt", "r");

    char name[40], surname[40], bith[40], card[40];
    int course, gender;
    int n;
    fscanf(f, "%d", &n);
    Student *a;

    for( int i = 0; i < n; i++ ){
        a = new Student();

        fscanf(f, " %s\n", &name);
        fscanf(f, " %s\n", &surname);
        fscanf(f, " %s\n", &card);
        fscanf(f, " %d %d\n", &course, &gender);
        fscanf(f, " %s\n", &bith);

        a -> enterName( name, surname );
        a -> cardEnter( card );
        a -> enterData( course, gender, bith );

        list.insert_element(*a);
        a = 0;
    }

    printf("Task 1:\npostorder:\n");
    postOrder( list.getRoot() );
    printf("\npreorder:\n");
    preOrder( list.getRoot() );
    printf("\ninorder:\n");
    inOrder( list.getRoot() );
    printf("\n");

    for( node<Student> *i = list.getRoot(); i->left =)


/*some other stuff
    vector<int> v;

    v.push_back(7);
    v.push_back(2);
    v.push_back(3);
    v.push_back(67);
    v.push_back(9);


    vector<int>::iterator i = v.begin()-1, i1, i2;

*/
    return 0;
}
