#pragma once
#include <queue>
#include <string>
//got help from eric chen on 9/23/2022
//got help from liv on 9/26/2022
//got help from blake shaffer on 9/27/2022
//got help from richie on 10/3/2022
//got help from sarah on 10/3/2022

class Binary_tree
{
public:
	struct Node
	{
		int id;
		std::string name;
		std::string id_str;
		int balance_factor;
		Node* left;
		Node* right;
		Node()
		{
			left = nullptr;
			right = nullptr;
			id = 0;
			name = "";
			balance_factor = 0;
		}
		//for debugging only
		int fail_code = 0;
		//fail codes:
		/*
		* 0: no failure
		* 1: already exists
		* 2: bad balance
		* 3: unspecified error
		* 4: node doesnt exist
		* 5: failed to add
		* 6: failed to remove
		*/
		////////////////////
	};
	//constructor
	Binary_tree();
	//functions that help with inserting nodes
	void insert(std::string const&, std::string const&);
	//functions that help with removing nodes
	void remove(unsigned int const&);
	void remove_N(int const&);
	//functions that help with finding nodes
	void search(unsigned int const&);
	void search(std::string const&);
	//functions that help with printing
	void print_preorder_helper();
	void print_postorder_helper();
	void print_inorder_helper();
	void print_level_count();
	//for debugging only
	std::queue<int> inorder();
	void add_failed_nodes(std::string const&, std::string const&, int const&, int const&);
	void display_failed();
	std::queue<Node*> inorder_q();
	//int check_balance(Node*);
	//Node* priv_search(int const&, Node*);
	//Node* get_tree_root();
	//////////////////////
	//destructor
	~Binary_tree();

private:
	//functions that help with inserting nodes
	Node* create_new_node(std::string const&, std::string const&);
	Node* priv_insert(Node*, std::string const&, std::string const&);
	//functions that help with removing nodes
	Node* priv_remove(Node*, int const&);
	//functions that help with printing
	void print_queue(std::queue< Binary_tree::Node*>);
	//functions that help with finding nodes
	Node* priv_search(int const&, Node*);
	std::queue<Node*> priv_search(std::queue<Binary_tree::Node*>, std::string const&, Node*);
	//getters
	int get_id(Node*);
	std::string get_name(Node*);
	Node* get_tree_root();
	int getheight(Node*);
	int check_balance(Node*);
	int get_balance_factor(Node*);
	std::queue< Binary_tree::Node*> get_preorder(Binary_tree::Node*, std::queue< Binary_tree::Node*>&);
	std::queue< Binary_tree::Node*> get_postorder(Binary_tree::Node*, std::queue< Binary_tree::Node*>&);
	std::queue< Binary_tree::Node*> get_inorder(Binary_tree::Node*, std::queue< Binary_tree::Node*>&);
	//mutators
	Node* balance(Node*);
	Node* rotate_left(Node*);
	Node* rotate_right(Node*);
	void change_node_data(Node*, unsigned int const&);
	//variables
	int node_count;
	Node* tree_root;
	//for debugging only
	std::queue<Node*> failed_add;
	///////////////////////
};

/*//constructor*/
Binary_tree::Binary_tree()
{
	this->tree_root = nullptr;
	this->node_count = 0;
}

