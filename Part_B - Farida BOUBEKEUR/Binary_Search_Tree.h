// Farida Boubekeur
// Header file that contains AVL class with its functions
#include <iostream>
#include "TreeNode.h"
using namespace std;

class BSTree
{
public:
  BSTree();                // default constructor
  BSTree(const Patient &); // parameterized constructor

  void insert(const Patient &);          // inesrt a patient  in the BST
  void remove(const Patient &);          // remove a patient from BST
  bool contains(const Patient &);        // check if a patient is already added
  bool isEmpty(void) const;              // check if BST is empty
  Patient getPatient(const int &) const; // get a spesific patient
  int getTotalPatient() const;           // get numebr of current patients in ICU
  void print(void) const;                // print the content of the bst

private:
  TreeNode *root;
  int totalPatient; // current number of patient in the BST

  // utility function to insert
  void insertHelper(TreeNode *root, const Patient &p)
  {
    TreeNode *new_node = new TreeNode(p);

    if (p.getKey() > root->patient->getKey())
    {
      if (root->right == nullptr)
      {
        root->right = new_node;
        totalPatient++;
        return;
      }
      else
        insertHelper(root->right, p);
    }
    else if (p.getKey() < root->patient->getKey())
    {

      if (root->left == nullptr)
      {
        root->left = new_node;
        totalPatient++;
        return;
      }
      else
        insertHelper(root->left, p);
    }

    // case if two patients have same key is not allowed
    else
    {
      cout << "Patient already exists in the ICU service" << endl;
      return;
    }
  }

  // utility function to search for the minimum ID in the tree
  TreeNode *minInTree(TreeNode *root)
  {
    TreeNode *temp = root;
    // search for the last left node in the tree
    while (temp->left != nullptr)
      temp = temp->left;

    // last left node (MIN) found
    return temp;
  }

  // Utility function to check whether an element exists in the tree
  bool contains(TreeNode *root, const Patient *p) const
  {
    if (root == nullptr)
      return false;
    if (root->patient->getID() == p->getID())
      return true;

    if (p->getKey() > root->patient->getKey())
      return contains(root->right, p);
    else if (p->getKey() < root->patient->getKey())
      return contains(root->left, p);
  }

  // utility function to remove a patient
  TreeNode *removeHelper(TreeNode *root, const Patient *p)
  {

    if (isEmpty())
    {
      cout << "ICU service is empty" << endl;
      return root;
    }

    if (!contains(root, p))
    {
      cout << "NO such patient in ICU service" << endl;
      return nullptr;
    }

    if (p->getKey() > root->patient->getKey())
      root->right = removeHelper(root->right, p);

    else if (p->getKey() < root->patient->getKey())
      root->left = removeHelper(root->left, p);

    // when the root of subtree is the patient to be deleted
    else
    {
      // case 1: root with one or no child
      if (root->left == nullptr || root->right == nullptr)
      {
        // case 1.1: root with one child
        if (root->left != nullptr || root->right != nullptr)
        {
          // we know that at this stage, the root has only one non-null child
          // so we choos the non-null one
          TreeNode *temp = (root->left ? root->left : root->right);
          *root = *temp;
          free(temp);
          temp = nullptr;
          totalPatient--;
        }
        // case 1.2: root with no children
        else
        {
          root = nullptr;
          totalPatient--;
        }
      }
      // case 2: root with two children
      else
      {
        // find patient with smallest ID in right subtree
        TreeNode *temp = minInTree(root->right);
        root = temp;
        root->right = removeHelper(root->right, temp->patient);
      }
    }

    return root;
  }

  // Utility function to find a patient with an id
  Patient getPatienthelper(const int &key, TreeNode *root) const
  {
    Patient *r = nullptr;
    if (root == nullptr)
      return *r;
    if (root->patient->getKey() == key)
      return *root->patient;

    if (key < root->patient->getKey())
      return getPatienthelper(key, root->left);

    if (key > root->patient->getKey())
      return getPatienthelper(key, root->right);
  }

  // Utility function to Print ICU Patients' name
  void printHelper(TreeNode *temp) const
  {
    if (root == nullptr)
    {
      return;
    }
    if (temp->left != nullptr)
      printHelper(temp->left);
    cout << "First Name: " << temp->patient->getFirstname() << endl;
    cout << "Last Name:  " << temp->patient->getLastname() << endl;
    cout << "Key: " << temp->patient->getKey() << endl;
    if (temp->right != nullptr)
      printHelper(temp->right);
  }
};

// BSTree class Function

BSTree::BSTree()
{
  root = nullptr;
  totalPatient = 0;
}

BSTree::BSTree(const Patient &p) : totalPatient(0)
{
  root->patient = new Patient(p);
  root->left = nullptr;
  root->right = nullptr;
}

bool BSTree::isEmpty(void) const { return (root == nullptr); }
bool BSTree::contains(const Patient &p)
{
  return contains(root, &p);
}
void BSTree::insert(const Patient &p)
{
  if (isEmpty())
  {
    root = new TreeNode(p);
    totalPatient++;
    Patient temp;
    temp = p;
    temp.addPatientFile();
    return;
  }
  insertHelper(root, p);
  Patient temp;
  temp = p;
  temp.addPatientFile();
}

void BSTree::remove(const Patient &p)
{
  removeHelper(root, &p);
}

int BSTree::getTotalPatient() const
{
  return totalPatient;
}

void BSTree::print() const
{
  printHelper(root);
}
Patient BSTree::getPatient(const int &key) const
{
  if (root == nullptr)
  {
    Patient *r = nullptr;
    cout << "No patient with this ID." << endl;
    return *r;
  }

  Patient p = getPatienthelper(key, root);
  if (&p == nullptr)
  {

    cout << "No patient with this ID" << endl;
    return p;
  }

  else
    return p;
}
