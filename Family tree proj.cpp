#include<iostream>
#include<string>

using namespace std;

class node
{
public:
    char name[50];
    int age, height;    
    bool gender;             
    node* fc;          
    node* sibling;           

    node()
    {
        
        fc = sibling = NULL;
        gender = 0;
        strcpy(name, "");
        age = height = 0;
        
    }
    void getData()
    {
        char ch;
        cout << "enter Name of the Person: ";
        cin >> name;
        cout << " Enter age of " << name << ": ";
        cin >> age;
        cout << name << " is male or female (enter m or f): ";
        cin >> ch;
        if (ch == 'm')
            gender = 1;
    }
};


class familyTree
{
public:

    node* start;

    familyTree()
    {
        start = NULL;
    }

    node* traverseDown(node* ptr, char s[25])
    {
        ptr = ptr->fc;

        while (ptr != NULL)
        {
            if (strcmp(ptr->name, s) == 0)
                return ptr;
            else if (traverseRight(ptr, s) != NULL)
                return traverseRight(ptr, s);
            else
                ptr = ptr->fc;
        }
        return NULL;
    }
    node* traverseRight(node* ptr, char s[25])
    {
        ptr = ptr->sibling;

        while (ptr != NULL)
        {
            if (strcmp(ptr->name, s) == 0)
                return ptr;
            else if (traverseDown(ptr, s) != NULL)
                return traverseDown(ptr, s);
            else
                ptr = ptr->sibling;
        }
        return NULL;
    }
    node* search(char s[25])
    {
        node* ptr = start;

        if (strcmp(ptr->name, s) == 0)
            return ptr;
        else if (traverseRight(start, s) != NULL)
            return traverseRight(start, s);
        else if (traverseDown(start, s) != NULL)
            return traverseDown(start, s);
        else
        {
            return NULL;
            cout << " Not found " << endl;
        }
    }

    void add_new_Sibling(node* a, node* b)
    {
        while (a->sibling != NULL)
            a = a->sibling;
        a->sibling = b;

        b->height = a->height;
    }
    void add_new_Child(node* a, node* b)
    {
        if (a->fc == NULL)
            a->fc = b;
        else
            add_new_Sibling(a->fc, b);

        b->height = a->height + 1;
    }
    void addNew()
    {
        node* temp = new node;
        temp->getData();

        if (start == NULL)
        {
            start = temp;
            temp->height = 0;
        }

        else
        {
            cout << " Enter any relation's name: ";
            char name[50];
            cin >> name;
            cout << "1. Child\n2. Sibiling\n" << temp->name << " is to " << name << " : ";
            int opt;
            cin >> opt;
            switch (opt)
            {
            case 1:
                add_new_Child(search(name), temp);
                break;
            case 2:
                add_new_Sibling(search(name), temp);
                break;

            }
        }
        cout << "\nPerson sucessfully added.\n";
    }

