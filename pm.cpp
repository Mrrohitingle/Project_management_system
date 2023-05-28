
/*____________________________________PROJECT MANAGEMENT SYSTEM_________________________________*/

#include<string>
#include<iostream>
#include<climits>
#define MAX 30
using namespace std;
int top=-1;
struct node
{
    int t_id;
    string t_name;
    string t_sdate;
    string t_edate;
    string t_resources;
    node *left;
    node *right;
}*stack[MAX];

node *create_node()
{
    node *temp=new node;
    cout <<"\nEnter Task-ID                : ";
    cin >> temp->t_id;
    cout <<"Enter Task Name              : ";
    cin.ignore();
    getline(cin,temp->t_name);
    cout <<"Enter Start Date of the Task : ";
    cin.ignore();
    getline(cin,temp->t_sdate);
    cout <<"Enter End Date of the Task   : ";
    cin.ignore();
    getline(cin,temp->t_edate);
    cout <<"Enter Resources required    : ";
    cin.ignore();
    getline(cin,temp->t_resources);
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

void push(node *x)
{
	stack[++top]=x;
}
node *pop(){
	return stack[top--];
}
bool isempty() {
   if(top == -1)
      return true;
   else
      return false;
}

struct node* create_bst(int t)
{
    node *temp,*ptr,*root=NULL;
    char ch;
    int i=0;
    do
    {
        temp=create_node();
        if(root==NULL)
        {
            root=temp;
        }
        else
        {
            ptr=root;
            while(ptr!=NULL)
            {
                if(temp->t_id<ptr->t_id)
                {
                    if(ptr->left==NULL)
                    {
                        ptr->left=temp;
                        break;
                    }
                    else
                    {
                        ptr=ptr->left;
                    }
                }
                else
                {
                    if(ptr->right==NULL)
                    {
                        ptr->right=temp;
                        break;
                    }
                    else
                    {
                        ptr=ptr->right;
                    }
                }
                
            }
            
        }
        i=i+1;
    }while(i!=t);
    return root;
}
node *inorder(node *h)
{
    node *temp;
    node*root=h;
    temp=h;
    do
    {
        while(temp!=NULL)
        {
            push(temp);
            temp=temp->left;
        }
        temp=pop();
        cout <<"\n\t\tTask Id           : "<<temp->t_id;
        cout <<"\n\t\tTask Name         : "<<temp->t_name;
        cout <<"\n\t\tTask Start Date   : "<<temp->t_sdate;
        cout <<"\n\t\tTask End Date     : "<<temp->t_edate;
        cout <<"\n\t\tTask Resources    : "<<temp->t_resources;
        cout <<"\n";
        temp=temp->right;
        
    } while (!isempty() || temp!=NULL);
    return root;
    
}
int sum(int freq[], int i, int j) 
{
    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

int minCostBST(int keys[], int freq[], int n) {
    // Create a 2D array to store the minimum costs
    int cost[n][n];

    // Initialize the cost[i][i] values as the frequency of the key
    for (int i = 0; i < n; i++)
        cost[i][i] = freq[i];

    // Fill in the rest of the cost array using dynamic programming
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L + 1; i++) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;

            // Try making all keys in the range keys[i..j] as the root
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) +
                        sum(freq, i, j);

                if (c < cost[i][j])
                    cost[i][j] = c;
            }
        }
    }

    // The minimum cost of the binary search tree is stored in cost[0][n-1]
    return cost[0][n - 1];
}
node *insert(node *h)
{
    node *temp,*ptr,*root=h;
    char ch;
    do
    {
        cout<<"\nEnter Info. About New Task";
        temp=create_node();
        if(root==NULL)
        {
            root=temp;
        }
        else
        {
            ptr=root;
            while(ptr!=NULL)
            {
                if(temp->t_id<ptr->t_id)
                {
                    if(ptr->left==NULL)
                    {
                        ptr->left=temp;
                        break;
                    }
                    else
                    {
                        ptr=ptr->left;
                    }
                }
                else
                {
                    if(ptr->right==NULL)
                    {
                        ptr->right=temp;
                        break;
                    }
                    else
                    {
                        ptr=ptr->right;
                    }
                }
                
            }
            
        }
        cout <<"\nWant To Add More(Y/N) : ";
        cin>>ch;
    }while(ch=='Y'||ch=='y');
    return root;
}
node* delete_task(node* root, int id) {
    if (!root) 
    {                                                        // base case: empty tree
        cout << "Tree is empty\n";
        return nullptr;
    }
        if (id < root->t_id)
        {                                                       // search left subtree
            root->left = delete_task(root->left, id);
        }
        else if (id > root->t_id) {                             // search right subtree
            root->right = delete_task(root->right, id);
        }
        else 
        {                                                 // node with id to be deleted found
            if (!root->left) {                                 // case 1: no left child
                node* temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right) {                          // case 2: no right child
                node* temp = root->left;
                delete root;
                return temp;
            }
                                                            // case 3: node has two children
                                                            // find inorder successor (smallest node in right subtree)
            node* temp = root->right;
            while (temp->left)
            {
                temp = temp->left;
            }
                                                            // copy the value of inorder successor to root
            root->t_id = temp->t_id;
            root->right = delete_task(root->right, temp->t_id);                                                // delete the inorder successor
                                                            
        }
    return root;
}
void search_task(node *root, int id) {
    if (root == NULL) {
        cout << "Task not found" << endl;
        return;
    }

    if (root->t_id == id) {
        cout << "\n\t\tTask Id           : " << root->t_id;
        cout << "\n\t\tTask Name         : " << root->t_name;
        cout << "\n\t\tTask Start Date   : " << root->t_sdate;
        cout << "\n\t\tTask End Date     : " << root->t_edate;
        cout << "\n\t\tTask Resources    : " << root->t_resources;
        cout << "\n";
        return;
    }

    if (id < root->t_id) {
        search_task(root->left, id);
    } else {
        search_task(root->right, id);
    }
}
int main()
{
    node *root;
    string username,pass,pr;
    char ch;
    int n,t,k;
    int keys[10]={0};
    int freq[10];
    cout << "\n\t\t\t LOGIN";
    do
    {
        cout <<"\n\tUsername  : ";
        cin >>username;
        cout <<"\tPassword   : ";
        cin >>pass;
        if(username!="usr" || pass!="pass")
        {
            cout <<"\n\tInvalid Username or Password...!!";
            cout <<"\n\t\t\t LOGIN ";
        }
        else
        {
            break;
        }
    }while(true);

    cout << "\n||_*_*_*_*_*_*_*_*_* PROJECT MANAGEMENT SYSTEM *_*_*_*_*_*_*_*_*_||";
    do
    {
        cout <<"\n\n\t\t1. Decide Schedule for the Project\n\t\t2. Display the Schedule\n\t\t3. Insert Task into Schedule\n\t\t4. Delete Task from your Schedule\n\t\t5. Search Task from your Schedule\n\t\t6. Minimumcost of binary search tree is\n\t\t7. Exit";
        cout << "\n\t\tEnter Your Choice    : ";
        cin >>n;
        switch (n)
        {
            case 1:
            cout <<"\n=============================================================";
            cout <<"\nEnter Name of Project   : ";
            cin.ignore();
            getline(cin,pr);
            cout << "Enter Number of Task require for Your Project   : ";
            cin>>t;
            for(int i=1;i<t;i++)
            {
                keys[i]=i;
            }
            root=create_bst(t);
            break;
        
            case 2:
            cout <<"\n==============================================================";
            cout <<"\nProject Name  : "<<pr;
            cout <<"\nSchedule      : ";
            root=inorder(root);
            break;

            case 3:
            cout <<"\n==============================================================";
            root=insert(root);
            t=t+1;
            break;

            case 4:
            cout <<"\n==============================================================";
            cout <<"\nEnter Task ID that you wants to deleted: ";
            cin >>k;
            root=delete_task(root,k);
            cout <<"\nTasK Deleted Successfully";
            root=inorder(root);
            break;

            case 5:
            cout << "\n==============================================================";
            cout << "\nEnter Task ID to search: ";
            cin >> k;
            search_task(root, k);
            break;

            case 6:
            cout << "\n==============================================================";
            for (int i = 0; i < t; i++) 
            {
                    cout << "\nEnter frequency of task " << i+1 << ": ";
                    cin >> freq[i];
            }
            cout <<"\n Cost of Optimal Binary Search Tree is  :"<< minCostBST(keys, freq, t);  
            break;
         
            case 7:
            cout <<"\nExiting ....";

            default :
            cout <<"\nInvalid Input";

        }
       
    }while (n != 7);
    
    
}
