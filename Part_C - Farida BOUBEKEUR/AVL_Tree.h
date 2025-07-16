// Farida Boubekeur
// Header file that contains AVL class with its functions

#include "TreeNode.h"

using namespace std;

class AvlTree
{
public:
  AvlTree();                // default constructor
  AvlTree(const Patient &); // parameterized constructor

  void insert(const Patient &);          // inesrt a patient  in the AVL
  void remove(const Patient &);          // remove a patient from AVL
  bool contains(const Patient &);        // check if a patient is already added
  bool isEmpty(void) const;              // check if AVL is empty
  Patient getPatient(const int &) const; // get a spesific patient
  int getTotalPatient() const;           // get numebr of current patients in ICU
  void print(void) const;                // print the content of the bst

  // functions related to AVL implementation
  int getBalancefactor();
  Patient *rRotate(TreeNode *);
  Patient *lRotate(TreeNode *);

private:
  TreeNode *root;
  int totalPatients; // current number of patient in the AVL

  // utility function to insert
  void insertHelper(TreeNode *root, const Patient &p)
  {
    TreeNode *new_node = new TreeNode(p);

    if (p.getKey() > root->patient->getKey())
    {
      if (root->right == nullptr)
      {
        root->right = new_node;
        totalPatients++;
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
        totalPatients++;
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

    // save AVL properties
    if (getBalancefactor() > 1 && p.getKey() < root->left->patient->getKey())
      root->patient = rRotate(root);
    else if (getBalancefactor() < -1 && p.getKey() > root->right->patient->getKey())
      root->patient = lRotate(root);
    else if (getBalancefactor() > 1 && p.getKey() > root->left->patient->getKey())
    {
      root->left->patient = lRotate(root->left);
      root->patient = rRotate(root);
    }
    else if (getBalancefactor() < -1 && p.getKey() < root->right->patient->getKey())
    {
      root->right->patient = rRotate(root->right);
      root->patient = lRotate(root);
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

  // Utility function to check whether an element exist in the AVL tree
  bool containes(TreeNode *root, const Patient *p) const
  {
    if (root == nullptr)
      return false;
    if (root->patient->getID() == p->getID())
      return true;

    if (p->getKey() > root->patient->getKey())
      return containes(root->right, p);
    else if (p->getKey() < root->patient->getKey())
      return containes(root->left, p);
  }
  // utility function to remove a patient
  TreeNode *removeHelper(TreeNode *root, const Patient *p)
  {
    // if root==null
    if (isEmpty())
    {
      cout << "ICU service is empty" << endl;
      return root;
    }

    if (!containes(root, p))
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
          totalPatients--;
        }
        // case 1.2: root with no children
        else
        {
          root = nullptr;
          totalPatients--;
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

    // save AVL Trees properties after deletion
    if (getBalancefactor() > 1 && p->getKey() < root->left->patient->getKey())
      root->patient = rRotate(root);
    else if (getBalancefactor() < -1 && p->getKey() > root->right->patient->getKey())
      root->patient = lRotate(root);
    else if (getBalancefactor() > 1 && p->getKey() > root->left->patient->getKey())
    {
      root->left->patient = lRotate(root->left);
      root->patient = rRotate(root);
    }
    else if (getBalancefactor() < -1 && p->getKey() < root->right->patient->getKey())
    {
      root->right->patient = rRotate(root->right);
      root->patient = lRotate(root);
    }

    return root;
  }

  // Utility function to find a patient with a key
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
    cout << "Last Name: " << temp->patient->getLastname() << endl;
    cout << "Key: " << temp->patient->getKey() << endl;
    if (temp->right != nullptr)
      printHelper(temp->right);
  }

  // utility function that counts a height of the AVL
  int heightFinder(TreeNode *temp)
  {
    if (temp == NULL)
      return -1;
    return 1 + max(heightFinder(temp->left), heightFinder(temp->right));
  }
  int Bfactor(TreeNode *temp)
  {
    if (temp == nullptr)
      return -1;
    else
      return (heightFinder(temp->left) - heightFinder(temp->right));
  }
};

// AvlTree class function

AvlTree::AvlTree() : root(nullptr), totalPatients(0) {}

AvlTree::AvlTree(const Patient &p) : totalPatients(0)
{
  root->patient = new Patient(p);
  root->left = nullptr;
  root->right = nullptr;
}

bool AvlTree::isEmpty(void) const { return (root == nullptr); }
bool AvlTree::contains(const Patient &p)
{
  return containes(root, &p);
}
void AvlTree::insert(const Patient &p)
{
  if (isEmpty())
  {
    root = new TreeNode(p);
    totalPatients++;
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

void AvlTree::remove(const Patient &p)
{
  removeHelper(root, &p);
}

int AvlTree::getTotalPatient() const { return totalPatients; }

Patient AvlTree::getPatient(const int &key) const
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

void AvlTree::print() const
{
  printHelper(root);
}

// AVL specified functions
int AvlTree::getBalancefactor()
{
  return Bfactor(root);
}
Patient *AvlTree::rRotate(TreeNode *temp)
{
  TreeNode *x;
  x->patient = temp->left->patient;
  TreeNode *y;
  y->patient = x->right->patient;
  x->right->patient = temp->patient; // x becomes root of the subTree
  temp->left->patient = y->patient;
  return x->patient;
}

Patient *AvlTree::lRotate(TreeNode *temp)
{
  TreeNode *x;
  x->patient = temp->right->patient;
  TreeNode *y;
  y->patient = x->left->patient;
  x->left = temp; // x becomes root of the sublTree
  temp->right->patient = y->patient;
  return x->patient;
}
