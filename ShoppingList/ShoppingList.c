#define _CRT_SECURE_NO_WARNINGS
#include"ShoppingList.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define CLEAR while(getchar()!='\n'))
void addItem(struct ShoppingList *list)
{
    int flag;
    float amount;
    do{
        int i=(*list).length;
        if((*list).length == 0){
            (*list).itemList = dynMemory(1);
        }
        else{
            recallMem(&list->itemList, (*list).length +1);
        }
            
        if((*list).itemList != NULL){
            printf("Name of grocery item: ");
            while(getchar()!='\n');
            scanf("%[^\n]s", (*list).itemList[i].productName); //%[^\n]s = Läser in tills enterslag
            
            do{
                printf("How many?: ");
                scanf("%f",&amount);
                if(amount >0)
                    (*list).itemList[i].amount = amount;
                else
                    printf("Enter a positiv number!\n");
            }while(amount < 0);
            
            printf("What unit?(kg,lb etc..): ");
            scanf("%s",(*list).itemList[i].unit);
            (*list).length++;
            
        }
        
        printf("Add more items?\n");
        YesOrNo(&flag);
    }while(flag==0);
}




void printList(struct ShoppingList *list)
{
    int i;
    if((*list).length==0)
        printf("List is empty!\n");
    else{
        for(i=0; i<(*list).length; i++){
            printf("%d. %-20s %.2f %s\n",i+1,(*list).itemList[i].productName,(*list).itemList[i].amount, (*list).itemList[i].unit);
        }
    }
}

void editItem(struct ShoppingList *list)
{
    int ItemToChange,flag=0,flag2;
    float newValue;
    do{
    printf("What item do you want to edit?");
    scanf("%d",&ItemToChange);
    
        while(ItemToChange > 0 && ItemToChange <= (*list).length)
        {
                printf("Is this the item you want to change?\n%d. %-10s %.2f %2s\n",ItemToChange,(*list).itemList[ItemToChange-1].productName,(*list).itemList[ItemToChange-1].amount, (*list).itemList[ItemToChange-1].unit);
                YesOrNo(&flag);
            if(flag==1)
                break;
            do{
                printf("Ok, enter new Amount: ");
                scanf("%f",&newValue);
                (*list).itemList[ItemToChange-1].amount = newValue;
                  
            if(newValue>0){
                (*list).itemList[ItemToChange-1].amount = newValue;
                printf("New amount has ben set to %.2f of the item %d\n",(*list).itemList[ItemToChange-1].amount, ItemToChange);
                }
            else
            printf("You need to enter a positiv value\n");
            
            }while(newValue<0);
        break;
        }
        if(ItemToChange > (*list).length){
        printf("Item dose not exist, try again?\n");
        }
        printf("Want to try again?\n");
        YesOrNo(&flag2);
    }while(flag2==0);
}

void removeItem(struct ShoppingList *list)
{
    int removeItem, flag,i;
    do{
        printf("What item do you want to remove?");
        scanf("%d",&removeItem);
        
        if(removeItem <= (*list).length && removeItem >0)
        {
            printf("Is this the item you want to remover? %s\n",(*list).itemList[removeItem-1].productName);
            YesOrNo(&flag);
        }
        else{
            printf("Item donsn't exist!\n");
            flag=1;
        }
    }while(flag==1);
    
    (*list).length--;
   
    if((*list).length==0) // Om listans lägnd är 0 så frigörs minnet
        free((*list).itemList);

    if((removeItem-1)!=(*list).length)
    {
        for(i=removeItem-1; i<(*list).length; i++){
            strcpy((*list).itemList[i].productName,(*list).itemList[i+1].productName);
            (*list).itemList[i].amount = (*list).itemList[i+1].amount;
            strcpy((*list).itemList[i].unit,(*list).itemList[i+1].unit);
        }
    }
}

void saveList(struct ShoppingList *list)
{
    if((*list).length ==0)
        printf("List is empty can't save!\n");
    else{
        printf("Enter file name: ");
        char fileName[SIZE];
        scanf("%s",fileName);
        
        FILE *fp =fopen(fileName,"w");
        if(fp==NULL)
            printf("ERROR, cant open file.\n");
        else{
            fprintf(fp, "%d\n", (*list).length);
            for(int i=0; i< (*list).length; i++){
                fprintf(fp, "%s\n",  (*list).itemList[i].productName);
                fprintf(fp, "%f\n",  (*list).itemList[i].amount);
                fprintf(fp, "%s\n",  (*list).itemList[i].unit);
            }
            fclose(fp);
            printf("File is saved as: %s\n",fileName);
        }
    }
}

void loadList(struct ShoppingList* list)
{
    printf("Enter name you want to load: ");
    char fileName[SIZE];
    scanf("%s",fileName);
    
    FILE *fp = fopen(fileName, "r");
    
    if(fp==NULL)
        printf("ERROR cant open file");
    else{
        free((*list).itemList);
        fscanf(fp,"%d\n", &list->length);
        (*list).itemList = dynMemory((*list).length);
        
        for(int i=0; i<(*list).length; i++) {
            fscanf(fp,"%s\n", (*list).itemList[i].productName);
            fscanf(fp, "%f\n", &(*list).itemList[i].amount);
            fscanf(fp,"%s\n", (*list).itemList[i].unit);
        }
        printf("File loaded : %s\n",fileName);
        fclose(fp);
    }
}

struct GroceryItem* dynMemory(int size) //Returnerar pekaren till GroceryItem med return.
{
    struct GroceryItem *temp;
    temp = (struct GroceryItem*)calloc(sizeof(struct GroceryItem), size);
    if(temp!=NULL)
        return temp;
    else{
        printf("ERROR allocating memory");
        return NULL;
    }
}

void recallMem(struct GroceryItem **oldMem, int newMem) //Returnerar med hjälp av dubbelpekare, skickar in adressen till GroceryItem.
{
    
    struct GroceryItem *temp = (struct GroceryItem*)realloc(*oldMem, sizeof(struct GroceryItem) * newMem);
    if(temp != NULL)
    {
        *oldMem = temp;
    }
    else
        printf("ERROR reallocation of memory FAIL");
}

void YesOrNo(int *flag)
{
    int flag1;
    printf("1 for no 0 for yes!: ");
    scanf("%d",&flag1);
    *flag = flag1;
}

