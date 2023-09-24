#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

struct Node {
  int data;
  class Node* left;
  class Node* right;
};

Node* createNode(int data){
  Node* temp = new Node;
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
};

Node* addNode(Node* node, int data){
  if (node == NULL){
    node = createNode(data);
    return node;
  }
  if (data < node->data){
    node->left = addNode(node->left, data);
  }else if( data > node->data) {
    node->right = addNode(node->right, data);
  }
  return node;
};

void printNodes(Node* node){
  if (node != NULL){
    printNodes(node->left);
    std::cout << node->data << std::endl;
    printNodes(node->right);
  }
}
int getData(Node* node){
  if(node != NULL){
    return node->data;
  }
  return -1;
}
void printInBetween(Node* node, int k1, int k2){
  if (node != NULL){
    if (k1 < node->data){
      printInBetween(node->left, k1, k2);
    }
    if(k1 < node->data && k2 > node->data){
      std::cout << node->data << std::endl;
    }
    if(k2 > node->data){
      printInBetween(node->right, k1, k2);
    }
  }
}
void printInBetweenAndLimits(Node* node, int k1, int k2){
  if (node != NULL){
    if (k1 <= node->data){
      printInBetweenAndLimits(node->left, k1, k2);
    }
    if(k1 <= node->data && k2 >= node->data){
      std::cout << node->data << std::endl;
    }
    if(k2 >= node->data){
      printInBetweenAndLimits(node->right, k1, k2);
    }
  }
}
int getNumber(std::string str){
  std::string number = "";
  char ch;
  for(int i=0; i<str.length(); i++){
    ch = str[i];
    if(ch >= '0' && ch <= '9'){
      number += ch;
    }else{
      continue;
    }
  }
  if(number==""){
    return -1;
  }
  int num;
  num = std::stoi(number);
  return num;
}

void numberFunction(Node* node, std::string string){
  int inputNum;
  std::stringstream ss(string);
  std::string token;
  
  while (ss >> token){
    inputNum = getNumber(token);
    addNode(node, inputNum);
  }
}
Node* startFile(void){
  std::ifstream inFile;
  std::string input;
  int inputNumber;
  Node* temp;
  
  inFile.open("input.txt");
  
  if (inFile.is_open()) {
    getline(inFile, input, ' ');
    inputNumber = getNumber(input);
    temp = addNode(temp, inputNumber);
    while (!inFile.eof()) {
      getline(inFile, input);
      numberFunction(temp, input);
    }
    inFile.close();
    return temp;
  }else {
    std::cout << "NO FILE HAS BEEN OPENED" << std::endl;
    return temp;
  }
}
void menu(Node* node){
  std::cout << "Give the first number(k1), second number(k2) " << std::endl;
  std::cout << "ex) 4, 130 -> 4 is the LOWER limit and 130 is the UPPER limit " << std::endl;
      
  std::string k1Andk2;
  std::getline(std::cin, k1Andk2);
  int grade;
  std::string token;
  int k1;
  int k2;
  std::stringstream ss(k1Andk2);
      
  ss >> token;
  k1=getNumber(token);
  
  ss >> token;
  k2=getNumber(token);
  
  std::cout<< "" << std::endl;
  std::cout<< "Inbetween print: " << std::endl;

  printInBetween(node, k1, k2);

  std::cout<< "" << std::endl;
  std::cout<< "Inbetween print including the limits: " << std::endl;
  printInBetweenAndLimits(node, k1, k2);
}

int main(){
  Node* root = NULL;

  root = startFile();

  /*
      I have included the print all nodes function to prove that all the nodes are there.
      If you wish to see all ove them, uncomment the printNodes(root) comment.

      Else just compile and execute.
  */

  //printNodes(root);
  menu(root);
  
  return 0;
}