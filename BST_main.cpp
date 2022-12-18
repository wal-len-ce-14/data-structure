#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;



class BST{
    private:

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

        /********Root*********/
        Node* root;

    public:

        /********Function*********/
        BST(){root = NULL;}
        ~BST();
        Node *CreatedNode(int id, char gender, long long phone){Node N(id, gender, phone); return &N;}
        bool Load(char *Path, char mode);
        bool Insert(int id, char gender, long long phone);
        bool Search(char *Path, int id);
        bool showInLVR(char *Path, int id);
        bool showInVLR(char *Path, int id);

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
            if(cur-> LChild == NULL) cur-> LChild = CreatedNode(id, gender, phone);
            else cur = cur-> LChild;
        }else{
            if(cur-> RChild == NULL) cur-> RChild = CreatedNode(id, gender, phone);
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

int main(){
    BST bst;
    if(bst.Load("1first_input_data", 'I')){cout << "Failed to load file" << endl;}


    return 0;
}
