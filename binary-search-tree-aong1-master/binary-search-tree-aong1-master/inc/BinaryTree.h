#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <class Type>
struct Node {
    Type item;
    Node<Type> *left;
    Node<Type> *right;
};

template <class Type>
class BinaryTree
{
    public:
        BinaryTree();
		BinaryTree(const BinaryTree& other);
		BinaryTree& operator=(const BinaryTree& other);
        ~BinaryTree();
        void insert(Type item);
        void preOrder();
        void inOrder();
        void postOrder();
        int nodeCount();
        Node<Type>*find(Type item);
        Node<Type>*findRightMostNode(Node<Type> *find);
        void remove(Type item);
        int  height();
        int leavesCount();


    protected:
        Node<Type> *root;

    private:
        void destroy(Node<Type> * curr);
        void insert(Type item, Node<Type> * curr);
        void preOrder(Node<Type> *curr);
        void postOrder(Node<Type> *curr);
        void inOrder(Node<Type> * curr);
        int nodeCount(Node<Type> * curr);
        int leavesCount(Node<Type> * curr);
		void copyTree(Node<Type>* curr, Node<Type>* toCopy);
        Node<Type>*find(Type item, Node<Type> *curr);
        Node<Type>* remove(Type item, Node<Type>*curr);
        int height(Node<Type>*curr);
};

template <class Type>
BinaryTree<Type>::BinaryTree(){
	root = nullptr;
}

template <class Type>
BinaryTree<Type>::BinaryTree(const BinaryTree& other) {
	Node<Type>* tmp = other.root;
	root = new Node<Type>;
	root->item = other.root->item;		//set the root
	Node<Type>* curr = root;			//set a pointer to root
	int side = 0;

	copyTree(curr, tmp);				//pass a pointer to this root and the one to be copied to copyTree
	
}
template <class Type>
BinaryTree<Type>& BinaryTree<Type>::operator=(const BinaryTree& other) {

	destroy(root);

	Node<Type>* tmp = other.root;		//same as the copy constructor except you clear the tree before hand
	root = new Node<Type>;
	root->item = other.root->item;
	Node<Type>* curr = root;
	int side = 0;

	copyTree(curr, tmp);

}

template <class Type>
void BinaryTree<Type>::copyTree(Node<Type>* curr, Node<Type>* toCopy) {		//copy helper function
	curr->item = toCopy->item;
	curr->left = nullptr;
	curr->right = nullptr;

	if (toCopy->left != nullptr) {		//if the left of the copied item has something
		curr->left = new Node<Type>;	//make a new node in curr
		copyTree(curr->left, toCopy->left);	//recursively copy it using copyTree
	}
	if (toCopy->right != nullptr) {		//same here but to the right
		curr->right = new Node<Type>;
		copyTree(curr->right, toCopy->right);
	}
}

template <class Type>
BinaryTree<Type>::~BinaryTree(){
	destroy(root);
}

template <class Type>
void BinaryTree<Type>::destroy(Node<Type> * curr){
	if (curr != nullptr) {
		destroy(curr->left);
		destroy(curr->right);
		delete curr;
		curr = nullptr;
	}
}

template <class Type>
void BinaryTree<Type>::insert(Type item){
	if (root == nullptr) {
		root = new Node<Type>;
		root->item = item;
		root->left = nullptr;
		root->right = nullptr;
	}
	else {
		insert(item, root);
	}
}

template <class Type>
void BinaryTree<Type>::insert(Type item, Node<Type> * curr){
	if (item < curr->item) {
		if (curr->left == nullptr) {
			Node<Type>* tmp = new Node<Type>();
			tmp->item = item;
			tmp->right = nullptr;
			tmp->left = nullptr;
			curr->left = tmp;
		}
		else {
			insert(item, curr->left);
		}//end of inner if

	}//end of outer if
	else {
		if (curr->right == nullptr) {
			Node<Type>* tmp = new Node<Type>();
			tmp->item = item;
			tmp->right = nullptr;
			tmp->left = nullptr;
			curr->right = tmp;
		}
		else {
			insert(item, curr->right);
		}
	}
}


