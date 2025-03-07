/**
	CS280 BST
	@file bst.h
	@author Sam Micka
	@version 9/23/2020
*/
#ifndef BST_H_
#define BST_H_
#include <iostream>
using namespace std;

// must use this struct
struct movie
{
	string title;
	int rating;
	int year;
	movie* parent = NULL;
	movie* leftChild = NULL;
	movie* rightChild = NULL;
};

class bst 
{
	private:
		movie* root;
		void destroy(movie* node); // helper function for destructor
	public:
		bst(); //constructor
		~bst(); //destructor
		movie* search(string title); // returns the node with the matching title
		void addMovie(string name, int rating, int year); //method for inserting a new movie
		void deleteMovie(string title); //method for removing a movie
		movie* findMin(movie* node); //helper function for deleteMovie
		void findMovie(string title); // method for finding and printing out the information about a movie
		void printMoviesRating(int rating); // helper function
		void printMoviesRating(movie* node, int rating); // method to print all movies in order with rating above a certain value
		void printMovies(); // helper function
		void printMovies(movie* node); // method (already implemented) that will print the movies in order
};

// Constructor
bst::bst() 
{
	root = NULL;
}

/*
* Method name: destroy
* Purpose: helper method for the destructor
* @param node - the current node
* @return none
* Note: recursively destroy nodes, doing a post-order traversal
*/
void bst::destroy(movie* node)
{
	if(node == NULL)
	{
		return;
	}
	destroy(node->leftChild);
	destroy(node->rightChild);
	delete node;
}

// Destructor
// use a post-order traversal to delete movies one at a time by
// calling destory with root
bst::~bst() 
{
	destroy(root);
}


/*
* Method name: search
* Purpose: accepts a title searches the tree for the title
* @param title - the title of the movie
* @return - pointer to the movie node with the title
* Note: Use the iterative approach (not recursive) so we don't
* 	have to send another node parameter.
* 	You can call this from various other methods!
*/
movie* bst::search(string title)
{
	movie* currentNode = this->root;
	while(currentNode != NULL)
	{
		if(currentNode->title == title)
		{
			// cout << "First" << endl;
			return currentNode;
		}
		if(currentNode->title < title)
		{
			// cout << "Second" << endl << currentNode->title << endl;
			currentNode = currentNode->rightChild;
		}else if(currentNode->title > title)
		{
			// cout << "Third" << endl << currentNode->title << endl;
			currentNode = currentNode->leftChild;
		}
	}
	return NULL;
}

/*
* Method name: addMovie
* Purpose: accepts a title and creates a new movie node, puts it in the BST
* @param title - the title of the movie
* @param rating - the integer rating of the movie
* @param year - the integer year that the movie came out
* @return - none
* Note: Create a new movie node with the specified parameters.
* 	then go through the tree to put it in the lexicographically correct
* 	spot in the tree.
*/
void bst::addMovie(string title, int rating, int year)
{	
	if(this->root==NULL)
	{
		this->root = new movie;
		this->root->title = title;
		this->root->rating = rating;
		this->root->year = year;
		return;
	}
	movie* tmp = root;
	movie* parent;
	while(tmp != NULL)
	{
		parent = tmp;
		// cout << "something" + title << endl;
		// cout << parent->title << endl;	
		if(parent->title > title)
		{
			tmp = parent->leftChild;
		}else if(parent->title < title)
		{
			tmp = parent ->rightChild;
		}
	}
	movie* newMovie = new movie;
	if(parent->title > title)
	{
		parent->leftChild = newMovie;
	}else if(parent->title < title)
	{
		parent->rightChild = newMovie;
	}
	newMovie->parent = parent;
	newMovie->title = title;
	newMovie->rating = rating;
	newMovie->year = year; 
}


/*
* Method name: findMin
* Purpose: accepts a node that you want to start your search at and returns the minimum
* 	value node in that subtree
* @param node - the start node
* @return - the node with the smallest title in the subtree starting at node
* Note: this is a helper function for deleteMovie!
*/
movie* bst::findMin(movie* node)
{
	// cout << node->rightChild->leftChild->title << endl;
	movie* currentNode = node->rightChild;
	movie* min;
	while(currentNode != NULL)
	{
		min = currentNode;
		currentNode = currentNode->leftChild;
	}
	// cout << "This is the min " + min->title;
	return min;
}

