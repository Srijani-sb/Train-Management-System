#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DB_SIZE 100
#define NAME_SIZE 20
#define CLASS_LEN 20
#define STATUS_LEN 20
#define SIZE 10
#define M 5
typedef enum{FAILURE,SUCCESS} status_code;
typedef enum{FALSE,TRUE} boolean;

typedef struct passenger{
	char name[20];
    int passengerID; 
    char train_name[20];
    char boarding_station[20];
    char travelling_class[10];
    char destination_station[20];
    int train_no;
    int seat_no;
    int date;//ddmmyy
    
    struct passenger *left;
    struct passenger *right;
   int key;
    
}passenger;
typedef struct Treenode{
	int count,data;
	passenger val[M-1];
	struct Treenode *np[M];
}treenode;

typedef struct trainDb{
	char name[20];
    int passengerID;
    char destination_station[20];
	treenode *root;
	treenode *sroot;
	treenode *root3;
	treenode *root2;
	treenode *root1;
	
	passenger lptr;
	int train_no;
	int no_of_passengers;
	
	struct trainDb *left;
    struct trainDb *right;
}train_DB;
struct node{
    struct passenger record;
    struct node *next;
};
int srNo,yesFlag;

void intialize(train_DB *flp){
	flp->root=NULL;
	flp->sroot=NULL;
	flp->root3=NULL;
	flp->root2=NULL;
	flp->root1=NULL;
}
treenode *maketree(char name[],int p_id,char b_n[],char b_s[],char class[],char d_s[],int t_id,int key){
	int i;
	treenode *nptr;
	nptr=(treenode *)malloc(sizeof(treenode));
	if(nptr!=NULL){
		nptr->count=1;
		strcpy(nptr->val[0].name,name);
		nptr->val[0].passengerID=p_id;
		strcpy(nptr->val[0].train_name,b_n);
		strcpy(nptr->val[0].boarding_station,b_s);
		strcpy(nptr->val[0].travelling_class,class);
		strcpy(nptr->val[0].destination_station,d_s);
		nptr->val[0].train_no=t_id;
		nptr->val[0].key=key;
		for(i=0;i<M;i++){
			nptr->np[i]=NULL;
		}

	}
	return nptr;
}
passenger *makeDataNode(char name[],int p_id,char b_n[],char b_s[],char class[],char d_s[],int t_id,int key){
	int i;
	passenger *nptr;
	nptr=(passenger *)malloc(sizeof(passenger));
	if(nptr!=NULL){
		strcpy(nptr->name,name);
		nptr->passengerID=p_id;
		strcpy(nptr->train_name,b_n);
		strcpy(nptr->boarding_station,b_s);
		strcpy(nptr->travelling_class,class);
		strcpy(nptr->destination_station,d_s);
		nptr->train_no=t_id;
		nptr->key=key;
	}
	return nptr;
}
void freetree(treenode *root){
	if(root != NULL)
	{
		int i;
		for(i=0; i<root->count; i++)
		{
			if(i==0)
				freetree(root->np[i]);
			freetree(root->np[i+1]);
		}
		free(root);
		root = NULL;
	}
}
treenode *selectRoot(train_DB *flp, int select_flag)
{

	treenode *root;
	switch (select_flag)
	{
		case 0: root = flp->root;
				break;
		case 1: root = flp->sroot;
				break;
		case 2: root = flp->root3;
				break;
		case 3: root = flp->root2;
				break;
		case 4: root=flp->root1;
				break;
		default : root = flp->root;
				break;
	}
	return root;
}

