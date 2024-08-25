/* 
approved by avshalom !
25/08/2024 
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <string.h> /* strcmp strcat */


/****************** defenitions declerations and typedefs *******************/

#define MAX_SIZE_STR 100
#define TO_STR_INDX 3
#define FINALIZED_INDX 4
#define SAY_HELLO_INDX 5
#define NUM_MASTERS_INDX 7

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

/* dog class structure */
typedef struct dog
{
    animal_t animal;
    int num_legs;
}dog_t;

/* cat class structure */
typedef struct cat
{
    animal_t animal;
    char colors[MAX_SIZE_STR];
    int num_masters;
}cat_t;

/* LegendaryAnimal class structure */
typedef struct legendary_animal
{
    cat_t cat;
}legendary_animal_t;

/* typedef for toString method */
typedef char* (*to_string_func_ptr_t)(object_t*);
typedef void (*finalized_func_ptr_t)(object_t*);
typedef void (*say_hello_func_ptr_t)(animal_t*);
typedef int (*num_masters_func_ptr_t)(animal_t*);

/* Declerations */
/* object class */
object_t *ObjectInit(void);
void ObjectCtorClassObj(class_t *class, object_t *object);
void ObjectDestroyerObj(object_t *object);
class_t *ObjectGetClassObj(object_t *this);
int ObjectHashCodeObj(object_t *this);
int ObjectEqualsObjObj(object_t *this, object_t *other); 
char *ObjectToStringObject(object_t *object);
void ObjectFinalizeObject(object_t *object);
/* animal class */
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
char *AnimalToStringAnimal(object_t *object);
void AnimalFinalizeObject(object_t *object);
/* dog class */
dog_t *DogInit(void);
void DogCtorClassDog(class_t *class, dog_t *dog);
void DogSayHelloDog(dog_t *dog);
char *DogToStringDog(object_t *object);
void DogStaticBlocks(void);
void DogFinalizeObject(object_t *object);
/* cat class */
cat_t *CatInit(void);
cat_t *CatInitString(char *color);
void CatCtorClassCat(class_t *class, cat_t *cat);
void CatCtorClassCatString(class_t *class, cat_t *cat, char *color);
void CatStaticBlocks(void);
char *CatToStringCat(object_t *object);
void CatFinalizeObject(object_t *object);
/* legendary animal class */
legendary_animal_t *LegendaryAnimalInit(void);
void LegendaryAnimalCtorClassLa(class_t *class, legendary_animal_t *la);
void LegendaryAnimalStaticBlocks(void);
void LegendaryAnimalSayHelloLegendaryAnimal(legendary_animal_t *la);
char *LegendaryAnimalToStringLegendaryAnimal(object_t *object);
void LegenderyAnimalFinalizeObject(object_t *object);

/* global variables - and classes initializations */
int counter = 0;
int flag_static_block_animal = 1;
int flag_static_block_dog = 1;
int flag_static_block_cat = 1;
int flag_static_block_legenderay_animal = 1;
char g_str[MAX_SIZE_STR] = {0};

method_ptr_t vtable_object[] = {(method_ptr_t)ObjectGetClassObj,
                                (method_ptr_t)ObjectHashCodeObj,
                                (method_ptr_t)ObjectEqualsObjObj,
                                (method_ptr_t)ObjectToStringObject,
                                (method_ptr_t)ObjectFinalizeObject};

method_ptr_t vtable_animal[] = {(method_ptr_t)ObjectGetClassObj,
                                (method_ptr_t)ObjectHashCodeObj,
                                (method_ptr_t)ObjectEqualsObjObj,
                                (method_ptr_t)AnimalToStringAnimal,
                                (method_ptr_t)AnimalFinalizeObject,
                                (method_ptr_t)AnimalSayHelloAnimal,
                                (method_ptr_t)AnimalShowCounter,
                                (method_ptr_t)AnimalGetNumMastersAnimal};

method_ptr_t vtable_dog[] = {(method_ptr_t)ObjectGetClassObj,
                                (method_ptr_t)ObjectHashCodeObj,
                                (method_ptr_t)ObjectEqualsObjObj,
                                (method_ptr_t)DogToStringDog,
                                (method_ptr_t)DogFinalizeObject,
                                (method_ptr_t)DogSayHelloDog,
                                (method_ptr_t)AnimalShowCounter,
                                (method_ptr_t)AnimalGetNumMastersAnimal};

