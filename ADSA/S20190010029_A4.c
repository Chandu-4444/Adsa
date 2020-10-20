#include <stdio.h>
#include <stdlib.h>

// An AVL tree node
struct node {
  int key;
  struct node *left;
  struct node *right;
  int height;
  int count;
};
int count = 0, found=0;

int height(struct node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

struct node *newNode(int key) {
  struct node *node = (struct node *)malloc(sizeof(struct node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  node->count = 1;
  return (node);
}

struct node *rightRotate(struct node *y) {
  struct node *x = y->left;
  struct node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

struct node *leftRotate(struct node *x) {
  struct node *y = x->right;
  struct node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getBalance(struct node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

struct node *insert(struct node *node, int key) {
  if (node == NULL)
    return (newNode(key));

  if (key == node->key) {
    (node->count)++;
    return node;
  }

  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  node->height = max(height(node->left), height(node->right)) + 1;

  int balance = getBalance(node);

  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct node *minValueNode(struct node *node) {
  struct node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

struct node *deleteNode(struct node *root, int key) {

  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);

  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {

    if (root->count > 1) {
      (root->count)--;
      return root;
    }
    if ((root->left == NULL) || (root->right == NULL)) {
      struct node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;

      free(temp);
    } else {
      struct node *temp = minValueNode(root->right);

      root->key = temp->key;
      root->count = temp->count;
      temp->count = 1;

      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  root->height = max(height(root->left), height(root->right)) + 1;

  int balance = getBalance(root);

  // If this node becomes unbalanced, then there are 4 cases

  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void InOrder(struct node *root) {
  if (root != NULL) {
    InOrder(root->left);
    for (int i = 0; i < root->count; i++)
      printf("%d ", root->key);
    InOrder(root->right);
  }
}

void Frequency(struct node *root, int val) {
  if (root != NULL) {
    Frequency(root->left, val);
    if (root->key == val) {
      count = root->count;
    }
    Frequency(root->right, val);
  }
}




void Select(struct node *root, int val) {
  if (root) {
    Select(root->left, val);
    if (count == val) {
      printf("The Element In Position %d Is: %d\n", val, root->key);
      found =1;
    }
    count++;
    Select(root->right, val);
  }
}

int main() {
  struct node *root = NULL;
  int choice, val;
  printf("\t0. Exit\n\t1. Insert(M, i)\n\t2. Remove(M, i)\n\t3. Frequency(M, "
         "i)\n\t4. Select(M, i)\n");
  printf("Enter Your Choice: ");
  scanf("%d", &choice);
  while (1) {
    switch (choice) {
    case 1:
      printf("Enter Value To Be Inserted: ");
      scanf("%d", &val);
      root = insert(root, val);
      InOrder(root);
      printf("\n");
      break;
    case 2:
      printf("Enter The Value To Be Removed: ");
      scanf("%d", &val);
      root = deleteNode(root, val);
      InOrder(root);
      printf("\n");
      break;
    case 3:
      printf("Enter The To Find Its Frequency: ");
      scanf("%d", &val);
      Frequency(root, val);
      printf("The Frequency Of %d Is: %d\n", val, count);
      count = 0;
      break;
    case 4:
      printf("Enter The Position: ");
      scanf("%d", &val);
      InOrder(root);
      printf("\n");
      Select(root, val);
      if(found==0)
      {
          printf("Set Has No Element At Index: %d\n", val);
      }
      count = 0;
      break;

    default:
      printf("Wrong Choice : %d!\n", choice);
      break;
    }
    printf("\t0. Exit\n\t1. Insert(M, i)\n\t2. Remove(M, i)\n\t3. Frequency(M, "
           "i)\n\t4. Select(M, i)\n");
    printf("Enter Your Choice: ");
    scanf("%d", &choice);
  }

  printf("\n");
  return 0;
}