#include <iostream>



class Node {
    public:
    int data;
    Node* next;
    Node(int data = int(), Node* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

#pragma region Однонаправленный список с заглавным звеном

void init(Node*& list) {
    list = new Node();
}

bool isEmpty(Node* list) {
    return list->next == nullptr;
}

void pushBack(Node*& list, int data) {
    Node* temp = list;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new Node(data);
}

void insertAfter(Node* selectedNode, int data) {
    Node* newNode = new Node(data, selectedNode->next);
    selectedNode->next = newNode;
}

int deleteAfter(Node* selectedNode) {
    Node* deletedNode = selectedNode->next;
    selectedNode->next = deletedNode->next;
    int result = deletedNode->data;
    deletedNode->next = nullptr;
    delete deletedNode;
    return result;
}

void printList(Node* list) {
    Node* temp = list->next;
    while (temp != nullptr) {
        std::cout << temp->data << ' ';
        temp = temp->next;
    }
    std::cout << std::endl;
}

void clearList(Node*& list) {
    while (list->next != nullptr) {
        deleteAfter(list);
    }
}

#pragma endregion

#pragma region Функции решения задач

/*
Список заданий:
1. Перед первым двузначным числом вставить его квадрат +
2. Удалить все элементы кратные 7 +
3. Переставить максимальный элемент в голову списка, переключая указатели +
4. Упорядяочить список по возрастанию методом простых вставок
5. Рекурсивно построить копию списка без нечетных элементов +
*/

void insertSquareBFD(Node*& list) {
    Node* temp = list;
    bool found = false;
    while (temp->next != nullptr && !found) {
        int absValue = abs(temp->next->data);
        if ((absValue / 10) > 0 && (absValue / 10) < 10) {
            insertAfter(temp, absValue * absValue);
            found = true;
        }
        temp = temp->next;
    }
}

void deleteAllSevens(Node*& list) {
    Node* temp = list;
    while (temp->next != nullptr) {
        if (temp->next->data % 7 == 0) {
            deleteAfter(temp);
        }
        else {
            temp = temp->next;
        }
    }
}

void moveMaxToHead(Node*& list) {
    if (!isEmpty(list)) {
        Node* p = list;
        Node* beforeMaxNode = list;
        while (p->next != nullptr) {
            if (p->next->data > beforeMaxNode->next->data) {
                beforeMaxNode = p;
            }
            p = p->next;
        }
        int value = deleteAfter(beforeMaxNode);
        insertAfter(list, value);
    }
}

// void simpleInsertSort(Node*& list);

void recCopyWithoutOdds(Node* list, Node* tail) {
    // Исходный список без заглавного звена
    if (list != nullptr) {
        if (list->data % 2 == 0) {
            tail->next = new Node(list->data);
            recCopyWithoutOdds(list->next, tail->next);
        }
        else {
            recCopyWithoutOdds(list->next, tail);
        }
    }
}

#pragma endregion

int main() {
    Node* list;
    Node* destList;
    init(list);
    init(destList);

    for (int i = 0; i < 5; i++) {
        int value;
        std::cin >> value;
        pushBack(list, value);
    }
    recCopyWithoutOdds(list->next, destList);

    printList(destList);
    clearList(destList);
    clearList(list);
    system("pause");
}