void updateRoot (train_DB *flp, treenode *root, int select_flag)
{
	switch (select_flag)
	{
		case 0: flp->root = root;
				break;
		case 1: flp->sroot = root;
				break;
		case 2: flp->root3 = root;
				break;
		case 3: flp->root2 = root;
				break;
		case 4: flp->root1 = root;
				break;
		default : flp->root = root;
				break;
	}
}
void freeDB (train_DB *flp)
{
	treenode *root;
	int i=0;
	for(i=0; i<4; i++)
	{
		root = selectRoot(flp, i); // deleting all lists of a database
		if(root != NULL)
		{
			freetree(root);
		}
		updateRoot(flp, root, i);
	}
}
void visit (treenode *nptr, int index)
{
	printf("\t\t%s\t\t%d\t\t%s\t", nptr->val[index].name, nptr->val[index].passengerID, nptr->val[index].train_name);
	printf("\t\t%s\t\t%s\t%s\t\t%d\t", nptr->val[index].boarding_station,nptr->val[index].travelling_class ,nptr->val[index].destination_station, nptr->val[index].train_no);
	printf("\n");
}
void traverse (treenode *root)
{
	if(root != NULL)
	{
		int i;
		for(i=0; i<root->count; i++)
		{
			if(i==0)
				traverse(root->np[i]);
			printf("\n%d", srNo);
			srNo++;
			visit(root, i);
			traverse(root->np[i+1]);
		}
	}
}
void printRec (train_DB *flp, int select_flag)
{
	treenode *root;
	root = selectRoot(flp,select_flag);
	if(root == NULL)
	{
		printf("\nList is empty.\n\n");
	}
	else
	{
		printf("SERIAL NO.\tname\tID\tBoarding train\tboarding station\tCLASS\tDEstination station\tTrain NO");
		srNo = 1;
		traverse(root);
	}
	updateRoot(flp, root, select_flag);
}
int computeKey (passenger *id)
{
	int key;
	key =id->passengerID;
	return key;
}
void copyData (passenger *destination, passenger *source)
{
	// to copy data
	strcpy(destination->name, source->name);
	destination->passengerID = source->passengerID;
	strcpy(destination->train_name,source->train_name);
	strcpy(destination->boarding_station,source->boarding_station);
	
	strcpy(destination->travelling_class, source->travelling_class);
	strcpy(destination->destination_station, source->destination_station);

	destination->train_no = source->train_no;
	destination->key = source->key;
}

void pushIn (passenger *data, treenode *ptr, treenode *rightSub, int k)
{ // ptr is present node
	int j;
	for(j=ptr->count; j>k; j--)
	{
		copyData(&(ptr->val[j]), &(ptr->val[j-1]));
		ptr->np[j+1] = ptr->np[j];
	}
	copyData(&(ptr->val[k]), data);
	ptr->np[k+1] = rightSub;
	ptr->count++;
}