    void find()
    {
        char name1[50], name2[50];
        cout << "Enter names of two persons: ";
        cin >> name1 >> name2;
        node* ptr1 = search(name1);
        node* ptr2 = search(name2);
        node* ptr;
        node* ptrk = ptr1;
        node* ptrk1 = ptr2;

        switch (ptr1->height - ptr2->height)
        {

        case 0:
            char s[50];
            strcpy(s, "sister");
            if (ptr1->gender)
                strcpy(s, "brother");

            ptr = ptr1;
            while (ptr != NULL)
            {
                if (ptr == ptr2)
                {
                    cout << endl << name1 << " is " << name2 << "'s " << s << endl;
                    return;
                }
                ptr = ptr->sibling;
            }
            ptr = ptr2;
            while (ptr != NULL)
            {
                if (ptr == ptr1)
                {
                    cout << endl << name1 << " is " << name2 << "'s " << s << endl;
                    return;
                }
                ptr = ptr->sibling;
            }
            cout << endl << name1 << " and " << name2 << " are Cousins";
            break;

        case 1:
            char str3[50];
            strcpy(str3, "daughter");
            if (ptr1->gender)
                strcpy(str3, "son");
            ptr2 = ptr2->fc;
            while (ptr2 != NULL)
            {
                if (ptr2 == ptr1)
                {
                    cout << endl << name1 << " is " << name2 << "'s " << str3;
                    return;
                }
                ptr2 = ptr2->sibling;
            }
            strcpy(str3, "niece");
            if (ptr1->gender)
                strcpy(str3, "nephew");
            cout << endl << name1 << " is " << name2 << "'s " << str3;
            break;
        case -1:
            char str[10];
            strcpy(str, "mother");
            if (ptrk->gender)
                strcpy(str, "father");

            ptr = ptrk->fc;
            while (ptr != NULL)
            {
                if (ptr == ptrk1)
                {
                    cout << endl << name1 << " is " << name2 << "'s " << str;
                    return;
                }
                ptr = ptr->sibling;
            }
            strcpy(str, "aunt");
            if (ptrk->gender)
                strcpy(str, "uncle");
            cout << endl << name1 << " is " << name2 << "'s " << str;
            break;

        case 2:
            char str1[50];
            strcpy(str1, "daughter");
            if (ptr2->gender)
                strcpy(str1, "son");
            ptr2 = ptr2->fc->fc;
            while (ptr2 != NULL)
            {
                if (ptr2 == ptr1)
                {
                    cout << endl << name1 << " is grandparent " << str1 << " of " << name2;
                    return;
                }
                ptr2 = ptr2->sibling;
            }
            break;
        case -2:
            char str2[50];
            strcpy(str2, "mother");

            if (ptr1->gender)
                strcpy(str2, "father");

            ptr1 = ptr1->fc->fc;

            while (ptr1 != NULL)
            {
                if (ptr1 == ptr2)
                {
                    cout << endl << name1 << " is grandparent " << str2 << " of " << name2;
                    return;
                }
                ptr1 = ptr1->sibling;
            }

            break;
        default:
            cout << "Too far relationship or No relationship";
            break;
        }
    }

    void show(node* ptr)
    {
        char g[10];
        strcpy(g, "Female");
        if (ptr->gender)
            strcpy(g, "Male");
        cout << "\n\nName: " << ptr->name << endl;
        cout << "Age: " << ptr->age << endl;
        cout << "Gender: " << g << endl;
    }
    void display(node* ptr)
    {
        if (ptr == NULL)
            return;

        while (ptr != NULL)
        {
            cout << ptr->name << endl;
            display(ptr->fc);
            ptr = ptr->sibling;
        }
    }
    
    void update_height(node* ptr, int x)
    {
        if (ptr == NULL)
            return;

        while (ptr != NULL)
        {
            update_height(ptr->fc, x++);
            if (ptr->sibling != NULL)
                ptr->sibling->height = x;
            ptr = ptr->sibling;
        }
    }

};


void connect(familyTree* T1, familyTree* T2)
{
    char name[50];
    int opt;
    int x;
    cout << "Name of person in 1st tree to merge: ";
    cin >> name;
    cout << T2->start->name << " is to " << name << "\n1. Child 2. Sibling - ";;
    cin >> opt;
    node* ptr = T1->search(name);
    switch (opt)
    {
    case 1:
        T1->add_new_Child(ptr, T2->start);
        x = ptr->height + 1;
        break;
    case 2:
        T1->add_new_Sibling(ptr, T2->start);
        x = ptr->height;
        break;
    }
    T2->update_height(T2->start, x);
   
    cout << "Merged" << endl;
}

int main()
{
    familyTree T[100];
    int opt, n, n1, n2;
    char c, name[50];
    cout << "Enter the family tree number = ";
    cin >> n;
    while (1)
    {
        system("cls");

        cout << "\tFamily tree no = " << n << "\n\t1. Add new person\n\t2. Find relationship b/w two persons\n\t3. Search\n\t4. Display\n\t5. Exit\n\n\tEnter your choice = ";
        cin >> opt;
        cout << endl;

        switch (opt)
        {

        default:
            cout << "Invalid input";
            break;

        case 1:
            T[n].addNew();
            break;

        case 2:
            T[n].find();
            break;

        case 3:
            cout << "Enter name of person to search: ";
            cin >> name;
            T[n].show(T[n].search(name));
            break;

        case 4:
            T[n].display(T[n].start);
            break;

        case 5:
            return 0;
        }
        cout << "\nPress any key to continue.....";
        cin >> c;
    }
    return 0;
}