/*//functions that help with inserting*/
Binary_tree::Node* Binary_tree::create_new_node(std::string const& id_str, std::string const& name)
{
	Binary_tree::Node* node = new Binary_tree::Node;
	node->id = stoi(id_str);
	node->name = name;
	node->id_str = id_str;
	if (this->node_count == 0)
	{
		this->tree_root = node;
	}
	this->node_count = node_count + 1;
	return node;
}
void Binary_tree::insert(std::string const& id_str, std::string const& name)
{
	int id = stoi(id_str);
	//check for duplicates
	if (priv_search(id, this->tree_root) == nullptr)
	{
		this->tree_root = priv_insert(this->tree_root, id_str, name);
		//check that we actually inserted it
		if (priv_search(id, this->tree_root) == nullptr)
		{
			std::cout << "unsuccessful" << std::endl;
		}
		else
		{
			std::cout << "successful" << std::endl;
		}
	}
	else //already exists
	{
		std::cout << "unsuccessful" << std::endl;
	}

}
Binary_tree::Node* Binary_tree::priv_insert(Binary_tree::Node* root, std::string const& id_str, std::string const& name)
{
	if (root == nullptr)
	{
		root = create_new_node(id_str, name);
	}
	else if (stoi(id_str) > root->id)
	{
		root->right = priv_insert(root->right,id_str,name);
	}
	else if (stoi(id_str) < root->id)
	{
		root->left = priv_insert(root->left, id_str,name);
	}
	root->balance_factor = check_balance(root);
	root = balance(root);
	return root;
}

/*//functions that help with removing*/
void Binary_tree::remove(unsigned int const& id)
{
	//check if id exists
	if (priv_search(id, this->tree_root) == nullptr)
	{
		std::cout << "unsuccessful" << std::endl;
	}
	else
	{
		this->tree_root = priv_remove(this->tree_root, id);
		if (priv_search(id, this->tree_root) != nullptr)
		{
			std::cout << "unsuccessful" << std::endl;
		}
		else
		{
			std::cout << "successful" << std::endl;
			this->node_count = this->node_count - 1;
		}

	}

	//this->node_count = this->node_count - 1;
}
void Binary_tree::remove_N(int const& N)
{
	std::queue<Binary_tree::Node*> q;
	get_inorder(this->tree_root, q);
	for (int i = 0; i < N; i++)
	{
		q.pop();
	}
	remove(q.front()->id);
	while (!q.empty())
	{
		q.pop();
	}
}
Binary_tree::Node* Binary_tree::priv_remove(Node* root, int const& id)
{
	//pass in tree root
	//return tree root but with node removed
	if (root == nullptr)
	{
		return root;
	}
	if (root->id == id)
	{
		if (root->left == nullptr && root->right == nullptr)
		{
			root = nullptr;
			delete root;
		}
		else if (root->left == nullptr && root->right != nullptr)
		{
			//set node equal to right node
			root = root->right;
		}
		else if (root->left != nullptr && root->right == nullptr)
		{
			//set node equal to left node
			root = root->left;

		}
		else if (root->left != nullptr && root->right != nullptr)
		{
			std::queue<Binary_tree::Node*> q; // = get_inorder(root->right, q); this specific line is causing bad_alloc
			get_inorder(root->right, q);
			Binary_tree::Node* M = root; //get_ios(root->right, root->right->id);
			int temp = root->right->id;
			std::string tempn = root->right->name;
			//get the smallest value
			while (!q.empty())
			{
				if (q.front()->id <= temp)
				{
					temp = q.front()->id;
					M = q.front();
				}
				q.pop();
			}
			//get value of ios
			temp = M->id;
			tempn = M->name;
			//delete the ios by passing in the right subtree
			root->right = priv_remove(root->right, temp);
			//set the root
			root->id = temp;
			root->name = tempn;
		}
	}
	else if (root->id > id)
	{
		root->left = priv_remove(root->left, id);
	}
	else if (root->id < id)
	{
		root->right = priv_remove(root->right, id);
	}

	return root;
}

/*//functions that help with printing*/
void Binary_tree::print_preorder_helper()
{
	std::queue< Binary_tree::Node*> q;
	print_queue(get_preorder(this->tree_root, q));
}
void Binary_tree::print_postorder_helper()
{
	std::queue< Binary_tree::Node*> q;
	print_queue(get_postorder(this->tree_root, q));
}
void Binary_tree::print_inorder_helper()
{
	std::queue< Binary_tree::Node*> q;
	print_queue(get_inorder(this->tree_root, q));
}
void Binary_tree::print_level_count()
{
	std::cout << getheight(this->tree_root) << std::endl;
}
void Binary_tree::print_queue(std::queue<Binary_tree::Node*> q)
{
	std::string queue;
	while (!q.empty())
	{
		queue = queue + q.front()->name + ", ";
		q.pop();
	}
	queue = queue.substr(0, queue.size() - 2);
	std::cout << queue << std::endl;
}

