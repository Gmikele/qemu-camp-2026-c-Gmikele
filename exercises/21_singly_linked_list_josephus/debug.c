#include <stdio.h>
#include <stdlib.h>

// 简单单链表实现
struct node {
    int item;
    struct node *next;
};

typedef struct node *link;

link head = NULL;

link make_node(int item) {
    link p = malloc(sizeof(*p));
    if (p) {
        p->item = item;
        p->next = NULL;
    }
    return p;
}

void push(link p) {
    p->next = head;
    head = p;
}

void delete(link p) {
    if (head == NULL || p == NULL) return;
    
    if (head == p) {
        head = p->next;
        free(p);
        return;
    }
    
    for (link q = head; q != NULL; q = q->next) {
        if (q->next == p) {
            q->next = p->next;
            free(p);
            return;
        }
    }
}

void free_node(link p) { free(p); }

void traverse(void (*visit)(link)) {
    for (link p = head; p != NULL; p = p->next) {
        visit(p);
    }
}

void destroy() {
    link p = head;
    while (p != NULL) {
        link next = p->next;
        free(p);
        p = next;
    }
    head = NULL;
}

// 获取头节点
static link g_first_node = NULL;
static void capture_first(link p) {
    if (g_first_node == NULL) {
        g_first_node = p;
    }
}

static link get_head_node(void) {
    g_first_node = NULL;
    traverse(capture_first);
    return g_first_node;
}

// 获取下一个节点；若到达尾部则回绕到头结点
static inline link next_wrap(link p) {
    if (p == NULL) return get_head_node();
    return p->next ? p->next : get_head_node();
}

void print_item(link p) { printf("%d ", p->item); }

void create_list(int n) {
    if (n <= 0) return;
    destroy();
    for (int i = n; i >= 1; i--) {
        link new_node = make_node(i);
        push(new_node);
    }
}

// 测试next_wrap
void test_next_wrap() {
    printf("Testing next_wrap with list of 5 nodes:\n");
    create_list(5);
    
    link current = get_head_node();
    printf("Head node item: %d\n", current->item);
    
    for (int i = 0; i < 10; i++) {
        printf("Current item: %d\n", current->item);
        current = next_wrap(current);
    }
}

int main() {
    test_next_wrap();
    return 0;
}