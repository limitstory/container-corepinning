#include "linkedlist.h"

container *add_tail(container *head)
{
    container *temp = NULL, *list = NULL;
    temp = (container *)malloc(sizeof(container));
    if (temp == NULL)
    {
        printf("add_tail(): Out of Memory Space\n");
        return NULL;
    }

    temp->next = NULL;
    if (head == NULL)
        head = temp;
    else
    {
        list = head;
        while (list->next != NULL)
            list = list->next;
        list->next = temp;
    }
    return head;
}

void do_free(container *start)
{
    container *head = start;
    container *temp;
    while (head != NULL)
    {
        temp = head->next;
        free(head);
        head = temp;
        if (head == NULL)
        {
            //printf("(do_free): complete all list...\n");
            return;
        }
    }
}