/*Code to Enumerate ALL paths from the "Start" node to each "Stop" node, traversing cyclic paths ONLY once (otherwise, the program would run into an infinite loop). 
*/


#include<stdio.h>
#include<stdlib.h>
int l[100][100],p[100][100],c=0,n=0;
int m=1,mod=0;

struct NTree
{
	int dv;
	struct NTree *son;
	struct NTree *sib;
	char c;
};


struct llist
{
	struct NTree *node;
	struct llist *next;
	struct llist *pre;
};


struct NTree *create_NTree(int);

void add_son(int, int, struct NTree *);
void display_bfs(struct NTree *);
void display_dfs(struct NTree *);
struct NTree * search_node(int, struct NTree *);
struct llist * search_bfs_node(int, struct NTree *, struct llist *);
void display_all_paths(struct NTree *);
void display_all_paths_of_sons(struct llist *, struct NTree *, struct llist *);
struct llist * check_all_nodes_ll(struct llist *,struct NTree *);
void check_all_nodes(struct llist *);


struct llist * create_llist();
struct llist * queue_push(struct NTree *, struct llist **);
void queue_push1(struct NTree *, struct llist **);

struct NTree * queue_pop(struct llist **);
void stack_push(struct NTree *, struct llist **);
struct NTree * stack_pop(struct llist **);
void display_all_nodes_ll(struct llist *, struct llist *);
struct llist * create_a_copy(struct llist *);
void display_all_nodes_fll(struct llist *);


int main()
{
	int choice,flag=0,node_dv,son_dv;
	struct NTree *root,*ptr;

	do
	{
		printf("\t\tOperations Menu\n");
		printf("\t1. Create tree\n");
		printf("\t2. Insert a node\n");
		printf("\t3. Display  all path\n");
		printf("\t4. Display  all modified path\n");
		printf("\t5. Exit\n");
		printf("\n\tEnter your choice... ");
		scanf("%d",&choice);

		if(choice != 5 && choice !=1 && flag == 0)
		{
			printf("\nPlease create a tree first !!! \n\n");
			continue;
		}


		switch(choice)
		{
			case 1	:	if(flag==0)
							{
								printf("Enter the data value of the root node... ");
								scanf("%d",&node_dv);
								root=create_NTree(node_dv);
								flag=1;
							}
							else
								printf("Tree already created !!! \n\n");

							break;

			case 2	:	printf("Enter the value of the parent... ");
							scanf("%d",&node_dv);
							printf("Enter the value of the son... ");
							scanf("%d",&son_dv);
                           	do{
                            printf("\n\tSelect the choice.\n");
                            printf("\n\t1.If child entered is modified.\n");
                            printf("\t2.If child entered is not modified.\n");
                            scanf("%d",&m);
                            if(m!=1 && m!=2){printf("\n\tPlease Select the correct choice.\n");}
                            }while(m!=1 && m!=2);
							add_son(node_dv, son_dv, root);

							break;



			case 3	:	mod=0;
                        display_all_paths(root);
							break;
            case 4	:	mod=1;
                        display_all_paths(root);
							break;

			case 5	:	exit(0);
							break;

			default	:	printf("Please enter a valid choice !!!\n\n");
							break;

		}
	}
	while(choice!=5);
	return 0;
}


struct NTree * create_NTree(int node_dv)
{
	struct NTree *ptr;
	ptr=(struct NTree *)malloc(sizeof(struct NTree));
	ptr->dv = node_dv;
	ptr->son = NULL;
	ptr->sib = NULL;
	return ptr;
}


void add_son(int node_dv, int son_dv, struct NTree *root)
{
	struct NTree *node_ptr;
	struct NTree *snode_ptr;
	struct llist * ptr;
	ptr=NULL;
//	printf("+");
	ptr = search_bfs_node(node_dv,root,ptr);


	if(!ptr)
	{
		printf("Given parent node not found in the tree !!!\n");
		return;
	}
//printf("+");

	struct NTree *son_ptr;
	son_ptr = (struct NTree *)malloc(sizeof(struct NTree));
	son_ptr->dv = son_dv;
if(m==1){son_ptr->c='m';}else{son_ptr->c='n';}

//printf("*");


    snode_ptr = search_node(son_dv,root);

	if(!snode_ptr)
	{
	   // printf("-");

		son_ptr->son = NULL;

	}


else{	// printf("-");
    son_ptr->son = snode_ptr->son;

    }

        son_ptr->sib = NULL;
//printf("\n");
//display_all_nodes_fll(ptr);
struct  NTree *temp_pr1;
struct  llist *temp_pr2=ptr;
struct  llist *temp_pr;
//printf("\n");
while(ptr){
temp_pr=ptr;
	if(ptr->node->son == NULL)
	{
		ptr->node->son = son_ptr;
//printf("*");
	}
    else{
       // printf("-");
   //    check_all_nodes(ptr);
	temp_pr1 = ptr->node->son;

	while(temp_pr1->sib != NULL){printf("-%d\n",temp_pr1->dv);
		temp_pr1 = temp_pr1->sib;printf("-%d\n",temp_pr1->dv);}

	temp_pr1->sib = son_ptr;n++;return;
}
	ptr=temp_pr->next;
}
n++;
//display_all_nodes_fll(temp_pr2);
	return;
}