void split (passenger *data, treenode *ptr, treenode *newNp, int k, passenger *median, treenode **rightSub)
{ // ptr is present node
	// k is position
	int i, mid = M/2;
	*rightSub = (treenode*) malloc(sizeof(treenode));
	if(k <= mid)
	{
		for(i = mid; i < M-1; i++)
		{
			copyData(&((*rightSub)->val[i-mid]), &(ptr->val[i]));
			(*rightSub)->np[i+1-mid] = ptr->np[i+1];
		}
		ptr->count = mid;
		(*rightSub)->count = (M-1) - mid;
		pushIn(data, ptr, newNp, k);
	}
	else
	{
		mid++;
		for(i = mid; i < M-1; i++)
		{
			copyData(&((*rightSub)->val[i-mid]), &(ptr->val[i]));
			(*rightSub)->np[i+1-mid] = ptr->np[i+1];
		}
		ptr->count = mid;
		(*rightSub)->count = (M-1) - mid;
		pushIn(data, *rightSub, newNp, k-mid);
	}
	copyData(median, &(ptr->val[ptr->count - 1]));
	(*rightSub)->np[0] = ptr->np[ptr->count];
	ptr->count--;
}
boolean comparator(passenger *aptr,passenger *bptr,int compare_flag){
	boolean ret_val=TRUE;
	while(compare_flag){
		if(aptr->passengerID>bptr->passengerID){
			ret_val=FALSE;
		}
		else if(aptr->passengerID==bptr->passengerID){
			if(comparator(aptr,bptr,1)==FALSE){
				ret_val=FALSE;
			}
		}
	}
	return ret_val;
}
status_code pushDown (passenger* data, treenode *root, passenger *median, treenode **rightSub, int compare_flag)
{
	status_code sc = SUCCESS;
	int k = 0; // position
	if(root == NULL)
	{
		copyData(median, data);
		*rightSub = NULL;
		sc = FAILURE;
	}
	else
	{
		// perform search
		int found = 0;
		while(k < root->count && comparator(&(root->val[k]), data, compare_flag) == TRUE)
		{
			k++;
		}
		if(compare_flag == 0 && k < root->count && root->val[k].key == data->key) // for key case
		{
			found = 1;
		} // else found = 0;


		if(found)
		{
			// update
			copyData(&(root->val[k]), data);
			// sc = SUCCESS;
		}
		else
		{
			passenger newData;
			treenode *newNp;
			sc = pushDown(data, root->np[k], &newData, &newNp, compare_flag);
			if(sc == FAILURE)
			{
				if(root->count < M-1)
				{
					pushIn(&newData, root, newNp, k);
					sc = SUCCESS;
				}
				else
				{
					split(&newData, root, newNp, k, median, rightSub);
					// sc = FAILURE;
				}
			}
		}
	}
	return sc;
}
status_code insertUpdate (train_DB *flp, char name[],int p_id,char b_n[],char b_s[],char class[],char d_s[],int t_id,int select_flag,int compare_flag){

	status_code sc = SUCCESS;
	int key;
	passenger median;
	treenode *root, *rightSub, *temp;
	root = selectRoot(flp, select_flag);
	if(getNum(flp, select_flag) == DB_SIZE)
	{
		sc = FAILURE;
	}
	else
	{
		key = p_id;
		passenger *data = makeDataNode(name,p_id,b_n,b_s,class,d_s,t_id,key);
		sc = pushDown(data, root, &median, &rightSub, compare_flag);
		if(sc == FAILURE)
		{
			key = p_id;
			temp=  maketree(name,p_id,b_n,b_s,class,d_s,t_id,key);
			copyData(&(temp->val[0]), &median);
			temp->np[0] = root;
			temp->np[1] = rightSub;
			root = temp;
			sc = SUCCESS;
		}
	}
	updateRoot(flp, root, select_flag);
	return sc;
}
void copyInPredecessor (treenode *ptr, int index)
{ // ptr is present node
	treenode *leafNode = ptr->np[index];
	while(leafNode->np[leafNode->count] != NULL)
	{
		leafNode = leafNode->np[leafNode->count];
	}
	copyData(&(ptr->val[index]), &(leafNode->val[leafNode->count - 1]));
}
void removeData (treenode *ptr, int index)
{ // ptr is present node
	int i;
	for(i = index; i < ptr->count - 1; i++)
	{
		copyData(&(ptr->val[i]), &(ptr->val[i+1]));
	}
	ptr->count--;
}
void moveRight (treenode *ptr, int index)
{ // ptr is present node
	treenode *rightSub = ptr->np[index+1];
	treenode *leftSub = ptr->np[index];
	rightSub->np[rightSub->count + 1] = rightSub->np[rightSub->count];
	int i;
	for(i = rightSub->count; i>0; i--)
	{
		copyData(&(rightSub->val[i]), &(rightSub->val[i-1]));
		rightSub->np[i] = rightSub->np[i-1];
	}
	rightSub->count++;
	copyData(&(rightSub->val[0]), &(ptr->val[index]));
	rightSub->np[0] = leftSub->np[leftSub->count];
	leftSub->count--;
	copyData(&(ptr->val[index]), &(leftSub->val[leftSub->count]));
}
void combine (treenode *ptr, int index)
{ // ptr is present node
	int i;
	treenode *leftSub = ptr->np[index-1];
	treenode *rightSub = ptr->np[index];
	copyData(&(leftSub->val[leftSub->count]), &(ptr->val[index-1]));
	leftSub->count++;
	leftSub->np[leftSub->count] = rightSub->np[0];
	for(i=0; i < rightSub->count; i++)
	{
		copyData(&(leftSub->val[leftSub->count]), &(rightSub->val[i]));
		leftSub->count++;
		leftSub->np[leftSub->count] = rightSub->np[i+1];
	}
	ptr->count--;
	for(i = index - 1; i < ptr->count; i++)
	{
		copyData(&(ptr->val[i]), &(ptr->val[i+1]));
		ptr->np[i+1] = ptr->np[i+2];
	}
	free(rightSub);
}
void moveLeft (treenode *ptr, int index)
{ // ptr is present node
	treenode *leftSub = ptr->np[index-1];
	treenode *rightSub = ptr->np[index];
	copyData(&(leftSub->val[leftSub->count]), &(ptr->val[index-1]));
	leftSub->count++;
	leftSub->np[leftSub->count] = rightSub->np[0];
	copyData(&(ptr->val[index-1]), &(rightSub->val[0]));
	rightSub->count--;
	int i;
	for(i=0; i<rightSub->count; i++)
	{
		copyData(&(rightSub->val[i]), &(rightSub->val[i+1]));
		rightSub->np[i] = rightSub->np[i+1];
	}
	rightSub->np[rightSub->count] = rightSub->np[rightSub->count + 1];
}
void restore (treenode *ptr, int index)
{ // ptr is present node
	if(index == ptr->count)
	{
		if(ptr->np[index - 1]->count > (M-1)/2)
		{
			moveRight(ptr, index-1);
		}
		else
		{
			combine(ptr, index);
		}
	}
	else if(index == 0)
	{
		if(ptr->np[1]->count > (M-1)/2)
		{
			moveLeft(ptr, 1);
		}
		else
		{
			combine(ptr, 1);
		}
	}
	else
	{
		if(ptr->np[index - 1]->count > (M-1)/2)
		{
			moveRight(ptr, index-1);
		}
		else if(ptr->np[index + 1]->count > (M-1)/2)
		{
			moveLeft(ptr, index+1);
		}
		else
		{
			combine(ptr, index);
		}
	}
}