method_ptr_t vtable_cat[] = {(method_ptr_t)ObjectGetClassObj,
                                (method_ptr_t)ObjectHashCodeObj,
                                (method_ptr_t)ObjectEqualsObjObj,
                                (method_ptr_t)CatToStringCat,
                                (method_ptr_t)CatFinalizeObject,
                                (method_ptr_t)AnimalSayHelloAnimal,
                                (method_ptr_t)AnimalShowCounter,
                                (method_ptr_t)AnimalGetNumMastersAnimal};

method_ptr_t vtable_legendary_animal[] = {(method_ptr_t)ObjectGetClassObj,
                    (method_ptr_t)ObjectHashCodeObj,
                    (method_ptr_t)ObjectEqualsObjObj,
                    (method_ptr_t)LegendaryAnimalToStringLegendaryAnimal,
                    (method_ptr_t)LegenderyAnimalFinalizeObject,
                    (method_ptr_t)LegendaryAnimalSayHelloLegendaryAnimal,
                    (method_ptr_t)AnimalShowCounter,
                    (method_ptr_t)AnimalGetNumMastersAnimal};

class_t object_class = {"Object",
                        NULL,
                        sizeof(object_t),
                        vtable_object};

class_t animal_class = {"Animal",
                        &object_class,
                        sizeof(animal_t),
                        vtable_animal};

class_t dog_class = {"Dog",
                        &animal_class,
                        sizeof(dog_t),
                        vtable_dog};

class_t cat_class = {"Cat",
                        &animal_class,
                        sizeof(cat_t),
                        vtable_cat};

class_t legendary_animal_class = {"Legendary Animal",
                                   &cat_class,
                                   sizeof(legendary_animal_t),
                                   vtable_legendary_animal};

/******************************** OBJECT CLASS ***************************/

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
    sprintf(g_str + strlen(g_str), "%d", ObjectHashCodeObj(object));

    return g_str; 
}