struct NTree * search_node(int node_dv, struct NTree *root)
{


	if(root==NULL)
		return NULL;
    int i=0;
	struct NTree *current_ptr;
	struct llist *queue;

	queue=NULL;

	queue_push(root, &queue);

	while(queue != NULL && i<=n)
	{
		current_ptr = queue_pop(&queue);
		if(current_ptr->dv == node_dv)
			return current_ptr;

		current_ptr = current_ptr->son;
		if(current_ptr)
		{i++;
			queue_push(current_ptr, &queue);
			current_ptr = current_ptr->sib;
			while(current_ptr)
			{
				queue_push(current_ptr, &queue);
				current_ptr = current_ptr->sib;
			}
		}
	}

	return NULL;
}


struct llist * create_llist()
{
	struct llist *ptr;
	ptr = (struct llist *)malloc(sizeof(struct llist));
	ptr->node = NULL;
	ptr->next = NULL;
	ptr->pre = NULL;
	return ptr;
}


struct llist *  queue_push(struct NTree *newptr, struct llist **h)
{

	if ((*h) == NULL)
	{
		(*h) = (struct llist *)malloc(sizeof(struct llist));
		(*h)->node = newptr;
		(*h)->next=NULL;
		(*h)->pre=NULL;
		return *h;
	}

	struct llist *tptr,*ptr;

	tptr=*h;

	while(tptr->next != NULL)
		tptr = tptr->next;
//		printf("-%d-\n",tptr->node->dv);

	ptr = (struct llist *)malloc(sizeof(struct llist));
	ptr->node = newptr;
	ptr->next = NULL;
    ptr->pre  = tptr;
	tptr->next = ptr;
	return ptr;
}


struct NTree * queue_pop(struct llist **h)
{
	struct NTree *tptr;
	struct llist *tempptr;

	tptr = (*h)->node;


	tempptr = *h;

	*h = (*h)->next;
	free(tempptr);
	return tptr;
}



void display_all_paths(struct NTree *root)
{
	if(root->son == NULL)
	{
		printf("%d->NULL\n\n",root->dv);
		return;
	}

	struct llist *pre_path_ll,*last_ptr;
	pre_path_ll = NULL;

	last_ptr=queue_push(root, &pre_path_ll);
	display_all_paths_of_sons(pre_path_ll,root->son,last_ptr);
	return;
}


void display_all_paths_of_sons(struct llist *history_ll, struct NTree *ptr,struct llist *last)
{
	struct llist *temp_history_ll,*last_ptr;
	struct NTree *temp_ptr;
	temp_ptr=ptr;

	while(temp_ptr!=NULL)
	{
		temp_history_ll = NULL;
		temp_history_ll = create_a_copy(history_ll);

        if(check_all_nodes_ll(last,temp_ptr)!=NULL){

        last_ptr = queue_push(temp_ptr, &temp_history_ll);
   // printf("-%d-",temp_ptr->dv);
		if(temp_ptr->son == NULL)
			display_all_nodes_ll(last_ptr,temp_history_ll);
		else
			display_all_paths_of_sons(temp_history_ll, temp_ptr->son,last_ptr);
        }else{//printf("loop");display_all_nodes_ll(last);
        return;}

		temp_ptr = temp_ptr->sib;
	}

	return;
}


struct llist * create_a_copy(struct llist *history_ll)
{
	struct llist *new_head, *newptr;

	new_head = (struct llist *)malloc(sizeof(struct llist));
	new_head->node=history_ll->node;
	new_head->next=NULL;
	new_head->pre=NULL;

	struct llist *ptr1,*ptr2;
	ptr1=history_ll->next;
	ptr2=new_head;

	while(ptr1 != NULL)
	{
		newptr=(struct llist *)malloc(sizeof(struct llist));
		newptr->node=ptr1->node;
		newptr->next=ptr1->next;
        newptr->pre =ptr1->pre;
		ptr2->next=newptr;
		ptr2->pre=newptr;
		ptr1=ptr1->next;
		ptr2=ptr2->next;
	}
	return new_head;
}


void display_all_nodes_ll(struct llist *ptr,struct llist *temp_ptr)
{
    int k=0;
	while(ptr!=NULL)
	{
	//	printf("%d->",ptr->node->dv);
if(ptr->node->c=='m'){k=1;}

		ptr=ptr->pre;
	}
	if(k==1){//display_all_nodes_fll(temp_ptr);


		while(temp_ptr!=NULL)
	{
		printf("%d->",temp_ptr->node->dv);
		temp_ptr=temp_ptr->next;
	}
}
	if(k==0 && mod!=1){
	    while(temp_ptr!=NULL)
	{
		printf("%d->",temp_ptr->node->dv);
		temp_ptr=temp_ptr->next;
	}
	}
	printf("\n");
}

