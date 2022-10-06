#pragma once
#include "binary_tree.h"
#include <iostream>
#include <string>
class test
{
public:
	/*
	* insert test
	* remove test
	* balance test
	* print test
	* search test
	*/
	void insert_test();
	void remove_test();
	void balance_test();
	void search_test();
	std::string random_name();
	std::string random_id();
};
void test::insert_test()
{
	Binary_tree bst;
	int i = 0;
	std::cout << "insert test: " << std::endl;
	std::cout << "enter amount of id's to insert into tree: ";
	std::cin >> i;
	for (int j = 0; j < i; j++)
	{
		std::cout << j << ": ";
		bst.insert(random_id(), random_name());
	}
	std::queue<Binary_tree::Node*> q;
	q = bst.inorder_q();
	while (!q.empty())
	{
		if (bst.priv_search(q.front()->id,q.front()) == nullptr)
		{
			//add_failed_nodes(str_id, name, id, fail_code
			bst.add_failed_nodes(q.front()->id_str, q.front()->name, q.front()->id, 5);
		}
		q.pop();
	}
	bst.display_failed();
	std::cout << "clearing tree..." << std::endl;
}
void test::remove_test()
{
	Binary_tree bst;
	int i = 0;
	std::queue<int> q;
	std::queue<Binary_tree::Node*> j;
	std::cout << "remove test: " << std::endl;
	std::cout << "enter amount of id's to insert into tree: ";
	std::cin >> i;
	for (int j = 0; j < i; j++)
	{
		//std::cout << j << ": ";
		bst.insert(random_id(), random_name());
	}
	q = bst.inorder();
	//j = bst.inorder_q();
	//call remove function for entire queue
	while (!q.empty())
	{
		std::cout << q.front() << ": ";
		bst.remove(q.front());
		q.pop();
	}
	//get queue of (hopefully) empty tree
	j = bst.inorder_q();
	while (!j.empty())
	{
		//search the tree for the specific node starting at the node itself
		if (bst.priv_search(j.front()->id, j.front()) != nullptr)
		{
			//add_failed_nodes(str_id, name, id, fail_code
			bst.add_failed_nodes(j.front()->id_str, j.front()->name, j.front()->id, 6);
		}
		j.pop();
	}
	bst.display_failed();
	std::cout << "clearing tree..." << std::endl;
}
void test::balance_test()
{
	std::cout << "balance test: " << std::endl;
	Binary_tree bst;
	int i = 0;
	std::cout << "enter amount of id's to insert into tree: ";
	std::cin >> i;
	for (int j = 0; j < i; j++)
	{
		//std::cout << j << ": ";
		bst.insert(random_id(), random_name());
	}
	std::queue<Binary_tree::Node*> q;
	q = bst.inorder_q();
	while (!q.empty())
	{
		std::cout << q.front()->id << ": " << q.front()->balance_factor << std::endl;
		if (bst.check_balance(q.front()) < -1 || bst.check_balance(q.front()) > 1)
		{
			//add_failed_nodes(str_id, name, id, fail_code
			bst.add_failed_nodes(q.front()->id_str, q.front()->name, q.front()->id, 2);
		}
		q.pop();
	}
	bst.display_failed();
	std::cout << "clearing tree..." << std::endl;
}

void test::search_test()
{
	Binary_tree bst;
	int i = 0;
	std::queue<int> q;
	std::queue<Binary_tree::Node*> j;
	std::cout << "search test: " << std::endl;
	std::cout << "enter amount of id's to insert into tree: ";
	std::cin >> i;
	for (int j = 0; j < i; j++)
	{
		//std::cout << j << ": ";
		bst.insert(random_id(), random_name());
	}
	q = bst.inorder();
	j = bst.preorder_q();

	//j = bst.inorder_q();
	//call remove function for entire queue
	while (!j.empty())
	{
		std::cout << j.front()->id << std::endl;
		if (bst.priv_search(j.front()->id,bst.get_tree_root()) == nullptr)
		{
			bst.add_failed_nodes(j.front()->id_str, j.front()->name, j.front()->id, 4);
		}
		j.pop();
	}
	
	bst.display_failed();
	std::cout << "clearing tree..." << std::endl;
}

std::string test::random_name()
{
	std::vector<char> alphabet = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	std::string name = "";
	for (int i = 0; i < 5; i++)
	{
		name = name + alphabet.at(rand() % (alphabet.size() - 1));
	}
	name = name + " ";
	for (int i = 0; i < 5; i++)
	{
		name = name + alphabet.at(rand() % (alphabet.size() - 1));
	}
	return name;
}
std::string test::random_id()
{
	std::vector<char> numbers= { '0','1','2','3','4','5','6','7','8','9'};
	std::string id = "";
	for (int i = 0; i < 8; i++)
	{
		id = id + numbers.at(rand() % (numbers.size() - 1));
	}
	return id;
}