/* finalize method */
void ObjectFinalizeObject(object_t *object)
{
    free(object);
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

    /* doing static blocks if neccecary */
    if (flag_static_block_animal)
    {
        AnimalStaticBlocks();
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

    /* doing static blocks if neccecary */
    if (flag_static_block_animal)
    {
        AnimalStaticBlocks();
    }

    AnimalCtorClassAnimalInt(&animal_class, animal, num_masters);

    return animal;
}

/* animal ctor */
void AnimalCtorClassAnimal(class_t *class, animal_t *animal)
{
    /* calling parent ctor */
    ObjectCtorClassObj(class, (object_t*)animal);

        /* instance variable init */
    animal->num_legs = 5;
    animal->num_masters = 1;

    printf("Instance initialization block Animal\n");
    printf("Animal Ctor\n");
    
    ++counter;
    animal->ID = counter;
    ((say_hello_func_ptr_t)class->vtable[SAY_HELLO_INDX])(animal);
    AnimalShowCounter();

    printf("%s\n", ((to_string_func_ptr_t)class->vtable[TO_STR_INDX])((object_t*)animal));
    printf("%s\n", ObjectToStringObject((object_t*)animal));
}

/* animal int ctor*/
void AnimalCtorClassAnimalInt(class_t *class,
                              animal_t *animal,
                              int num_masters)
{
    /* calling parent ctor */
    ObjectCtorClassObj(class, (object_t*)animal);

       /* instance variable init */
    animal->num_legs = 5;
    animal->num_masters = 1;

    printf("Instance initialization block Animal\n");
    printf("Animal Ctor int\n");
    
    ++counter;
    animal->ID = counter;

    animal->num_masters = num_masters;
}

/* sayHello animal method */
void AnimalSayHelloAnimal(animal_t *animal)
{
    printf("Animal Hello!\n");
    printf("I have %d legs\n", animal->num_legs);
}

/* showCounter method */
void AnimalShowCounter(void)
{
    /* doing static blocks if neccecary */
    if (flag_static_block_animal)
    {
        AnimalStaticBlocks();
    }

    printf("%d\n", counter);
}

/* static blocks of animal class */
void AnimalStaticBlocks(void)
{
    flag_static_block_animal = 0;

    printf("Static block Animal 1\n");
    printf("Static block Animal 2\n");
}

/* animal toString method */
char *AnimalToStringAnimal(object_t *object)
{
    /* reset global string */
    char reset[MAX_SIZE_STR] = {0};
    strncpy(g_str, reset, MAX_SIZE_STR);

    /* build the string */
    strcpy(g_str, "Animal with ID: ");
    sprintf(g_str + strlen(g_str), "%d", ((animal_t*)object)->ID);

    return g_str; 
}

/* animal getNimMasters method */
int AnimalGetNumMastersAnimal(animal_t *animal)
{
    return animal->num_masters;
}

/* finalize method */
void AnimalFinalizeObject(object_t *object)
{
    printf("finalize Animal with ID:%d\n", ((animal_t*)object)->ID);
    ((finalized_func_ptr_t)(animal_class.parent_class->
                                            vtable[FINALIZED_INDX]))(object);
}

/************************** DOG CLASS *************************/
/* dog init */
dog_t *DogInit(void)
{
    dog_t *dog = (dog_t*)malloc(dog_class.size);
    if (NULL == dog)
    {
        return NULL; 
    }

    /* doing static blocks of parent and child if neccecary */
    if (flag_static_block_animal)
    {
        AnimalStaticBlocks();
    }
    if (flag_static_block_dog)
    {
        DogStaticBlocks();
    }   
    
    DogCtorClassDog(&dog_class, dog);

    return dog;
}

/* dog ctor */
void DogCtorClassDog(class_t *class, dog_t *dog)
{
    /* calling parent ctor */
    int num_masters = 2;
    AnimalCtorClassAnimalInt(class, (animal_t*)dog, num_masters);

    dog->num_legs = 4;

    printf("Instance initialization block Dog\n");
    printf("Dog Ctor\n");
}

/* sayHello animal method */
void DogSayHelloDog(dog_t *dog)
{
    printf("Dog Hello!\n");
    printf("I have %d legs\n", dog->num_legs);
}

/* static blocks of static class */
void DogStaticBlocks(void)
{
    flag_static_block_dog = 0;

    printf("Static block Dog\n");
}

/* dog toString method */
char *DogToStringDog(object_t *object)
{
    /* reset global string */
    char reset[MAX_SIZE_STR] = {0};
    strncpy(g_str, reset, MAX_SIZE_STR);

    /* build the string */
    strcpy(g_str, "Dog with ID: ");
    sprintf(g_str + strlen(g_str), "%d", ((animal_t*)object)->ID);

    return g_str; 
}

/* finalize method */
void DogFinalizeObject(object_t *object)
{
    printf("finalize Dog with ID:%d\n", ((animal_t*)object)->ID);
    ((finalized_func_ptr_t)(dog_class.parent_class->
                                            vtable[FINALIZED_INDX]))(object);
}

/************************** CAT CLASS *************************/

/* cat init */
cat_t *CatInit(void)
{
    cat_t *cat = (cat_t*)malloc(cat_class.size);
    if (NULL == cat)
    {
        return NULL; 
    }

    /* doing static blocks of parent and child if neccecary */
    if (flag_static_block_animal)
    {
        AnimalStaticBlocks();
    }
    if (flag_static_block_cat)
    {
        CatStaticBlocks();
    }  

    /* calling the constroctors */
    CatCtorClassCat(&cat_class, cat);

    return cat;
}

/* cat init with color */
cat_t *CatInitString(char *color)
{
    cat_t *cat = (cat_t*)malloc(cat_class.size);
    if (NULL == cat)
    {
        return NULL; 
    }

    /* doing static blocks of parent and child if neccecary */
    if (flag_static_block_animal)
    {
        AnimalStaticBlocks();
    }
    if (flag_static_block_cat)
    {
        CatStaticBlocks();
    } 

    /* calling the constroctors */
    CatCtorClassCatString(&cat_class, cat, color);

    return cat;
}

/* cat ctor */
void CatCtorClassCat(class_t *class, cat_t *cat)
{
    /* calling parent ctor */
    CatCtorClassCatString(class, cat, "black");

    printf("Cat Ctor\n");

    cat->num_masters = 2;
}

/* cat ctor with color */
void CatCtorClassCatString(class_t *class, cat_t *cat, char *color)
{
    /* calling parent ctor */
    AnimalCtorClassAnimal(class, (animal_t*)cat);
    
    /* assigning values for instance variable */
    cat->num_masters = 5;

    strcpy(cat->colors,color);

    printf("Cat Ctor with color: %s\n", cat->colors);
}

/* static blocks of static class */
void CatStaticBlocks(void)
{
    flag_static_block_cat = 0;

    printf("Static block Cat\n");
}

/* cat toString method */
char *CatToStringCat(object_t *object)
{
    /* reset global string */
    char reset[MAX_SIZE_STR] = {0};
    strncpy(g_str, reset, MAX_SIZE_STR);

    /* build the string */
    strcpy(g_str, "Cat with ID: ");
    sprintf(g_str + strlen(g_str), "%d", ((animal_t*)object)->ID);

    return g_str; 
}

/* finalize method */
void CatFinalizeObject(object_t *object)
{
    printf("finalize Cat with ID:%d\n", ((animal_t*)object)->ID);
    ((finalized_func_ptr_t)(cat_class.parent_class->
                                            vtable[FINALIZED_INDX]))(object);
}

/************************** LEGENDARY ANIMAL CLASS *************************/

/* LegendaryAnimal init */
legendary_animal_t *LegendaryAnimalInit(void)
{
    legendary_animal_t *la = 
                    (legendary_animal_t*)malloc(legendary_animal_class.size);
  
    if (NULL == la)
    {
        return NULL; 
    }

    /* doing static blocks of parent and child if neccecary */
    if (flag_static_block_animal)
    {
        AnimalStaticBlocks();
    }
    if (flag_static_block_cat)
    {
        CatStaticBlocks();
    }
    if (flag_static_block_legenderay_animal)
    {
        LegendaryAnimalStaticBlocks();
    }

    /* calling the constroctors */
    LegendaryAnimalCtorClassLa(&legendary_animal_class, la);

    return la;
}

/* legendary animal ctor */
void LegendaryAnimalCtorClassLa(class_t *class, legendary_animal_t *la)
{
    /* calling parent ctor */
    CatCtorClassCat(class, (cat_t*)la);

    printf("Legendary Ctor\n");
}

/* static blocks of static class */
void LegendaryAnimalStaticBlocks(void)
{
    flag_static_block_legenderay_animal = 0;

    printf("Static block Legendary Animal\n");
}

/* sayHello method */
void LegendaryAnimalSayHelloLegendaryAnimal(legendary_animal_t *la)
{
    printf("Legendary Hello!\n");
}

/* legendary animal toString method */
char *LegendaryAnimalToStringLegendaryAnimal(object_t *object)
{
    /* reset global string */
    char reset[MAX_SIZE_STR] = {0};
    strncpy(g_str, reset, MAX_SIZE_STR);

    /* build the string */
    strcpy(g_str, "LegendaryAnimal with ID: ");
    sprintf(g_str + strlen(g_str), "%d", ((animal_t*)object)->ID);

    return g_str; 
}

/* finalize method */
void LegenderyAnimalFinalizeObject(object_t *object)
{
    printf("finalize LegendaryAnimal with ID:%d\n", ((animal_t*)object)->ID);
    ((finalized_func_ptr_t)(legendary_animal_class.parent_class->
                                            vtable[FINALIZED_INDX]))(object);
}

/********************************* MAIN ****************************/

void Foo(animal_t *a)
{
    printf("%s\n",((to_string_func_ptr_t)((object_t*)a)->class
                                        ->vtable[TO_STR_INDX])((object_t*)a));
}

int main(void)
{
    size_t i =0;
    object_t *object;
    animal_t *animal = AnimalInit();
    dog_t *dog = DogInit();
    cat_t *cat = CatInit();
    legendary_animal_t *la = LegendaryAnimalInit();
    animal_t *array[5] = {NULL};

    AnimalShowCounter();

    printf("%d\n", animal->ID);
    printf("%d\n", ((animal_t*)dog)->ID);
    printf("%d\n", ((animal_t*)cat)->ID);
    printf("%d\n", ((animal_t*)la)->ID);

    array[0] = (animal_t*)(DogInit());
    array[1] = (animal_t*)(CatInit());
    array[2] = (animal_t*)(CatInitString("white"));  
    array[3] = (animal_t*)(LegendaryAnimalInit());                  
    array[4] = AnimalInit();
    
    for (; i < 5; ++i)
    {
        int num_masters = ((num_masters_func_ptr_t)((array[i])->object.class->
                                        vtable[NUM_MASTERS_INDX]))(array[i]);

        ((say_hello_func_ptr_t)((array[i])->object.class->
                                            vtable[SAY_HELLO_INDX]))(array[i]);
        
        printf("%d\n", num_masters);
    }

     for (i = 0; i < 5; ++i)
    {
        Foo(array[i]);
        ((finalized_func_ptr_t)((array[i])->object.class->
                                vtable[FINALIZED_INDX]))((object_t*)(array[i]));
    }
    
    AnimalFinalizeObject((object_t*)animal);
    DogFinalizeObject((object_t*)dog);
    CatFinalizeObject((object_t*)cat);
    LegenderyAnimalFinalizeObject((object_t*)la);
    

    return 0;
}