struct llist * check_all_nodes_ll(struct llist *ptr,struct NTree *nod)
{


    struct llist *temp_ptr=ptr,*ptr1,*ptr2=ptr;
    int k=0;
	while(ptr!=NULL && ptr2!=NULL )
	{
	//    printf("A\n");
    if(k==0){
		if(ptr->node->dv==nod->dv){
	//    printf("B\n");
                ptr1=ptr;
                ptr2=ptr1->pre;
                ptr=temp_ptr;
                while(ptr2!=NULL && ptr2->node->dv==ptr->node->dv){
//	    printf("C\n");

                            if(ptr->node->dv==ptr1->node->dv){return NULL;}
                            else{ptr=ptr->pre;ptr2=ptr2->pre;}
                        }
   //                     	    printf("D\n");

                for(;ptr2->node->dv!=nod->dv && ptr2!=NULL;ptr2=ptr2->pre){if(ptr2->pre==NULL){return temp_ptr;}}
                k=1;
 //                                       	    printf("E\n");
   //                          printf("-%d-\n",nod->dv);

//printf("-*%d*-\n",ptr2->node->dv);
                ptr2=ptr2->pre;
//printf("-*%d*-\n",ptr2->node->dv);

        }
		ptr=ptr->pre;
    }
        if(k==1){
            ptr=temp_ptr;
            if(ptr2->node->dv==ptr->node->dv){


                while(ptr2!=NULL && ptr2->node->dv==ptr->node->dv){

                            if(ptr2->node->dv==ptr1->node->dv){return NULL;}
                            else{ptr=ptr->pre;ptr2=ptr2->pre;                           // printf("*%d %d*",ptr->node->dv,ptr2->node->dv);
}
                        }
                for(;ptr2->node->dv!=nod->dv && ptr2!=NULL;ptr2=ptr2->pre){if(ptr2->pre==NULL){return temp_ptr;}}

            }
                ptr2=ptr2->pre;
        }
        }


	return temp_ptr;
}







struct llist * search_bfs_node(int node_dv, struct NTree *root, struct llist *ptr)
{
	if(root==NULL)
	{
		printf("NULL\n");
		return NULL;
	}
    int i=0,p=1;
	struct NTree *current_ptr;
	struct llist *queue,*temp_ptr=ptr;

		     //printf("%d\n",n);

	queue=NULL;

	queue_push1(root, &queue);

	while(queue != NULL && i<=n)
	{
		current_ptr = queue_pop(&queue);
	//	     printf(" %d%d ",current_ptr->dv,node_dv);

		if(current_ptr->dv==node_dv){
		    temp_ptr=ptr;
	//	    printf("*");
	//	    display_all_nodes_fll(temp_ptr);printf("+*");
		    if(temp_ptr==NULL){queue_push1(current_ptr,&ptr);}
		    else{
		    for(p=1;temp_ptr->node!=current_ptr;temp_ptr=temp_ptr->next){
		  //     		     printf(" %d%d ",current_ptr->dv,temp_ptr->node->dv);
//printf("-+");
		       if(temp_ptr->next==NULL ){
		            queue_push1(current_ptr,&ptr);}}
		    }
		}
		current_ptr = current_ptr->son;
		if(current_ptr)
		{
		    i++;
			queue_push1(current_ptr, &queue);
            current_ptr = current_ptr->sib;
			while(current_ptr)
			{
						    // printf("-%d ",current_ptr->dv);

				queue_push1(current_ptr, &queue);
				current_ptr = current_ptr->sib;

			}
		}
	}
	return ptr;
}
void queue_push1(struct NTree *newptr, struct llist **h)
{

	if ((*h) == NULL)
	{
		(*h) = (struct llist *)malloc(sizeof(struct llist));
		(*h)->node = newptr;
		(*h)->next=NULL;
		return;
	}

	struct llist *tptr,*ptr;

	tptr=*h;

	while(tptr->next != NULL)
		tptr = tptr->next;

	ptr = (struct llist *)malloc(sizeof(struct llist));
	ptr->node = newptr;
	ptr->next = NULL;

	tptr->next = ptr;
	return;
}
void display_all_nodes_fll(struct llist *ptr)
{
	while(ptr!=NULL)
	{
		printf("%d->",ptr->node->dv);
		ptr=ptr->next;
	}
	printf("\n");
}



void check_all_nodes(struct llist *ptr){
	struct llist * temp_ptr=ptr;
	struct llist * temp_ptr1=temp_ptr;
temp_ptr=temp_ptr->next;
while(temp_ptr){
if(temp_ptr->node->dv==ptr->node->dv){printf("found\n");temp_ptr1->next==temp_ptr->next;}
temp_ptr1=temp_ptr;
temp_ptr=temp_ptr->next;

}

return;
 }