boolean isEmpty (train_DB *flp)
{
	boolean ret_val = TRUE;
	if( flp->root != NULL ) {
		ret_val = FALSE;
	}
	return ret_val;
}
boolean isFull (train_DB *flp)
{
	boolean ret_val = FALSE;
	if(getNum(flp, 0) == DB_SIZE)
		ret_val = TRUE;
	return ret_val;
}
boolean isKeyEqual (passenger *aptr, passenger *bptr)
{
	boolean ret_val = FALSE;
	if(aptr->passengerID == bptr->passengerID && aptr->date == bptr->date)
		ret_val = TRUE;
	return ret_val;
}

boolean isNewKeyEqual (passenger *aptr, passenger *bptr)
{
	// for listUnique
	boolean retVal = FALSE;
	if(strcmp(aptr->name, bptr->name) == 0 && aptr->passengerID == bptr->passengerID)
		retVal = TRUE;
	return retVal;
}
status_code recursiveDeleteByKey (treenode *ptr, int key)
{ // ptr is present node
	status_code sc;
	int k=0; // position
	if(ptr == NULL)
	{
		sc = FAILURE;
	}
	else
	{
		// perform search
		int found = 0;
		k=0;
		while(k < ptr->count && ptr->val[k].key < key)
		{
			k++;
		}
		if(k < ptr->count && ptr->val[k].key == key)
		{
			found = 1;
		} // else found = 0;

		if(found)
		{
			sc = SUCCESS;
			if(ptr->np[k] != NULL)
			{
				copyInPredecessor(ptr, k);
				recursiveDeleteByKey(ptr->np[k], ptr->val[k].key);
			}
			else
			{
				removeData(ptr, k);
			}
		}
		else
		{
			sc = recursiveDeleteByKey(ptr->np[k], key);
		}
		if(ptr->np[k] != NULL && ptr->np[k]->count < (M-1)/2)
		{
			restore(ptr, k);
		}
	}
	return sc;
}

status_code deleteByKey (train_DB *flp,int key, int select_flag)
{
	treenode *root = selectRoot(flp, select_flag);
	int successFlag = 0;
	status_code sc = SUCCESS, scc;
	while(sc == SUCCESS)
	{
		scc = recursiveDeleteByKey(root, key);
		if(scc == SUCCESS)
		{
			successFlag = 1;
		}
		sc = scc;
		if(root != NULL && root->count == 0) // empty root
		{
			treenode *temp = root;
			root = root->np[0];
			free(temp);
		}
	}
	updateRoot(flp, root, select_flag);
	if(successFlag == 0)
	{
		sc = FAILURE;
	}
	else
	{
		sc = SUCCESS;
	}
	return sc;
}
status_code insertUpdateSubTree (train_DB *flp, char name[],int p_id,char b_n[],char b_s[],char class[],char d_s[],int t_id){
	status_code sc=SUCCESS;
	int key=p_id;
	if(strcmp(class,"Sleeper")==0){
		sc=insertUpdate(flp,name,p_id,b_n,b_s,class,d_s,t_id,1,0);
		deleteByKey(flp, key, 2);
		deleteByKey(flp, key, 3);
		deleteByKey(flp, key, 4);
	}
	else if(strcmp(class, "3AC") == 0)
	{
		sc=insertUpdate(flp,name,p_id,b_n,b_s,class,d_s,t_id,2,0);
		deleteByKey(flp, key, 1);
		deleteByKey(flp, key, 3);
		deleteByKey(flp, key, 4);

	}
	else if(strcmp(class, "2AC") == 0)
	{
		sc=insertUpdate(flp,name,p_id,b_n,b_s,class,d_s,t_id,3,0);
		deleteByKey(flp, key, 1);
		deleteByKey(flp, key, 2);
		deleteByKey(flp, key, 4);
	}
	else if(strcmp(class, "1AC") == 0)
	{
		sc=insertUpdate(flp,name,p_id,b_n,b_s,class,d_s,t_id,4,0);
		deleteByKey(flp, key, 1);
		deleteByKey(flp, key, 2);
		deleteByKey(flp, key, 3);
	}
	else
	{
		sc = FAILURE;
	}
	return sc;
}

