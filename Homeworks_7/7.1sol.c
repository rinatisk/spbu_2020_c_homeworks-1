#include <stdbool.h>
#include <stdio.h>

#include "../library/commonUtils/graph.h"

Edge** getEdgesArray(int numberOfStudents)
{
    int studentNumber = 0;
    int cheatNumber = 0;
    Edge** students = createEdgeArray(numberOfStudents);
    for (int i = 0; i < numberOfStudents; ++i) {
        scanf("%d %d", &studentNumber, &cheatNumber);
        students[i] = createEdge(studentNumber, cheatNumber, 1, true);
    }
    return students;
}

void printInfoAboutStudents(Graph* graphOfStudents, int quantityOfStudents)
{
    for (int i = 0; i < quantityOfStudents; ++i) {
        int numberOfStudent = i + 1;
        int originalAuthor = getOriginalAuthor(graphOfStudents, i + 1);
        if (numberOfStudent == originalAuthor) {
            printf("number of student - %d : doesn't cheat\n", numberOfStudent);
        }
        if (originalAuthor == 0) {
            printf("number of student - %d : didn't pass anything\n", numberOfStudent);
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

    Edge** edgesArray = getEdgesArray(quantityOfStudents);
    Graph* graphOfStudents = createGraph(quantityOfStudents, quantityOfStudents + 1, edgesArray);

    printInfoAboutStudents(graphOfStudents, quantityOfStudents);

    removeGraph(graphOfStudents);
    removeEdgeArray(edgesArray, quantityOfStudents);
    return 0;
}