/*//functions that help with searching*/
void Binary_tree::search(unsigned int const& id)
{
	if (priv_search(id, this->tree_root) == nullptr)
	{
		std::cout << "unsuccessful" << std::endl;
	}
	else
	{
		std::cout << get_name(priv_search(id, this->tree_root)) << std::endl;
	}
}
void Binary_tree::search(std::string const& name)
{
	std::queue<Binary_tree::Node*> q;
	q = priv_search(q, name, this->tree_root);
	if (q.empty())
	{
		std::cout << "unsuccessful" << std::endl;
	}
	else
	{
		while (!q.empty())
		{
			std::cout << q.front()->id_str << std::endl;
			q.pop();
		}
	}
}
Binary_tree::Node* Binary_tree::priv_search(int const& id, Binary_tree::Node* node)
{
	if (node == nullptr)
	{
		return node;
	}
	else if (node->id == id)
	{
		return node;
	}
	else if (node->id > id)
	{
		node = priv_search(id, node->left);
	}
	else if (node->id < id)
	{
		node = priv_search(id, node->right);
	}
	return node;
}
std::queue<Binary_tree::Node*> Binary_tree::priv_search(std::queue<Binary_tree::Node*> q, std::string const& name, Binary_tree::Node* node)
{
	if (node == nullptr)
	{
		return q;
	}
	if (node->name == name)
	{
		//im 99.9999999999999% sure this is preorder but you never know
		q.push(node);
		q = priv_search(q, name, node->left);
		q = priv_search(q, name, node->right);
	}
	if (node->name != name)
	{
		q = priv_search(q, name, node->left);
	}

	if (node->name != name)
	{
		q = priv_search(q, name, node->right);
	}

	return q;
}

/*//getters*/
int Binary_tree::get_id(Binary_tree::Node* target)
{
	return target->id;
}
std::string Binary_tree::get_name(Node* root)
{
	return root->name;
}
Binary_tree::Node* Binary_tree::get_tree_root()
{
	return this->tree_root;
}
int Binary_tree::getheight(Binary_tree::Node* node)
{
	int count = 0;
	if (node == nullptr)
	{
		return count;
	}
	else
	{
		count = std::max(getheight(node->left), getheight(node->right)) + 1;
	}
	return count;
}
int Binary_tree::check_balance(Node* tree_root)
{
	return getheight(tree_root->left) - getheight(tree_root->right);
}
int Binary_tree::get_balance_factor(Node* root)
{
	return root->balance_factor;
}
//return a queue of our nodes in preorder
std::queue< Binary_tree::Node*> Binary_tree::get_preorder(Binary_tree::Node* root, std::queue< Binary_tree::Node*>& q)
{
	if (root == nullptr)
	{
		return q;
	}
	else
	{
		q.push(root);
		q = get_preorder(root->left, q);
		q = get_preorder(root->right, q);
	}
	return q;
}
//return a queue of our nodes in postorder
std::queue< Binary_tree::Node*> Binary_tree::get_postorder(Binary_tree::Node* root, std::queue< Binary_tree::Node*>& q)
{
	if (root == nullptr)
	{
		return q;
	}
	else
	{
		q = get_postorder(root->left, q);
		q = get_postorder(root->right, q);
		q.push(root);
	}
	return q;
}
//return a queue of our nodes in inorder
std::queue< Binary_tree::Node*> Binary_tree::get_inorder(Binary_tree::Node* root, std::queue< Binary_tree::Node*>& q)
{
	if (root == nullptr)
	{
		return q;
	}
	else
	{
		q = get_inorder(root->left, q);
		q.push(root);
		q = get_inorder(root->right, q);
	}
	return q;
}