int recursiveGetNum(treenode *root)
{
	int retVal = 0;
	if(root != NULL)
	{
		int i;
		for(i=0; i<root->count; i++)
		{
			if(i==0)
				retVal += recursiveGetNum(root->np[i]);
			retVal++;
			retVal += recursiveGetNum(root->np[i+1]);
		}
	}
	return retVal;
}
int getNum(train_DB *flp, int count_flag)
{
	treenode *root;
	int retVal = 0;
	root = selectRoot(flp, count_flag);
	if(root != NULL)
	{
		retVal = recursiveGetNum(root);
	}
	updateRoot(flp, root, count_flag);
	return retVal;
}


void getListDestination(struct node *head)
{
    int train_no;
    char destination_station[20];
    struct node *ptr=head;
    printf("Enter the train ID and destination station you want to get the list for:\n");
    scanf("%d %s",&train_no,destination_station);
    
    while(ptr!=NULL && ptr->record.train_no != train_no)
    {
        ptr=ptr->next;
    }
    if(ptr==NULL)
    {
        printf("No such list found!!\n");
    }
    else
    {
        printf("\nThe list is : \n");
        while(ptr->record.train_no == train_no)
        {
            if(strcmp(ptr->record.destination_station,destination_station)==0)
            {
                printf("%s\t%d\n",ptr->record.name,ptr->record.passengerID);
            }
            ptr=ptr->next;
        }   
    }
}
status_code recursiveDelete (treenode *ptr, unsigned int id)
{ // ptr is present node
	status_code sc;
	int k=0; // position
	if(ptr == NULL)
	{
		sc = FAILURE;
	}
	else
	{
		// perform search
		int found = 0;
		k=0;
		while(k < ptr->count && ptr->val[k].passengerID < id)
		{
			k++;
		}
		if(k < ptr->count && ptr->val[k].passengerID == id)
		{
			found = 1;
		} // else found = 0;

		if(found)
		{
			sc = SUCCESS;
			if(ptr->np[k] != NULL)
			{
				copyInPredecessor(ptr, k);
				recursiveDelete(ptr->np[k], ptr->val[k].passengerID);
			}
			else
			{
				removeData(ptr, k);
			}
		}
		else
		{
			sc = recursiveDelete(ptr->np[k], id);
		}
		if(ptr->np[k] != NULL && ptr->np[k]->count < (M-1)/2)
		{
			restore(ptr, k);
		}
	}
	return sc;
}