template <class Type>
void BinaryTree<Type>::preOrder(){
	std::cout << "Pre Order: ";
	preOrder(root);
}
template <class Type>
void BinaryTree<Type>::preOrder(Node<Type> *curr){
	if (curr) {
		std::cout << curr->item << " ";
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

template <class Type>
void BinaryTree<Type>::inOrder(){
	std::cout << "In Order: ";
	inOrder(root);
}
template <class Type>
void BinaryTree<Type>::inOrder(Node<Type> *curr){
	if (curr) {
		preOrder(curr->left);
		std::cout << curr->item << " ";
		preOrder(curr->right);
	}
}

template <class Type>
void BinaryTree<Type>::postOrder(){
	std::cout << "Post Order: ";
	postOrder(root);
}
template <class Type>
void BinaryTree<Type>::postOrder(Node<Type> *curr){
	if (curr) {
		preOrder(curr->left);
		preOrder(curr->right);
		std::cout << curr->item << " ";
	}
}


template <class Type>
int BinaryTree<Type>::nodeCount(){
	return nodeCount(root);
}

template <class Type>
int BinaryTree<Type>::nodeCount(Node<Type> *curr){
	if (curr) {
		return 1 + nodeCount(curr->left) + nodeCount(curr->right);
	}
	return 0;
}

template <class Type>
int BinaryTree<Type>::leavesCount(){
	return leavesCount(root->left) + leavesCount(root->right);
}

template <class Type>
int BinaryTree<Type>::leavesCount(Node<Type> *curr){
	if (!curr) {
		return 0;
	}
	else if (!curr->left && !curr->right) {		//return a one if the node has no children
		return 1;
	}
	else {
		return leavesCount(curr->left) + leavesCount(curr->right);	//otherwise keep recursively checking the tree
	}
}


template <class Type>
Node<Type>*BinaryTree<Type>::find(Type item){
	if (root->item == item) {
		return root;
	}
	else {
		find(item, root);
	}
}


template <class Type>
Node<Type>*BinaryTree<Type>::find(Type item, Node<Type>*curr){
	
	if (item == curr->item) {
		return curr;
	}
	if(item < curr->item && curr->left != nullptr) {
		return find(item, curr->left);
	}
	if (item > curr->item && curr->right != nullptr) {
		return find(item, curr->right);
	}
	return nullptr;
}


template <class Type>
Node<Type>*BinaryTree<Type>::findRightMostNode(Node<Type> *curr){
	if (!curr->right) {			//if a right node doesn't exist return curr
		return curr;
	}
	else {
		findRightMostNode(curr->right);	//otherwise use recursion to continue down the tree
	}
}

template <class Type>
void BinaryTree<Type>::remove(Type item){
	Node<Type>* successor;
	Node<Type>* successorparent = root->right;
	if (root->item == item) {
		successor = root->right;
		while (successor->left) {			//get the leftmost node on the right
			successor = successor->left;
		}
		while (successorparent->left != successor) {	//get the one pointing to the successor
			successorparent = successorparent->left;
		}
		auto temp = root->item;				//store the old value in the root	
		root->item = successor->item;		//change the roots value
		successor->item = temp;				
		successorparent->left = successor->right;	//change the pointer to point at the deleted nodes child
		delete successor;		//delete the node
	}
	else {
		remove(item, root);
	}
}


template <class Type>
Node<Type>* BinaryTree<Type>::remove(Type item, Node<Type>* curr){

	Node<Type>* par = nullptr;		//this will point to the node that is the parent of cur 
	Node<Type>* cur = this->root;

	while (cur) {	
		if (cur->item == item) {
			if (!cur->left && !cur->right) {
				if (!par) {
					root = nullptr;
				}
				else if (par->left == cur) {		//if the left of the node equals the removable item
					par->left = nullptr;			//stop pointing at it
					delete cur;						//delete it
				}
				else {
					par->right = nullptr;
					delete cur;
				}

			}
			else if (cur->left && !cur->right) {	//if the node deleted has a left child but no right
				if (!par) {		
					root = cur->right;
				}
				else if (par->left == cur) {
					par->left = cur->left;
					delete cur;
				}
				else {
					par->right = cur->left;
					delete cur;
				}
			}
			else if (!cur->left && cur->right) {	//if the node deleted has a right child but no left
				if (!par) {
					root = cur->right;
				}
				else if (par->left == cur) {
					par->left = cur->right;
					delete cur;
				}
				else {
					par->right = cur->right;
					delete cur;
				}
			}
			else {		//if the deleted node has both a right and a left child
				Node<Type>* suc = cur->right;
				while (suc->left) {		//find the left most node on the right
					suc = suc->left;
				}
				auto successorData = suc->item;	//store the number that this node holds
				remove(suc->item, curr);		//delete the original node that held this value
				cur->item = successorData;		//replace the value that the program wanted to delete at the beginning
			}
			return curr;
		}
		else if (cur->item < item) {	//otherwise check the value held, if it's larger than cur go right, smaller go left
			par = cur;					//increment the par variable to equal the old cur
			cur = cur->right;
		}
		else {
			par = cur;
			cur = cur->left;
		}
	}
		return curr;
}

template <class Type>
int BinaryTree<Type>::height(){ 
	Node<Type>* curr = root;

	if (!curr) {
		return -1;
	}
	else {
		return height(curr);
	}
}
template <class Type>
int BinaryTree<Type>::height(Node<Type>*curr){
	if (!curr) {
		return -1;			//no curr return -1
	}

	int leftHeight = height(curr->left);
	int rightHeight = height(curr->right);

	if (leftHeight > rightHeight) {	//compare the heights of both branches whatever is bigger return that plus 1(because of the root)
		return 1 + leftHeight;
	}
	else {
		return 1 + rightHeight;
	}
}

#endif // BINARY_TREE_H
