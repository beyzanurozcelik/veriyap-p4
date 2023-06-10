#include<stdio.h>
#include<stdlib.h>

struct tnode {
	int id;
	int no;
	struct tnode *left;
	struct tnode *right;
};

struct snode {
	int id;
	int no;
	int leveli;
	int levelii;
	char levelc;
	struct snode *next;
};

struct tnode *addtotree(struct tnode *root, int id, int no) {
	struct tnode *newnode = malloc(sizeof(struct tnode));
	newnode -> no = no;
	newnode -> id = id;
	newnode -> left = NULL;
	newnode -> right = NULL;
	if (root == NULL) {
		root = newnode;
	}
	else{
		struct tnode *head, *headpre;
		head = root;
		while (head != NULL) {
			if (newnode->no < head->no) {
				headpre = head;
				head = head->left;
			}
			else {
				headpre = head;
				head = head->right;
			}
		}
		if (newnode->no < headpre->no) {
			headpre->left = newnode;
		}
		else {
			headpre->right = newnode;
		}
	}
	return root;
}

void printinorder(struct tnode *root) {
	if (root == NULL) {
		return;
	}
	printinorder(root->left);
	printf("%d %d\n",root->id,root->no);
	printinorder(root->right);

}

int treeheight(struct tnode *root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int lefth = treeheight(root->left);
		int righth = treeheight(root->right);
		
		if (lefth > righth) {
			return lefth+1;
		}
		else {
			return righth+1;
		}
	}
}
void addlevel(struct tnode *root,int level,struct snode **head) {
	struct snode *temp = *head;
	if (root == NULL) {
		return;
	}
	if (level == 1) {
		struct snode *newnode = malloc(sizeof(struct snode));
		newnode -> id = root->id;
		newnode -> no = root -> no;
		newnode -> next = NULL;
		if (*head == NULL) {
			*head = newnode;
		}
		else {
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newnode;
		}
		
	}
	else if (level > 1){
		addlevel(root->left,level-1,head);
		addlevel(root->right, level-1,head);
	}
}

void lllevelorder(struct tnode *root,struct snode **head) {
	int h = treeheight(root);
	for (int i=1; i<=h; i++) {
		addlevel(root,i,head);
	}
}


int main() {
	struct snode *head = NULL;
	struct tnode *root = NULL;
	int id1=0,no1;
	while (id1 != -1) {
		scanf("%d",&id1);
		if (id1 != -1) {
			scanf("%d",&no1);
			root = addtotree(root,id1,no1);
		}
	}
	
	printinorder(root);
	printf("\n");

	lllevelorder(root,&head);
	
	struct snode *temp = head;
	
	struct tnode *root2 = root,*root3;
	char c;
	
	while (temp != NULL) {
		if (temp == head) {
			printf("%d %d\n",temp->id,temp->no);
		}
		else {
			int a = temp->no;
			int count = 0;
			while (root2->no != a) {
				count++;
				if (a < root2->no) {
					root3 = root2;
					c = 'L';
					root2 = root2->left;
				}
				else {
					root3 = root2;
					c = 'R';
					root2 = root2->right;
				}
				
			}
			temp->leveli = root3->no;
			temp->levelc = c;
			temp->levelii = count+1;
		}
		temp = temp->next;
		root2 = root;
	}
	temp = head;
	temp = temp->next;
	while (temp != NULL) {
		if (temp-> next != NULL) {
		if (temp->levelii != temp->next->levelii) {
			printf("%d %d %c%d %c%c \n",temp->id,temp->no,'(',temp->leveli,temp->levelc,')');
		}
		else {
			printf("%d %d %c%d %c%c ",temp->id,temp->no,'(',temp->leveli,temp->levelc,')');
		}
		}
		else {
			printf("%d %d %c%d %c%c",temp->id,temp->no,'(',temp->leveli,temp->levelc,')');
		}
		temp = temp->next;
	}
	
	return 0;

}
















