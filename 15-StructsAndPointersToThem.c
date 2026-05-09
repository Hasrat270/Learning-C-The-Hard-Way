#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void Person_destroy(struct Person *who)
{
    assert(who != NULL);

    free(who->name);
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    struct Person *hasrat = Person_create("Hasrat", 21, 60, 175);
    struct Person *khan = Person_create("Khan", 21, 60, 180);

    printf("Hasrat is at memory location %p:\n", hasrat);
    Person_print(hasrat);
    
    printf("Khan is at memory location %p:\n", khan);
    Person_print(khan);

    hasrat->age += 20;
    hasrat->height -= 2;
    hasrat->weight += 40;
    Person_print(hasrat);

    khan->age += 20;
    khan->weight += 20;
    Person_print(khan);

    Person_destroy(hasrat);
    Person_destroy(khan);

    return 0;
}