/*
* Method name: deleteMovie
* Purpose: accepts a title and removes
* @param title - the title of the movie to be removed 
* @return - none
* Note: find the movie with the title matching the input and
* 	remove it from the tree, remember, you may have to move things
* 	around to maintain the BST properties! You must follow the
* 	pseudocode on pages 178, 179, and 180 in the textbook
*/
void bst::deleteMovie(string title)
{
	movie* toDelete = search(title);
	// cout << toDelete->rightChild << endl;
	// cout << toDelete->leftChild->title << endl;
	if(toDelete->leftChild == NULL && toDelete->rightChild == NULL)
	{
		// cout << "first" << endl;
		if(toDelete->parent == NULL)
		{
			root = NULL;
		}else if(toDelete == toDelete->parent->leftChild)
		{
			toDelete->parent->leftChild = NULL;
		}else if(toDelete == toDelete->rightChild)
		{
			toDelete->parent->rightChild = NULL;
		}
		// cout << "second" << endl;
		delete toDelete;
		return; 
	}else if(toDelete->leftChild != NULL && toDelete->rightChild == NULL)
	{
		if(toDelete->parent == NULL)
		{
			root = toDelete->leftChild;
		}else if(toDelete == toDelete->parent->leftChild)
		{
			toDelete->parent->leftChild = toDelete->leftChild;
		}else if(toDelete ==  toDelete->parent->rightChild)
		{
			toDelete->parent->rightChild = toDelete->leftChild;
		}
		toDelete->leftChild->parent = toDelete->parent;
		delete toDelete; 
		return;
	}else if(toDelete->rightChild != NULL && toDelete->leftChild == NULL)
	{
		// cout << "Third" << endl;
		if(toDelete->parent == NULL)
		{
			root = toDelete->rightChild;
		}else if(toDelete == toDelete->parent->leftChild)
		{
			toDelete->parent->leftChild = toDelete->rightChild;
		}else if(toDelete ==  toDelete->parent->rightChild)
		{
			toDelete->parent->rightChild = toDelete->rightChild;
		}
		toDelete->rightChild->parent = toDelete->parent;
		delete toDelete;
		return;
	}else if(toDelete->rightChild != NULL && toDelete->leftChild != NULL)
	{
		movie* tmp = findMin(toDelete);
		if(tmp == tmp->parent->leftChild)
		{
			tmp->parent->leftChild = NULL;
		}else if(tmp == tmp->parent->rightChild)
		{
			tmp->parent->rightChild = NULL;
		}
		if(toDelete->parent == NULL)
		{
			// tmp = findMin(toDelete);
			root = tmp;
			tmp->parent = NULL;
		}else if(toDelete == toDelete->parent->leftChild)
		{
			// tmp = findMin(toDelete);
			tmp->parent = toDelete->parent;
			toDelete->parent->leftChild = tmp;
		}else if(toDelete == toDelete->parent->rightChild)
		{
			// tmp = findMin(toDelete);
			// cout << toDelete->parent->title << endl;
			// cout << tmp->title << endl;
			tmp->parent = toDelete->parent;
			toDelete->parent->rightChild = tmp;
		}
		// tmp->rightChild = toDelete->rightChild;
		tmp->leftChild = toDelete->leftChild;
		delete toDelete;
		return;
	}
}

/*
* Method name: findMovie
* @param title - the title of the movie
* @return - none
* Note: find the movie and print out the associated information. Hint,
* 		if you implement search first, this method is very easy!
*/
void bst::findMovie(string title)
{
	movie* found = search(title);
	cout << "Title: " << found->title << endl << "Rating: " << found->rating << endl << "Year: " << found->year << endl;
}

// helper function to call printMoviesRating with root
void bst::printMoviesRating(int rating)
{
	printMoviesRating(root, rating);
}


/*
* Method name: printBST
* Purpose: prints each movie's information, in-order traversal!
* @param node - the node to start at
* @param rating - the cut off rating, for example, rating = 3 then you should
					only print movies with a rating of 3 or higher
* @return - none
*/
void bst::printMoviesRating(movie* node, int rating)
{
	// cout << "First" << endl;
	// cout << (node == NULL) << endl;
	if(node == NULL)
	{
		// cout << "fourth" << endl;
		return;
	}
	// cout << "Second" << endl;
	printMoviesRating(node->leftChild, rating);
	// cout << "third" << endl;
	if(node->rating >= rating)
	{
		cout << "Title: " << node->title << endl << "Rating: " << node->rating << endl << "Year: " << node->year << endl;
	}
	printMoviesRating(node->rightChild, rating);
}


// helper function to call printMovies with root
void bst::printMovies()
{
	printMovies(root);
}

/*
* Method name: printBST
* Purpose: prints each movie's information, in-order traversal!
* @return - none
*/
void bst::printMovies(movie* node)
{
	if(node == NULL)
	{
		return;
	}
	printMovies(node->leftChild);
	cout << "Title: " << node->title << ", Rating: " << node->rating << ", Year: " << node->year << endl;
	printMovies(node->rightChild);
}
#endif
