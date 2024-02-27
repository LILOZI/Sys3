#include "StrList.h"


struct _Node {
    char* _str;
    struct _Node* _next;
};

struct _StrList {
    Node* _head;
    size_t _size;
};

StrList* StrList_alloc()
{
    StrList* p_list = (StrList*)malloc(sizeof(StrList));
    if(p_list != NULL)
    {
        p_list->_head = NULL;
        p_list->_size = 0;
    }
    return p_list;
}

void StrList_free(StrList* strList)
{
    if(strList != NULL)
    {
        Node* p_temp_node = strList->_head;
        Node* p_free_node;
        while(p_temp_node != NULL)
        {
            p_free_node = p_temp_node;
            p_temp_node = p_temp_node->_next;
            free(p_free_node);
        }
        strList->_size = 0;
        strList->_head = NULL;
    }
}

void free_node(Node* node)
{
    free(node);
}

size_t StrList_size(const StrList* strList)
{   
    if(strList != NULL)
    {
        return strList->_size;
    }
    return 0;
}

void StrList_insertLast(StrList* strList, const char* str)
{
    if(strList != NULL)
    {
        if(strList->_head == NULL)
        {
            strList->_head = create_node(str);
        }
        else
        {
            Node* p_node = strList->_head;
            while(p_node->_next != NULL)
            {
                p_node = p_node->_next;
            }
            Node* p_insert_node = create_node(str);
            if(p_insert_node != NULL)
            {
                p_node->_next = p_insert_node;
            }
        }
    }
}

void StrList_insertAt(StrList* strList, const char* data, int index)
{   
    if(strList != NULL)
    {
        Node* p_node = strList->_head;
        while(index >1)
        {
            index--;
            p_node = p_node->_next;
        }
        Node* p_next_node = p_node->_next;
        Node* p_insert_node = create_node(data);
        if(p_insert_node != NULL)
        {
            p_node->_next = p_insert_node;
            p_insert_node->_next = p_next_node;
        }
    }
}

char* StrList_firstData(const StrList* strList)
{
    if(strList != NULL)
    {
        return strList->_head->_str;
    }
    return NULL;
}

void StrList_print(const StrList* strList)
{  
    if(strList != NULL)
    {
        if(strList->_head != NULL)
        {
            Node* p = strList->_head;
            while(p->_next != NULL)
            {   
                printf("%s ",p->_str);
                p = p->_next;
            }
            printf("%s\n", p->_str);
        }
        else
        {
             printf("\n");
        }
    }
}

void StrList_printAt(const StrList* strList, int index)
{
    if(strList != NULL)
    {
        Node* p_node = strList->_head;
        while(index >0)
        {
            index--;
            p_node = p_node->_next;
        }
        printf("%s\n", p_node->_str);
    }
}

int StrList_printLen(const StrList* strList)
{
    int count = 0;
    if(strList != NULL)
    {
        Node* p_node = strList->_head;
        while(p_node != NULL)
        {
            count += strlen(p_node->_str);
            p_node = p_node->_next;
        }
    }
    return count;
}

int StrList_count(StrList* strList, const char* str)
{   
    int count = 0;
    if(strList != NULL)
    {
        Node* p_cur = strList->_head;
        while(p_cur != NULL)
        {
            if(strcmp(p_cur->_str, str) == 0)
            {
                count++;
            }
            p_cur = p_cur->_next;
        }
    }
    return count;
}

void StrList_remove(StrList* strList, const char* str)
{
    if(strList != NULL)
    {
        Node* p_cur = strList->_head;
        Node* p_prev = NULL;
        while(p_cur != NULL)
        {
            if(strcmp(p_cur->_str, str) == 0)
            {
                if(p_prev == NULL)
                {
                    strList->_head = p_cur->_next;
                    free_node(p_cur);
                    p_cur = strList->_head;
                    strList->_size--;
                    continue;
                }
                else
                {
                    p_prev->_next = p_cur->_next;
                    free_node(p_cur);
                    p_cur = p_prev->_next;
                    strList->_size--;
                    continue; 
                }
            }
            if(p_prev == NULL)
            {
                p_prev = p_cur;
            }
            else
            {
                p_prev = p_prev->_next;
            }
            p_cur = p_cur->_next;
        }
    }
}

