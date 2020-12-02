#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../library/commonUtils/graph.h"

Edge** getEdgesArray(int numberOfStudents, int* notPassedStudents)
{
    int studentNumber = 0;
    int cheatNumber = 0;
    Edge** students = createEdgeArray(numberOfStudents);
    for (int i = 0; i < numberOfStudents; ++i) {
        scanf("%d %d", &studentNumber, &cheatNumber);
        if (cheatNumber != -1) {
            students[i] = createEdge(studentNumber, cheatNumber, 1, true);
        } else {
            notPassedStudents[studentNumber] = -1;
        }
    }
    return students;
}

void printInfoAboutStudents(Graph* graphOfStudents, int quantityOfStudents, int* notPassedStudents)
{
    for (int i = 0; i < quantityOfStudents; ++i) {
        int numberOfStudent = i + 1;
        if (notPassedStudents[numberOfStudent] == -1) {
            printf("number of student - %d : didn't pass anything\n", numberOfStudent);
            continue;
        }
        int originalAuthor = getOriginalAuthor(graphOfStudents, i + 1);
        if (numberOfStudent == originalAuthor) {
            printf("number of student - %d : doesn't cheat\n", numberOfStudent);
        }
        if (numberOfStudent != originalAuthor && originalAuthor != 0) {
            printf("number of student - %d : number of student from who cheated - %d\n", numberOfStudent, originalAuthor);
        }
    }
}

int main()
{
    int quantityOfStudents = 0;
    printf("write number of students:\n");
    scanf("%d", &quantityOfStudents);

    int* notPassedStudents = calloc(quantityOfStudents + 1, sizeof(int));

    printf("write pairs throw a space, first is student number, second - number of student from who was cheated work\n"
           "for student 1, 2, 3 write 1 1, 2 2, 3 3, because they doesn't cheat\nif student doesn't write anything write -1 second\n");
    Edge** edgesArray = getEdgesArray(quantityOfStudents, notPassedStudents);
    Graph* graphOfStudents = createGraph(quantityOfStudents, quantityOfStudents + 1, edgesArray);

    printInfoAboutStudents(graphOfStudents, quantityOfStudents, notPassedStudents);

    removeGraph(graphOfStudents);
    removeEdgeArray(edgesArray, quantityOfStudents);
    free(notPassedStudents);

    return 0;
}
