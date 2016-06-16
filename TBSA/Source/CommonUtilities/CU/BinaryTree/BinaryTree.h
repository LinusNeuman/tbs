#pragma once
#include "CU/DLDebug/DL_Debug.h"
#include <ostream>


namespace CommonUtilities
{
	template<typename T>
	class BinaryTree;


	template <typename T>
	class TreeNode
	{
		friend BinaryTree < T > ;
	public:
		TreeNode(const T & aValueToHold)
		{
			myRight = nullptr;
			myLeft = nullptr;
			myData = aValueToHold;
		}
		T & GetData()
		{
			return myData;
		}

	private:
		TreeNode * myLeft;
		TreeNode * myRight;
		T myData;
	};

	template <typename T>
	class BinaryTree
	{
	public:
		BinaryTree();
		~BinaryTree();

		TreeNode<T>* GetRootNode() const;

		TreeNode<T>* Find(const T & aValue);

		void InsertNode(TreeNode<T>* aValueToInsert);
		void InsertNode(const T & aValueToInsert);

		void DeleteNode(TreeNode<T> * aNode);
		void DeleteNode(const T & aValue);

		void InOrderTraverse(void);
		void PostOrderTraverse(void);

	private:
		void PostOrderTraverseStream(std::ostream & aStreamToAddTo, const TreeNode<T> & aNode);
		void InOrderTraverseStream(std::ostream & aStreamToAddTo, const TreeNode<T> & aNode);
		void AddNode(TreeNode<T> & aNodeToAdd, TreeNode<T> & aNodeToCheck);
		TreeNode<T> * FindLocal(const T & aValueToFind, TreeNode<T> * aNodeToCheck);

		void DeleteNodeLocal(TreeNode<T>* & aParent, TreeNode<T> & aNodeToDelete);

		TreeNode<T> * myFirstNode;
	};

