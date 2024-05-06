#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
why do you have to link the math library in C when using GCC
https://stackoverflow.com/questions/1033898/why-do-you-have-to-link-the-math-library-in-c

Ashim Dhakal

*/

struct list_node {
    char name[40];
    double grade;
    struct list_node * next;
};

typedef struct list_node Node;
Node * create_node(char * name, double grade);
Node * push_data(char * name, double grade, Node * list);
void print_list(Node * list);

 void delete_list(Node * list);
 int grade_stats(Node * list, double * mean, double * std); // question 2
Node * file_to_list(char * file_path); // question 3

// bonus questions
 double min_grade(Node * list);
 double max_grade(Node * list);
double apply(Node * list, double (*func)(Node *));

int main(void) {

    // test list functions
    Node * list = create_node("Tom", 93.5);
    list = push_data("Adam", 94.6, list);
    list = push_data("Ada", 99.9, list);
    list = push_data("Nick", 85.3, list);

    // normal list
    print_list(list);
    // empty list
    print_list(NULL);

    // question 2, test cases
    double mean = -1, std = -1;
    int count = grade_stats(list, &mean, &std);
    printf("number of students: %d\ngrade mean: %.3lf\ngrade std: %.4lf\n", count, mean, std);

    // question 1, test case
    delete_list(list);

    // question 3, test case
    // list is pointing to a memory block that is freed
    // assign new address to list pointer
    list = file_to_list("text.txt");
    print_list(list);

    // bonus, test cases
     printf("grade min: %.3lf\n", apply(list, min_grade));
     printf("grade max: %.3lf\n", apply(list, max_grade));

    // delete newly assigned memory blocks by file_to_list
    delete_list(list);

    printf("end of ashims program! please press any key to exit...\n");
    getchar();

    return 0;
}


Node * create_node(char * name, double grade) {
    Node * node = malloc(sizeof(*node));
    // abort if malloc failed
    assert(node != NULL);
    // abort if input name is longer than 39 non-terminating chars
    assert(strlen(name) <= 39);
    strncpy(node->name, name, 39);
    node->grade = grade;
    node->next = NULL;
    return node;
}

Node * push_data(char * name, double grade, Node * list) {
    Node * head = create_node(name, grade);
    head->next = list;
    return head;
}

void print_list(Node * list) {
    if (list == NULL) {
        printf("empty list\n");
        return;
    }
    while (list->next != NULL) {
        printf("(%s, %.3lf)->", list->name, list->grade);
        list = list->next;
    }
    printf("(%s, %.3lf)->NULL\n", list->name, list->grade);
}


//implement your code below

void delete_list(Node * list) {
    Node * tempListNode = list;
    Node * nextVal;
  
  if (tempListNode == NULL) {
    printf("invalid list\n");
  } else {
    while (tempListNode != NULL) {
        nextVal = tempListNode->next; 
        free(tempListNode); 
        tempListNode = nextVal; // goto the next node
    }
  }

}

int grade_stats(Node * list, double * mean, double * std) {

    int total_grades = 0;
    double grades_sum = 0.0, variance_sum = 0.0, calculated_mean;

    for (Node *current = list; current != NULL; current = current->next) {
        grades_sum += current->grade;
        total_grades++;
    }
    
    if (total_grades > 0) {
        calculated_mean = grades_sum / total_grades;
        *mean = calculated_mean; 
        
        for (Node *current = list; current != NULL; current = current->next) {
            double diff = current->grade - calculated_mean;
            variance_sum += diff * diff;
        }
        *std = sqrt(variance_sum / total_grades); 
    }
    
    return total_grades;
}


Node * file_to_list(char * file_path) {
    FILE *file = fopen(file_path, "r");
    Node *list = NULL;
    char name[40];
    double grade;

    while (fscanf(file, "%39s %lf", name, &grade) == 2) {
        list = push_data(name, grade, list);
    }

    fclose(file); 
    return list; 
}


double min_grade(Node * list) {
    double ourLowestValue = list->grade;
    // need to make sure it aint empty
    while (list != NULL) {
        if (list->grade < ourLowestValue) {
            ourLowestValue = list->grade;
        }

        list = list->next;
    }
    return ourLowestValue;
}

double max_grade(Node * list) {
    double ourHighestValue = list->grade;
    while (list != NULL) {
        if (list->grade > ourHighestValue) {
            ourHighestValue = list->grade;
        } 
        list = list->next;
    }
    return ourHighestValue;
}

double apply(Node * list, double (*func)(Node *)) {
    return func(list);
}

