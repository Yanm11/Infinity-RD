#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <string.h> /* strcmp strcat */


/****************** defenitions declerations and typedefs *******************/

#define MAX_SIZE_STR 100

typedef void (*method_ptr_t)(void);

/* class structure representing metadata for classes */
typedef struct class 
{
	const char *class_name;
	struct class *parent_class; 
	size_t size;
	method_ptr_t *vtable;
} class_t;

/* object class structure */
typedef struct object
{
	class_t *class;
} object_t;


/* animal class structure */
typedef struct animal 
{
    object_t object;
    int num_legs;
    int num_masters;
    int ID;
} animal_t;

/* typedef for equals method */
typedef int (*equals_func_ptr_t)(object_t*, object_t*);


/* declerations */
object_t *ObjectInit(void);
void ObjectCtorClassObj(class_t *class, object_t *object);
void ObjectDestroyerObj(object_t *object);
class_t *ObjectGetClassObj(object_t *this);
int ObjectHashCodeObj(object_t *this);
int ObjectEqualsObjObj(object_t *this, object_t *other); 
char *ObjectToStringObject(object_t *object);
animal_t *AnimalInit(void);
animal_t *AnimalInitInt(int num_masters);
void AnimalCtorClassAnimal(class_t *class, animal_t *animal);
void AnimalCtorClassAnimalInt(class_t *class,
                              animal_t *animal,
                              int num_masters);
void AnimalSayHelloAnimal(animal_t *animal);
void AnimalShowCounter(void);
int AnimalGetNumMastersAnimal(animal_t *animal);
void AnimalStaticBlocks(void);
char *AnimalToStringAnimal(animal_t *animal);


/* global variables - classes */
int counter = 0;
int flag_static_block_animal = 1;
char g_str[MAX_SIZE_STR] = {0};

method_ptr_t vtable_object[] = {(method_ptr_t)ObjectGetClassObj,
                                (method_ptr_t)ObjectHashCodeObj,
                                (method_ptr_t)ObjectEqualsObjObj,
                                (method_ptr_t)ObjectToStringObject};

method_ptr_t vtable_animal[] = {(method_ptr_t)ObjectGetClassObj,
                                (method_ptr_t)ObjectHashCodeObj,
                                (method_ptr_t)ObjectEqualsObjObj,
                                (method_ptr_t)AnimalToStringAnimal,
                                (method_ptr_t)AnimalSayHelloAnimal,
                                (method_ptr_t)AnimalShowCounter,
                                (method_ptr_t)AnimalGetNumMastersAnimal};

class_t object_class = {"Object", NULL, sizeof(object_t), &vtable_object};
class_t animal_class = {"Animal",
                        &object_class,
                        sizeof(animal_t),
                        &vtable_animal};

/* object init */
object_t *ObjectInit(void)
{
    object_t *object = (object_t*)malloc(object_class.size);
    if (NULL == object)
    {
        return NULL;
    }

    ObjectCtorClassObj(&object_class, object);

    return object;
}

/* object constroctor */
void ObjectCtorClassObj(class_t *class, object_t *object)
{
    object->class = class;
}

/* object free method */
void ObjectDestroyerObj(object_t *object)
{
    free(object);
}

/* getClass method */
class_t *ObjectGetClassObj(object_t *this) 
{
    if (this == NULL)
    {
        return NULL;
    }

    return this->class;
}

/* hashCode method */
int ObjectHashCodeObj(object_t *this) 
{
    if (this == NULL) 
    {
        return 0;
    }

    return (int)((size_t)this);
}

/* equals method */
int ObjectEqualsObjObj(object_t *this, object_t *other) 
{
    return this == other;
}

/* object toString method */
char *ObjectToStringObject(object_t *object)
{
    /* reset global string */
    char reset[MAX_SIZE_STR] = {0};
    strncpy(g_str, reset, MAX_SIZE_STR);

    /* build the string */
    strcpy(g_str, ObjectGetClassObj(object)->class_name);
    strcat(g_str, "@");
    sprintf(g_str + strlen(g_str), "%d\n", ObjectHashCodeObj(object));

    return g_str; 
}

/************************** ANIMAL CLASS *************************/
/* animal init */
animal_t *AnimalInit(void)
{
    animal_t *animal = (animal_t*)malloc(animal_class.size);
    if (NULL == animal)
    {
        return NULL; 
    }

    AnimalCtorClassAnimal(&animal_class, animal);

    return animal;
}

/* animal init int */
animal_t *AnimalInitInt(int num_masters)
{
    animal_t *animal = (animal_t*)malloc(animal_class.size);
    if (NULL == animal)
    {
        return NULL; 
    }

    AnimalCtorClassAnimalInt(&animal_class, animal, num_masters);

    return animal;
}

/* animal ctor */
void AnimalCtorClassAnimal(class_t *class, animal_t *animal)
{
    /* calling parent ctor */
    ObjectCtorClassObj(class, (object_t*)animal);

    /* doing static blocks if neccecary */
    AnimalStaticBlocks();

    animal->num_legs = 5;

    printf("Instance initialization block Animal\n");
    printf("Animal Ctor\n");
    
    ++counter;
    animal->ID = counter;
    AnimalSayHelloAnimal(animal);
    AnimalShowCounter();

    printf("%s\n", AnimalToStringAnimal(animal));
    printf("%s\n", ObjectToStringObject((object_t*)animal));
}

/* animal int ctor*/
void AnimalCtorClassAnimalInt(class_t *class,
                              animal_t *animal,
                              int num_masters)
{
    /* calling parent ctor */
    ObjectCtorClassObj(class, (object_t*)animal);

    /* doing static blocks if neccecary */
    AnimalStaticBlocks();

    animal->num_legs = 5;
    
    printf("Instance initialization block Animal\n");
    printf("Animal Ctor int\n");
    
    ++counter;
    animal->ID = counter;

    animal->num_masters = num_masters;
}

/* sayHello animal method */
void AnimalSayHelloAnimal(animal_t *animal)
{
    printf("Animal Hello\n");
    printf("I have %d legs\n", animal->num_legs);
}

/* showCounter method */
void AnimalShowCounter(void)
{
    /* doing static blocks if neccecary */
    AnimalStaticBlocks();

    printf("%d\n", counter);
}

/* static blocks of animal class */
void AnimalStaticBlocks(void)
{
    if (flag_static_block_animal)
    {
        flag_static_block_animal = 0;

        printf("Static block Animal 1\n");
        printf("Static block Animal 2\n");
    }
}

/* animal toString method */
char *AnimalToStringAnimal(animal_t *animal)
{
    /* reset global string */
    char reset[MAX_SIZE_STR] = {0};
    strncpy(g_str, reset, MAX_SIZE_STR);

    /* build the string */
    strcpy(g_str, "Animal with ID: ");
    sprintf(g_str + strlen(g_str), "%d\n", animal->ID);

    return g_str; 
}

/* animal getNimMasters method */
int AnimalGetNumMastersAnimal(animal_t *animal)
{
    return animal->num_masters;
}

int main(void)
{
 
    animal_t *animal = AnimalInit();


    return 0;

}