	template <typename T>
	void CommonUtilities::BinaryTree<T>::PostOrderTraverseStream(std::ostream & aStreamToAddTo, const TreeNode<T> & aNode)
	{
		if (aNode.myLeft != nullptr)
		{
			PostOrderTraverseStream(aStreamToAddTo, *aNode.myLeft);
		}
		if (aNode.myRight != nullptr)
		{
			PostOrderTraverseStream(aStreamToAddTo, *aNode.myRight);
		}
		aStreamToAddTo << aNode.myData << std::endl;
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::PostOrderTraverse(void)
	{
		if (myFirstNode != nullptr)
		{
			PostOrderTraverseStream(std::cout, *myFirstNode);
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::InOrderTraverseStream(std::ostream & aStreamToAddTo, const TreeNode<T> & aNode)
	{
		if (aNode.myLeft != nullptr)
		{
			InOrderTraverseStream(aStreamToAddTo, *aNode.myLeft);
		}
		aStreamToAddTo << aNode.myData << std::endl;

		if (aNode.myRight != nullptr)
		{
			InOrderTraverseStream(aStreamToAddTo, *aNode.myRight);
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::InOrderTraverse(void)
	{
		if (myFirstNode != nullptr)
		{
			InOrderTraverseStream(std::cout, *myFirstNode);
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::DeleteNode(const T & aValue)
	{
		DeleteNode(Find(aValue));
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::DeleteNodeLocal(TreeNode<T>* & aParent, TreeNode<T> & aNodeToDelete)
	{

		if (aNodeToDelete.myLeft == nullptr)
		{
			aParent = aNodeToDelete.myRight;
		}
		else if (aNodeToDelete.myRight == nullptr)
		{
			aParent = aNodeToDelete.myLeft;
		}
		else
		{
			TreeNode<T> * previous = &aNodeToDelete;
			TreeNode<T> * temp = aNodeToDelete.myLeft;

			while (temp->myRight != nullptr)
			{
				previous = temp;
				temp = temp->myRight;
			}

			aNodeToDelete.myData = temp->GetData();

			if (previous == &aNodeToDelete)
			{
				previous->myLeft = temp->myLeft;
			}
			else
			{
				previous->myRight = temp->myLeft;
			}
			delete temp;
			temp = nullptr;
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::DeleteNode(TreeNode<T> * aNode)
	{
		DL_ASSERT(myFirstNode != nullptr, "Trying to delete a node in an empty tree!");
		DL_ASSERT(aNode != nullptr, "Trying to delete a node that doesn't exist!");

		TreeNode<T> * toCheck = myFirstNode;

		if (aNode->GetData() == toCheck->GetData())
		{
			DeleteNodeLocal(myFirstNode, *aNode); 
			return;
		}

		while (toCheck->myLeft != nullptr || toCheck->myRight != nullptr)
		{
			if (toCheck->myLeft != nullptr)
			{
				if (aNode->GetData() == toCheck->myLeft->GetData())
				{
					DeleteNodeLocal(toCheck->myLeft, *aNode);
					return;
				}
			}
			if (toCheck->myRight != nullptr)
			{
				if (aNode->GetData() == toCheck->myRight->GetData())
				{
					DeleteNodeLocal(toCheck->myRight, *aNode);
					return;
				}
			}
			if (aNode->GetData() < toCheck->GetData())
			{
				toCheck = toCheck->myLeft;
			}
			else
			{
				toCheck = toCheck->myRight;
			}
		}
		DL_ASSERT(Find(aNode->GetData()) == nullptr, "Trying to delete a node that doesn't exist");
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::InsertNode(const T & aValueToInsert)
	{
		InsertNode(new TreeNode<T>(aValueToInsert));
	}

	template <typename T>
	TreeNode<T> * CommonUtilities::BinaryTree<T>::FindLocal(const T & aValueToFind, TreeNode<T> * aNodeToCheck)
	{
		if (aNodeToCheck == nullptr)
		{
			return aNodeToCheck;
		}

		if (aValueToFind == aNodeToCheck->GetData())
		{
			return aNodeToCheck;
		}
		else if (aValueToFind < aNodeToCheck->GetData())
		{
			return FindLocal(aValueToFind, aNodeToCheck->myLeft);
		}
		else
		{
			return FindLocal(aValueToFind, aNodeToCheck->myRight);
		}
	}

	template <typename T>
	TreeNode<T>* CommonUtilities::BinaryTree<T>::Find(const T & aValue)
	{
		return FindLocal(aValue, myFirstNode);
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::AddNode(TreeNode<T> & aNodeToAdd, TreeNode<T> & aNodeToCheck)
	{
		if (aNodeToAdd.GetData() < aNodeToCheck.GetData())
		{
			if (aNodeToCheck.myLeft == nullptr)
			{
				aNodeToCheck.myLeft = &aNodeToAdd;
			}
			else
			{
				AddNode(aNodeToAdd, *aNodeToCheck.myLeft);
			}
		}
		else
		{
			if (aNodeToCheck.myRight == nullptr)
			{
				aNodeToCheck.myRight = &aNodeToAdd;
			}
			else
			{
				AddNode(aNodeToAdd, *aNodeToCheck.myRight);
			}
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::InsertNode(TreeNode<T>* aValueToInsert)
	{
		DL_ASSERT(aValueToInsert != nullptr, "BinaryTree InsertNode trying to insert nullptr");

		if (myFirstNode != nullptr)
		{
			AddNode(*aValueToInsert, *myFirstNode);
		}
		else
		{
			myFirstNode = aValueToInsert;
		}
	}

	template <typename T>
	TreeNode<T>* CommonUtilities::BinaryTree<T>::GetRootNode() const
	{
		return myFirstNode;
	}

	template <typename T>
	CommonUtilities::BinaryTree<T>::BinaryTree()
	{
		myFirstNode = nullptr;
	}

	template <typename T>
	CommonUtilities::BinaryTree<T>::~BinaryTree()
	{

	}

};