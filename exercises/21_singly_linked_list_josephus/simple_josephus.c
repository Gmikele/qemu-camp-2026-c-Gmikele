#include <stdio.h>
#include <stdlib.h>

// 简单的环形单链表节点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建环形单链表，包含n个节点，值为1到n
Node* create_circular_list(int n) {
    if (n <= 0) return NULL;
    
    Node* head = NULL;
    Node* tail = NULL;
    
    for (int i = 1; i <= n; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
            new_node->next = head; // 环形，指向自己
        } else {
            tail->next = new_node;
            new_node->next = head;
            tail = new_node;
        }
    }
    
    return head;
}

// 释放环形链表
void free_circular_list(Node* head) {
    if (head == NULL) return;
    
    Node* current = head;
    Node* temp;
    
    do {
        temp = current->next;
        free(current);
        current = temp;
    } while (current != head);
}

// 约瑟夫环问题
void josephus(int n, int k, int m) {
    if (n <= 0 || k <= 0 || m <= 0) {
        printf("参数错误：n, k, m 都必须大于 0\n");
        return;
    }
    
    Node* head = create_circular_list(n);
    if (head == NULL) {
        printf("创建链表失败\n");
        return;
    }
    
    // 找到第k个位置作为起点
    Node* current = head;
    for (int i = 1; i < k; i++) {
        current = current->next;
    }
    
    printf("约瑟夫环(n=%d, k=%d, m=%d): ", n, k, m);
    
    // 当链表中还有超过一个节点时
    while (n > 0) {
        // 找到要删除的节点的前一个节点
        Node* prev = current;
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        
        // 现在current指向要删除的节点
        printf("%d ", current->data);
        
        if (current->next == current) {
            // 最后一个节点
            free(current);
            break;
        } else {
            // 删除current节点
            prev->next = current->next;
            Node* to_delete = current;
            current = current->next;
            free(to_delete);
        }
        n--;
    }
    
    printf("\n");
}

int main() {
    printf("测试约瑟夫环问题:\n");
    
    // 测试用例1: n=5, k=1, m=2，预期输出: 2 4 1 5 3
    printf("测试1: ");
    josephus(5, 1, 2);
    
    // 测试用例2: n=7, k=3, m=1，预期输出: 3 4 5 6 7 1 2
    printf("测试2: ");
    josephus(7, 3, 1);
    
    // 测试用例3: n=9, k=1, m=8，预期输出: 8 7 9 2 5 4 1 6 3
    printf("测试3: ");
    josephus(9, 1, 8);
    
    return 0;
}