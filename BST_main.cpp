#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

struct Node;
void Clear_File(char* Path);
int Level(Node* node, int level);

/*****Define Node******/
struct Node{
    int ID;   //Key
    char Gender;
    long long Phone;
    Node *LChild, *RChild;
    Node(int id, char gender, long long phone): ID(id), Gender(gender), Phone(phone){
        LChild = NULL;
        RChild = NULL;
    }
};

class BST{
    private:

        /********Root*********/
        Node* root;

    public:

        /********Function*********/
        BST(){root = NULL;}
        ~BST();
        Node *CreatedNode(int id, char gender, long long phone){Node N(id, gender, phone); return &N;}
        bool Load(char *Path, char mode);
        bool Insert(int id, char gender, long long phone);
        bool Search(char *Path, int id, Node* r = root);
        bool showInLVR(char *Path);
        bool showInVLR(char *Path);
        bool Tree_H(char *Path);

};

bool BST::Load(char* Path, char mode){
    int id; char gender; long long phone; Node *cur;
    queue<Node*> Q;
    fstream file;
    file.open(Path, ios::in | ios::out);
    if(!file) return false;
    switch(mode){
        case 'I':
            while(file >> id >> gender >> phone){
                Insert(id, gender, phone);
            }
            break;
        case 'O':
            Q.push(root);
            while(!Q.empty()){
                cur = Q.front();
                file << cur-> ID << ' '
                     << cur-> Gender << ' '
                     << cur-> Phone << endl;
                Q.pop();
                if(cur-> LChild != NULL) Q.push(cur-> LChild);
                if(cur-> RChild != NULL) Q.push(cur-> RChild);
            }
            break;
        default:
            return false;
    }
    return true;
}

bool BST::Insert(int id, char gender, long long phone){
    Node *cur = root;
    if(root == NULL) root = CreatedNode(id, gender, phone);
    while(cur-> ID != id){
        if(id < cur-> ID){
            if(cur-> LChild == NULL) {
                cur-> LChild = CreatedNode(id, gender, phone);
                break;
            }
            else cur = cur-> LChild;
        }else{
            if(cur-> RChild == NULL) {
                cur-> RChild = CreatedNode(id, gender, phone);
                break;
            }
            else cur = cur-> RChild;
        }
    }
    if(cur-> ID == id) return false;
    else return true;
}

BST::~BST(){
    Node *cur;
    queue<Node*> Q;
    Q.push(root);
    while(!Q.empty()){
        cur = Q.front();
        Q.pop();
        delete cur;
        if(cur-> LChild != NULL) Q.push(cur-> LChild);
        if(cur-> RChild != NULL) Q.push(cur-> RChild);
    }
}

bool BST::showInLVR(char *Path){
    Node *cur = root;
    stack<Node*> S;
    fstream file;
    file.open(Path, ios::app);
    if(!file) return false;
    file << "LVR sequence" << endl
         << "===========================" << endl;

    S.push(root);
    while(!S.empty()){
        /******traverse to most left******/
        while(S.top()-> LChild != NULL){
            S.push( S.top()-> LChild );
        }
        /******traverse back until node has right child******/
        while(!S.empty()){
            cur = S.top();
            file << cur-> ID << ' '
                 << cur-> Gender << ' '
                 << '0' << cur-> Phone << endl;
            S.pop();
            if(cur-> RChild != NULL){
                S.push(cur-> RChild);
                break;
            }
        }
    }
    file << "---------------------------" << endl << endl;
    file.close();
    return true;
}

bool BST::showInVLR(char *Path){
    Node *cur = root;
    stack<Node*> S;
    fstream file;
    file.open(Path, ios::app);
    if(!file) return false;
    file << "VLR sequence" << endl
         << "===========================" << endl;

    S.push(root);
    while(!S.empty()){
        /******traverse to most left and output every node******/
        while(S.top()-> LChild != NULL){
            cur = S.top();
            file << cur-> ID << ' '
                 << cur-> Gender << ' '
                 << '0' << cur-> Phone << endl;
            S.push( S.top()-> LChild );
        }
        /******traverse back until node has right child******/
        while(!S.empty()){
            S.pop();
            if(S.top()-> RChild != NULL){
                S.push(S.top()-> RChild);
                break;
            }
        }
    }
    file << "---------------------------" << endl << endl;
    file.close();
    return true;
}

bool BST::Search(char *Path, int id, Node *r){
    fstream file;
    file.open(Path, ios::app);
    if(!file) return false;
    if(root == NULL) return false;
    if(r-> ID == id){
        file << r-> ID << ' '
             << r-> Gender << ' '
             << '0' << r-> Phone << endl;
        return true;
    }else if(r-> LChild != NULL){
        if(Search(Path, id, r-> LChild)) return true;
    }else if(r-> RChild != NULL){
        if(Search(Path, id, r-> RChild)) return true;
    }else return false;
    file.close();
    return true;
}

bool BST::Tree_H(char *Path){
    fstream file;
    file.open(Path, ios::out);
    if(!file) return false;
    file << "Tree height: " << Level(root) << endl;
    file.close();
}

void Clear_File(char* Path){
    fstream file;
    file.open(Path, ios::trunc);
    file.close();
}

int Level(Node *node, int level = 0){
    if(node == NULL) return level;

    int LHeight, RHeight;
    LHeight = Level(node-> LChild, level+1);
    RHeight = Level(node-> LChild, level+1);
    if(LHeight > RHeight) return LHeight;
    else return RHeight;
}

int main(){
    /*********first time**********/
    BST bst;
    Clear_File("1first_traversal.txt");
    Clear_File("2second_traversal.txt");
    Clear_File("1first_search.txt");
    Clear_File("2second_search.txt");

    if(bst.Load("1first_input_data.txt", 'I')) cout << "Failed to load file" << endl;

    bst.showInLVR("1fist_traversal.txt");

    bst.Search("1first_search.txt", 100044);
    bst.Search("1first_search.txt", 657535);
    bst.Search("1first_search.txt", 100025);
    bst.Search("1first_search.txt", 100097);
    bst.Search("1first_search.txt", 031570);

    bst.Tree_H("1first_height");

    bst.Load("1first_output_data.txt", 'O');
    /*********second time**********/


    delete bst;

    return 0;
}