status_code deleteTree (train_DB *flp, int p_id, int select_flag)
{
	treenode *root = selectRoot(flp, select_flag);
	int successFlag = 0;
	status_code sc = SUCCESS, scc;
	while(sc == SUCCESS)
	{
		scc = recursiveDelete(root, p_id);
		if(scc == SUCCESS)
		{
			successFlag = 1;
		}
		sc = scc;
		if(root != NULL && root->count == 0) // empty root
		{
			treenode *temp = root;
			root = root->np[0];
			free(temp);
		}
	}
	updateRoot(flp, root, select_flag);
	if(successFlag == 0)
	{
		sc = FAILURE;
	}
	else
	{
		sc = SUCCESS;
	}
	return sc;
}
status_code deleteSubTree (train_DB *flp, int p_id)
{
	status_code sc = SUCCESS;
	sc = deleteTree(flp, p_id, 1);
	sc = deleteTree(flp, p_id, 2);
	sc = deleteTree(flp, p_id, 3);
	sc = deleteTree(flp, p_id, 4);
	return sc;
}
void insertIntoNewDB (train_DB *flp, treenode *root, int compare_flag)
{ // flp is new DB
	if(root != NULL)
	{
		int i;
		for(i=0; i<root->count; i++)
		{
			if(i==0)
				insertIntoNewDB(flp, root->np[i], compare_flag);
			status_code sc = insertUpdate(flp, root->val[i].name, root->val[i].passengerID, root->val[i].train_name, root->val[i].boarding_station, root->val[i].travelling_class, root->val[i].destination_station, root->val[i].train_no, 0, compare_flag);
			insertIntoNewDB(flp, root->np[i+1], compare_flag);
		}
	}
}
void getSorted(train_DB *flp, int p_id)
{
	treenode *root = flp->root;
	if(root != NULL)
	{
		train_DB newDB;
		train_DB *newDBptr = &newDB;
		intialize(newDBptr);
		insertIntoNewDB(newDBptr, root, p_id);
		printRec(newDBptr, 0);
		freeDB(newDBptr);
	}
}
void SortByTravelDate(train_DB *flp,int p_id){
	getSorted(flp,flp->lptr.passengerID);
	//printf("%s",flp->destination_station);
	return;
}
void SortTrains(struct node *lptr)
{
  struct node *ptr;
  ptr=lptr;
  
  if (ptr != NULL)
  {
    while (ptr != NULL)
    {

      printf("\nThe travel date of passengers with the train id %d is:%d", ptr->record.train_no, ptr->record.date);
    }
  }
}
void recursiveSearch (treenode *root, int start, int end)
{
	if(root != NULL)
	{
		int i;
		for(i=0; i<root->count; i++)
		{
			if(i==0)
				recursiveSearch(root->np[i], start, end);
			if(start < root->val[i].train_no)
			{
				if( ( root->val[i].train_no < end ) )
				{
					if(yesFlag == 0)
					{
						printf("\n\nSERIAL NO.\tNAME\tID\tCLASS\tTrain id");
						srNo = 1;
						yesFlag = 1;
					}
					printf("\n%d", srNo);
					srNo++;
					visit(root, i);
				}
			}
			recursiveSearch(root->np[i+1], start, end);
		}
	}
}

void searchtrain (train_DB *flp, int start, int end, int select_flag)
{
	treenode *root = selectRoot(flp, select_flag);
	if(root != NULL)
	{
		srNo = 1;
		recursiveSearch(root, start, end);
	}
	updateRoot(flp, root, select_flag);
}
void RangeSearch(treenode *node,int start,int end)
{
    int i;
    if(node)
    {
        for(i=0;i<node->count;i++)
        {
            RangeSearch(node->np[i],start,end);
            if(node->val[i].train_no>=start&&node->val[i].train_no<=end)
            {
                printf("%d",node->val[i]);
            }
        }
        RangeSearch(node->np[i],start,end);
    }
}
/*void printsearch(train_DB *root,int k1,int k2){
	if(NULL==root){
		return;
	}
	if(k1<root->train_no){
		printsearch(root->left,k1,k2);
	}
	if(k1<=root->train_no && k2>=root->train_no){
		     printf("%d ", root->train_no );

	}
	printsearch(root->right,k1,k2);
}*/