/*//mutators*/
Binary_tree::Node* Binary_tree::balance(Node* root)
{
	//based off code from lecture slides (avl trees)
	if (root->balance_factor == -2)
	{
		if (root->right->balance_factor == 1)
		{
			root->right = rotate_right(root->right);
			root = rotate_left(root);
		}
		else
		{
			root = rotate_left(root);
		}
		root->left->balance_factor = check_balance(root->left);
		root->right->balance_factor = check_balance(root->right);
	}
	else if (root->balance_factor == 2)
	{
		if (root->left->balance_factor == -1)
		{
			root->left = rotate_left(root->left);
			root = rotate_right(root);
		}
		else
		{
			root = rotate_right(root);
		}
		root->left->balance_factor = check_balance(root->left);
		root->right->balance_factor = check_balance(root->right);
	}
	root->balance_factor = check_balance(root);
	return root;
}
//based off of the code in the lecture slides (AVL trees)
Binary_tree::Node* Binary_tree::rotate_left(Node* root)
{
	Binary_tree::Node* N = nullptr;
	Binary_tree::Node* node = nullptr;
	node = root->right->left;
	N = root->right;
	root->right = node;
	N->left = root;
	return N;
}
//based off of the code in the lecture slides (AVL trees)
Binary_tree::Node* Binary_tree::rotate_right(Node* root)
{
	Binary_tree::Node* N = nullptr;
	Binary_tree::Node* node = nullptr;
	node = root->left->right;
	N = root->left;
	root->left = node;
	N->right = root;
	return N;
}
void Binary_tree::change_node_data(Binary_tree::Node* target, unsigned int const& data)
{
	target->id = data;
}

/*//for debugging only*/
void Binary_tree::add_failed_nodes(std::string const& id_str, std::string const& name, int const& id, int const& fail_code)
{
	Binary_tree::Node* n = new Binary_tree::Node;
	n->id = id;
	n->name = name;
	n->id_str = id_str;
	n->fail_code = fail_code;
	failed_add.push(n);
}
///////////////////


/*//for debugging only*/
std::queue<int> Binary_tree::inorder()
{
	std::queue<Binary_tree::Node*> q;
	get_inorder(this->tree_root, q);
	std::queue<int> v;
	while (!q.empty())
	{
		v.push(q.front()->id);
		q.pop();
	}
	return v;
}
////////////////////////


/*//for debugging only*/
std::queue<Binary_tree::Node*> Binary_tree::inorder_q()
{
	std::queue<Binary_tree::Node*> q;
	get_inorder(this->tree_root, q);
	return q;
}
///////////////////////


/*//for debugging only*/
void Binary_tree::display_failed()
{
	if (!failed_add.empty())
	{
		while (!failed_add.empty())
		{
			std::cout << "id string: " << failed_add.front()->id_str << std::endl;
			std::cout << "id: " << failed_add.front()->id << std::endl;
			std::cout << "name: " << failed_add.front()->name << std::endl;
			if (failed_add.front()->fail_code == 1)
			{
				std::cout << "the id already exists inside the tree" << std::endl;
			}
			else if (failed_add.front()->fail_code == 2)
			{
				std::cout << "the balance is incorrect " << failed_add.front()->balance_factor <<std::endl;
			}
			else if (failed_add.front()->fail_code == 4)
			{
				std::cout << "node does not exist" << std::endl;
			}
			else
			{
				std::cout << "unspecified failure" << std::endl;
			}
			failed_add.pop();
		}
	}
	else
	{
		std::cout << "nothing failed!" << std::endl;
	}

}
///////////////////////

/*//destructor*/
Binary_tree::~Binary_tree()
{
	//for debugging only
	std::cout << "clearing tree..." << std::endl;
	//////////////////////////
	std::queue<Binary_tree::Node*> q;
	get_inorder(this->tree_root, q);
	while (!q.empty())
	{
		delete(q.front());
		q.pop();
	}
}