void StrList_removeAt(StrList* strList, int index)
{
    if (index < 0 || index > strList->_size) 
    {
        return; 
    }
    if(strList != NULL)
    {
        if (index == 0)
        {
            Node *del = strList->_head;
            strList->_head = strList->_head->_next;
            free_node(del);
            strList->_size--;
            return;
        }

        Node *p = strList->_head;
        for (int i = 0; i < index - 1; i++)
        {
            p = p->_next;
        }
        Node *del = p->_next;
        p->_next = p->_next->_next;
        free_node(del);
        strList->_size--;
    }
}

int StrList_isEqual(const StrList* strList1, const StrList* strList2)
{
    if(strList1 != NULL && strList2 != NULL)
    {
        if(strList1->_size != strList2->_size)
        {
            return 0;
        }
        Node* p_l1 = strList1->_head;
        Node* p_l2 = strList2->_head;
        while(p_l1 != NULL)
        {
            if(strcmp(p_l1->_str, p_l2->_str) != 0)
            {
                return 0;
            }
            p_l1 = p_l1->_next;
            p_l2 = p_l2->_next;
        }
        return 1;
    }
    if(strList1 == NULL && strList2 == NULL)
    {
        return 1;
    }
    return 0;
        
}

StrList* StrList_clone(const StrList* strList)
{
    StrList* p_clone = StrList_alloc();
    p_clone->_size = strList->_size;
    p_clone->_head = dup_nodes(strList->_head);
    return p_clone;
}

void StrList_reverse(StrList* strList)
{
    if(strList != NULL)
    {   
        if(strList->_size == 1)
        {
            return;
        }
        Node* p_cur = strList->_head;
        Node* p_prev = NULL;
        Node* p_next = p_cur->_next;
        while(p_cur != NULL)
        {
            p_next = p_cur->_next;
            p_cur->_next = p_prev;
            p_prev = p_cur;
            p_cur = p_next;
        }
        strList->_head = p_prev;
    }
    return;
}

void StrList_sort(StrList* strList)
{
    if(strList != NULL)
    {
        int swaps = 0;
        Node* p_cur, *p_next, *p_prev;
        p_cur = strList->_head;
        p_next = p_cur->_next;
        p_prev = NULL;
        do
        {   
            p_cur = strList->_head;
            p_next = p_cur->_next;
            p_prev = NULL;
            swaps = 0;
            for(size_t i = 0; i<strList->_size-1; i++)
            {
                if(strcmp(p_cur->_str, p_next->_str) > 0)
                {
                    if(p_prev != NULL)
                    {
                        p_prev->_next = p_next;
                        p_cur->_next = p_next->_next;
                        p_next->_next = p_cur;

                        p_prev = p_next;
                    }
                    else
                    {
                        p_cur->_next = p_next->_next;
                        p_next->_next = p_cur; 
                        strList->_head = p_next;

                        p_prev = strList->_head;
                    }
                    p_next = p_cur->_next;
                    swaps++;
                    continue;
                }
                if(p_prev == NULL)
                {
                    p_prev = strList->_head;
                }
                else
                {
                    p_prev = p_cur;
                }
                p_cur = p_next;
                p_next = p_next->_next;
            }
        } 
        while (swaps > 0);
    }
}

int StrList_isSorted(StrList* strList)
{
    if(strList != NULL)
    {
        Node* p_cur = strList->_head;
        if(p_cur!= NULL)
        {
            Node* p_next = p_cur->_next;
            while(p_next != NULL)
            {
                if(strcmp(p_cur->_str, p_next->_str) > 0)
                {
                    return 0;
                }
                p_cur = p_next;
                p_next = p_next->_next;
            }
        }
    }
    return 1;
}

Node* create_node(const char *str)
{
    Node* p_node = (Node*)malloc(sizeof(Node));
    if(p_node != NULL)
    {
        p_node->_next = NULL;
        p_node->_str = strdup(str); 
    }
    return p_node;
}

Node* dup_nodes(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    Node* p_dup = create_node(node->_str);
    p_dup->_next = dup_nodes(node->_next);
    return p_dup;
}

void initList(StrList* strList, size_t length, char* str)
{   if(strList != NULL)
    {
        strList->_size = length;
        char* node_data = strtok(str, " ");
        strList->_head = create_node(node_data);
        if(strList->_head != NULL)
        {
            Node* p_cur_node = (strList->_head);
            node_data = strtok(NULL, " ");
            while(node_data != NULL)
            {   
                Node* p_temp_node = create_node(node_data);
                if(p_temp_node != NULL)
                {
                    p_cur_node->_next = p_temp_node;
                    p_cur_node = p_cur_node->_next;
                    node_data = strtok(NULL, " ");
                }
            }
        }
    }
}