int main()
{
	train_DB my_fl, my_fl2, new_db;
	struct node *head=NULL;
	train_DB *my_ptr = &my_fl, *my2 = &my_fl2, *newp = &new_db;
	intialize(my_ptr);
	intialize(my2);
	intialize(newp);

	status_code sc=SUCCESS;
	int id=0,train_id=0;
	int i=0, j=0, not_failed=0, num_rec=0, select=12, flag=1, num=0;
	char name[20],train_name[20],boarding_station[20],travelling_class[10];
    char destination_station[20];
	treenode *nptr = NULL;
	int start,end=0;

	while(flag)
	{
		id=0,train_id=0;
		i=0, j=0, not_failed=0, num_rec=0, select=12, flag=1, num=0;
		start=0,end=0;
		name[0]='\0'; train_name[0]='\0'; boarding_station[0]='\0';travelling_class[0]='\0';
		destination_station[0]='\0';

		select=12;
		printf("Please enter appropriate number each time (until you want to exit : 0) for the corresponding operation");
		printf("\n0. EXIT\n1. insert\n2. delete\n3. getListDestination\n4.SortByTravelDate\n5.SortTrains\n6.RangeSearch\n7.Print List\n");
		scanf("%d", &select);
		printf("\n");
		switch (select)
		{
			case 0: { // Exit
						flag=0;
						printf("\nSUCCESS : Exited !!\n");
					}
					break;
			case 1: { // insertUpdate
						printf("\nEnter the number of records to insert : ");
						scanf("%d",&num_rec);
						printf("\n");
						for(i=0; i<num_rec; i++)
						{
							printf("Enter the passenger name ( without spaces ) : ");
							scanf("%s",name);

							printf("Enter the passenger id ( non zero ) : ");
							scanf("%d",&id);

							printf("Enter the boarding train ( without spaces ) : ");
							scanf("%s",train_name);
							
							printf("Enter the boarding station ( without spaces ) : ");
							scanf("%s",boarding_station);
							
							printf("Enter the travelling class ( without spaces ) : ");
							scanf("%s",travelling_class);

							printf("Enter the destination station ( without spaces ) : ");
							scanf("%s",destination_station);
							
							printf("Enter the train id ( non zero ) : ");
							scanf("%d",&train_id);


							if (insertUpdate(my_ptr, name, id, train_name, boarding_station, travelling_class, destination_station, train_id,0, 0) == SUCCESS)
							{
								printf("\nSUCCESS : List updated.\n\n");
								sc = insertUpdateSubTree(my_ptr, name, id, train_name, boarding_station, travelling_class, destination_station, train_id);
							}
							else
							{
								printf("\nFAILURE : There is no space.\n\n");
							}
						}
					}
					break;
			case 2: { // delete
						int del;
						printf("\nEnter the passenger id whose details are to be deleted : ");
						scanf("%d", &del);

						if (deleteTree(my_ptr, del, 0) == SUCCESS)
						{
							printf("\nReservation cancelled successfully\n\n");
							sc = deleteSubTree(my_ptr, del);
						}
						else
						{
							printf("\nReservation Cancellation failed.\n\n");
						}
					}
					break;
			case 3: { // getNumFlights
						num=getNum(my_ptr, 0);
						printf("\nSUCCESS: Number of passengers having the same destination station and same train id are %d.\n\n", num);
						
						getListDestination(head);
					}
					break;
			case 4:{
						printf("Enter id:");
						scanf("%d",&id);
						if(isEmpty(my_ptr) == TRUE)
						{
							printf("\nThe list is empty.\n\n");
						}
						else
						{
							printf("\nSUCCESS : \n\n");
							SortByTravelDate(my_ptr,id);
						}
				break;
			}
			case 5:{
				SortTrains(head);
				break;
			}
			case 6:{
				printf("Enter From-train-Number : ");
						scanf("%d",&start);
						printf("Enter To-Train-Number : ");
						scanf("%d",&end);

						printf("\n\nSleeper CLASS");
						yesFlag = 0;
						searchtrain(my_ptr, start, end,1);
						if(yesFlag == 0)
							printf("\n\nNo match.\n\n");

						printf("\n3AC CLASS");
						yesFlag = 0;
						searchtrain(my_ptr, start, end,2);
						if(yesFlag == 0)
							printf("\n\nNo match.\n\n");

						printf("\n2AC CLASS");
						yesFlag = 0;
						searchtrain(my_ptr, start, end,3);
						if(yesFlag == 0)
							printf("\n\nNo match.\n\n");
							
						printf("\n1AC CLASS");
						yesFlag = 0;
						searchtrain(my_ptr, start, end,4);
						if(yesFlag == 0)
							printf("\n\nNo match.\n\n");

						printf("\n\n");
				
				break;
			}
			case 7 :{
						printf("\n\nLIST OF RECORDS IS : \n\n");
						printRec(my_ptr, 0);
						printf("\n");
				
						break;
			}
			default:{
				flag=0;
				break;
			}
		}
	}
	freeDB(my_ptr);
	freeDB(my2);
	freeDB(newp);
	return 0;
}





