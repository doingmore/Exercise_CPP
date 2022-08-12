#include "BST.h"

// ======================== Constructors ========================
BST::BST()
	: m_root{ NULL }
{}

BST::BST(const int& value)
{
	m_root = new Node{ value };
}

// ======================== Constructors ========================
// 
// ======================== Rule Of three - Copy CTR and assignemnt operator ========================
// = delete
BST::~BST()
{
	deallocateALL(m_root);
}
// ======================== Rule Of three - Copy CTR and assignemnt operator ========================
// 
// ======================== Move Semantics ========================
BST::BST(BST&& other)
{
	m_root = other.m_root;
	other.m_root = NULL;
}
BST& BST::operator= (BST&& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (this->m_root != NULL)
	{
		deallocateALL(this->m_root);
		m_root = NULL;
	}

	this->m_root = other.m_root;
	other.m_root = NULL;

	return *this;
}
// ======================== Move Semantics ========================




void BST::insert(const int& newVelue)
{
	if (m_root == NULL)
	{
		m_root = new Node{ newVelue };
	}
	else
	{
		insertNewNode(m_root, newVelue);
	}
}

void BST::insertNewNode(Node* node, const int& newVelue)
{
	if (node == NULL) // for stop and go back
	{
		return;
	}
	else if (node->getValue() == newVelue) // if already have that value terminate insertion go back
	{
		return;
	}

	if (node->getValue() < newVelue)
	{
		insertNewNode(node->getRight(), newVelue);
		if (node->getRight() == NULL)
		{
			Node* newNode = new Node{ newVelue };
			node->setRight(newNode);
		}
		// else go back
	}
	else
	{
		insertNewNode(node->getLeft(), newVelue);
		if (node->getLeft() == NULL)
		{
			Node* newNode = new Node{ newVelue };
			node->setLeft(newNode);
		}
		// else go back
	}
}

void BST::deallocateALL(Node* node) // post travel
{
	if (node == NULL)
	{
		return;
	}

	deallocateALL(node->getLeft());
	deallocateALL(node->getRight());
	delete node;
}
