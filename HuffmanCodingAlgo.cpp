#include <bits/stdc++.h>
using namespace std;

long long totalTableSize=0;
long long messageSize=0;
map<char,string> huffmanTable;

struct Node{
    char data;
    long long frequency;
    Node* left;         // each node will be containing a character, its frequency and pointers to its left and right child
    Node* right;
    Node(char data,long long frequency){       // Constructor for initializing a new Node
        this->data=data;
        this->frequency=frequency;
        left=nullptr;               // intially the nodes will not be having any child
        right=nullptr;
    }
};

//Print Huffman Codes
void printHuffmanCodes(Node* root,string str,vector<char> &arr,vector<int> &freq){
    if(!root) return;
    if(root->data!='#'){   // all the nodes apart from the intial leaf nodes will be '#'
        huffmanTable[root->data]=str;               // each character storing its corresponding Huffman code 
        totalTableSize+= str.size();
        // calculating the contribution of each character to the total encoded message size
        long long freqCurrChar = root->frequency;
        messageSize+= (str.size() * 1ll * freqCurrChar);
        return;
    }
    printHuffmanCodes(root->left,str+"0",arr,freq);   // on going left '0' will be added to the string (Huffman Coding)
    printHuffmanCodes(root->right,str+"1",arr,freq);    // on going right '1' will be added to the string (Huffman Coding)
}

class cmp{           // Comparator function is used because sorting is done on the basis of the 2nd element of Node
    public:
    bool operator()(Node *a,Node *b){
        return a->frequency>b->frequency;        // node having lesser frequency will be higher on the priority queue (minHeap)
    }   
};

// Making the Huffman Tree
void huffmanCodes(vector<char> &arr, vector<int> &freq, int n){
    // priority queue is used for getting the smallest node (wrt frequency) in O(logN) time
    priority_queue<Node*,vector<Node*>,cmp> minHeap;

    for(int i=0;i<n;i++){
        Node* node = new Node(arr[i],freq[i]);
        minHeap.push(node);
    }

    while(minHeap.size()>1){
        Node* leftChild=minHeap.top();
        minHeap.pop();
        Node* rightChild=minHeap.top();
        minHeap.pop();
        // creating a new temporary node which will become the parent for these left and right Child nodes
        Node* temp= new Node('#',leftChild->frequency+rightChild->frequency);
        temp->left=leftChild;
        temp->right=rightChild;       // merging the 2 smallest leaf nodes
        minHeap.push(temp);
    }

    string str="";          // this will store the Huffman Codes for each character
    Node* root=minHeap.top();
    printHuffmanCodes(root,str,arr,freq);
}

int main(){
    long long n=26;      // for storing each character
    totalTableSize=26*8;        // Gets ASCII codes where each character occupies 8 bits (ex. a=65 = 01000001)
    vector<char> arr(26);
    for(int i=0;i<26;i++){
        arr[i]=(char)('a'+i);
    }
    long long mini=20;
    long long maxi=80;
    long long initialTotalSize=0;

    random_device rd;         // used for generating random numbers by creating an object named 'rd'
    mt19937 gen(rd());        // uses the Mersenne Twister random number generator for high performance
    vector<int> freq(26,0);
    for(int i=0;i<26;i++){
        uniform_int_distribution<> distrib(mini, maxi);   // defines a uniform distribution in range [mini,maxi]
        long long x=distrib(gen);        // makes frequency of each character randomly within the range [20,80] using distribution object
        freq[i]=x;
        initialTotalSize+=(8*x);     // initial size will be the frequency of each character multiplied by 8
    }

    // for(auto &it:arr) cout<<it<<" "; 
    // cout<<endl;
    // for(auto &it:freq) cout<<it<<" ";
    // cout<<endl;

    // During testing the input generated were
    // a b c d e f g h i j k l m n o p q r s t u v w x y z 
    // 54 64 41 75 20 56 73 51 78 79 30 60 39 52 62 68 35 24 55 40 40 55 34 21 30 76

    huffmanCodes(arr,freq,n);

    long long totalFinalSize = totalTableSize+messageSize;
    long long diffInSize = initialTotalSize-totalFinalSize;
    double compressedPercentage = ((double)1* diffInSize) / initialTotalSize;
    cout<<compressedPercentage*100<<endl;
    // for(auto &val:huffmanTable){
    //     cout<<val.first<<" : "<<val.second<<endl;
    // }

    // Compression Percentage came out to be 38.89% and Huffman Table looked like
    //  a : 11010
    //  b : 0001
    //  c : 10111
    //  d : 0110
    //  e : 101100
    //  f : 11110
    //  g : 0100
    //  h : 11000
    //  i : 1000
    //  j : 1001
    //  k : 00100
    //  l : 11111
    //  m : 01011
    //  n : 11001
    //  o : 0000
    //  p : 0011
    //  q : 01010
    //  r : 110110
    //  s : 11101
    //  t : 10100
    //  u : 10101
    //  v : 11100
    //  w : 00101
    //  x : 101101
    //  y : 110111
    //  z : 0111
}