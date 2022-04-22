#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Element Element;
struct Element {
    int number;
    Element*  next;
};


typedef struct Queue Queue;
struct Queue{
    Element* first;
};

Queue* initialise(){
    Queue* queue =(Queue*)malloc(sizeof(*queue));
    Element* element = (Element*)malloc(sizeof(*element));
    element = NULL;
    queue->first = element;
    return queue;
}


void EnQueue(Queue* queue, int number) {
    if(queue == NULL){
        return;
    }
    Element* newElement = (Element*)malloc(sizeof(*newElement));


    newElement->number = number;
    newElement->next = NULL;


    if(queue->first != NULL) {
       Element* currentElement = queue->first;
       while(currentElement->next != NULL) {
          currentElement = currentElement->next;
       }

       currentElement->next = newElement;
    }
    else{
        queue->first = newElement;
    }


}

void DeQueue(Queue* queue) {
    if(queue == NULL || queue->first == NULL) {
        return;
    }

    printf("DeQueue element is : %d \n", queue->first->number);
    queue->first=queue->first->next;
}

float Means(Queue* queue) {
    if(queue == NULL || queue->first == NULL) {
        printf("The queue is empty \n");
        return;
    }

    int count = 0;
    float sum =0;

    Element* element = (Element*)malloc(sizeof(*element));

    element = queue->first;

    while(element != NULL) {
            count++;
        sum += element->number;
         element = element->next;
    }


    return sum/count;

}

int lengthOfQueue(Queue* queue) {
    Element* element = (Element*)malloc(sizeof(*element));
    element = queue->first;
    int count = 0;
    while(element != NULL) {
            count++;
        element=element->next;
    }
    return count;
}

int QueueElements(Queue* queue) {
    Element* element = (Element*)malloc(sizeof(*element));
    element = queue->first;
    return element->number;
}


void PrintQueue(Queue* queue) {
    Element* element = (Element*)malloc(sizeof(*element));
    element = queue->first;
    printf("Queue's element are : ");
    while(element != NULL) {
        printf("%d ", element->number);
        element = element->next;
    }
    printf("\n");
}


/*Linked list*/



typedef struct Stack Stack;
struct Stack{
    Element* first;
};

Stack* initialiseStack(){
    Stack* stack =(Stack*)malloc(sizeof(*stack));
    Element* element = (Element*)malloc(sizeof(*element));
    element = NULL;
    stack->first = element;
    return stack;
}

void push(Stack* stack, int number) {

    Element* element = (Element*)malloc(sizeof(*element));
    element->number = number;
    element->next = stack->first;
    stack->first = element;
}


void pop(Stack* stack){
    if(stack == NULL || stack->first == NULL){
        printf("The stack is empty \n");
        return;
    }
    Element* element = (Element*)malloc(sizeof(*element));
    element = stack->first;
    stack->first = stack->first->next;
    printf("The deleled element is : %d \n", element->number);
    free(element);
}

int peak(Stack* stack){
    if(stack == NULL || stack->first == NULL) {
        printf("The stack is empty \n");
        return;
    }
    return stack->first->number;
}

int lengthOfStack(Stack* stack) {
    Element* element = (Element*)malloc(sizeof(*element));
    element = stack->first;
    int count = 0;
    while(element != NULL) {
            count++;
        element=element->next;
    }
    return count;
}


void PrintStack(Stack* stack) {
    if(stack == NULL || stack->first == NULL) {
        printf("The stack is empty \n");
        return;
    }
    Element* element = (Element*)malloc(sizeof(*element));
      element = stack->first;

      while( element!= NULL) {
        printf("%d ", element->number);
        element = element->next;
      }
      printf("\n");

}








int main()
{

    srand( time(NULL));
    int longer =0;
    do{
        longer = rand();
    }while(longer < 30);



    printf("%d \n", longer);

    FILE* file = NULL;
    file = fopen("test.txt", "w+");
    int number = 0;
    char* tab = (char*)malloc(sizeof(*tab)*longer);
    //char tab[15];

    int count = 0;

        if(file != NULL){

           for(int i = 0; i < longer; i++) {
                number = rand()%10;
                fprintf(file,"%d",number);
            }


            fclose(file);

        }

        file=fopen("test.txt","r");


        fgets(tab, longer+1, file);

        fclose(file);

        printf("%s \n", tab);

        fclose(file);
        for(int i = 0; i < longer; i++) {
            printf("%c ", tab[i]);
        }
        printf("\n");

    Queue* Queue = initialise();



    for(int i = 0; i < longer; i+=2) {
      if(i ==0){
        EnQueue(Queue, split(tab,longer,i));
      }
      else{
        EnQueue(Queue, split(tab,longer,i));
      }
    }

    PrintQueue(Queue);

    float mean = Means(Queue);

    printf("Mean : %f \n",mean);

    Stack* stack = initialiseStack();

    transByMean(Queue,stack);
    PrintStack(stack);
    peak(stack);
    pop(stack);
    PrintStack(stack);

    int leng=lengthOfStack(stack);
    int* dizi = (int*)malloc(sizeof(*dizi)*leng);
    for(int i=0; i <leng; i++){
        *(dizi+i) = peak(stack);
        pop(stack);
    }

    for(int i= 0; i < leng; i++) {
        printf("%d ",*(dizi+i));
    }
    printf("\n");
    PrintStack(stack);
    printf("\n");



   // free(tab);
    return 0;
}


 int split( char tab[], int sizeArray, int pos) {
     char splited[2] = "";
    for(int i = 0; i <2; i++ ){
        splited[i] += tab[pos+i];
    }

    if(splited[0] == '0') {
        splited[0] ='1';
    }
    else if(splited[1] == NULL){
        splited[1] ='0';
    }

    return atoi(splited);
 }

 void transByMean(Queue* queue, Stack* stack) {
    Element* element = (Element*)malloc(sizeof(*element));

    element = queue->first;
    float mean = Means(queue);
    while(element != NULL) {
        if(element->number < mean){
            push(stack,element->number);
        }
        element = element->next;
    }

 }


