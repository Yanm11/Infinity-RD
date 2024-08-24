#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <string.h> /* strcmp */

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


/* mutable integer class structure */
typedef struct mutable_integer 
{
    object_t object;
    int value;
} mutable_integer_t;

/* typedef for equals method */
typedef int (*equals_func_ptr_t)(object_t*, object_t*);
typedef void (*set_func_ptr_t)(mutable_integer_t*, int);
typedef int (*get_func_ptr_t)(mutable_integer_t*);

/* declerations */
object_t *ObjectInit(void);
void ObjectCtorClassObj(class_t *class, object_t *object);
void ObjectDestroyerObj(object_t *object);
class_t *ObjectGetClassObj(object_t *this);
int ObjectHashCodeObj(object_t *this);
int ObjectEqualsObjObj(object_t *this, object_t *other); 
mutable_integer_t *MutableIntegerInitInt(int value);
void MutableIntegerCtorClassMIInt(class_t *class,
                        mutable_integer_t *mutable_integer,
                        int value);
int MutableIntegerEqualsObjObj(object_t *this, object_t *other);
int MutableIntegerHashCodeObj(object_t *this);
void MutableIntegerSetInt(mutable_integer_t *this, int value);
int MutableIntegerGetInt(mutable_integer_t *this);


/* global variables - classes */
method_ptr_t vtable_object[] = {(method_ptr_t)ObjectGetClassObj,
                                (method_ptr_t)ObjectHashCodeObj,
                                (method_ptr_t)ObjectEqualsObjObj};

method_ptr_t vtable_mutable_integer[] = {(method_ptr_t)ObjectGetClassObj,
                                         (method_ptr_t)MutableIntegerHashCodeObj,
                                         (method_ptr_t)MutableIntegerEqualsObjObj,
                                         (method_ptr_t)MutableIntegerSetInt,
                                         (method_ptr_t)MutableIntegerGetInt};

class_t object_class = {"ObjectClass", NULL, sizeof(object_t), &vtable_object};
class_t mutable_integer_class = {"MutableInteger",
                                 &object_class,
                                 sizeof(mutable_integer_t),
                                 &vtable_mutable_integer};


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

/* mutable int init */
mutable_integer_t *MutableIntegerInitInt(int value)
{
    mutable_integer_t *mutable_integer = (mutable_integer_t*)malloc(
                                                    mutable_integer_class.size);
    if (NULL == mutable_integer)
    {
        return NULL;
    }

    MutableIntegerCtorClassMIInt(&mutable_integer_class, mutable_integer, value);

    return mutable_integer;
}

/* mutable int constroctor */
void MutableIntegerCtorClassMIInt(class_t *class,
                        mutable_integer_t *mutable_integer,
                        int value)
{
    /* calling parent ctor */
    ObjectCtorClassObj(class, (object_t*)mutable_integer);
    mutable_integer->value = value;
}

/* mutable int equals */
int MutableIntegerEqualsObjObj(object_t *this, object_t *other)
{
    if (NULL == this || NULL == other)
    {
        return 0;
    }

    return (((mutable_integer_t*)(this))->value == 
           ((mutable_integer_t*)(other))->value);
}

/* mutable int hashcode */
int MutableIntegerHashCodeObj(object_t *this) 
{
    if (this == NULL) 
    {
        return 0;
    }

    return ((mutable_integer_t *)this)->value % 4096;
}

/* mutable int set */
void MutableIntegerSetInt(mutable_integer_t *this, int value)
{
    if (NULL == this)
    {
        return;
    }
    this->value = value;
}

/* mutable int get */
int MutableIntegerGetInt(mutable_integer_t *this)
{
    if (NULL == this)
    {
        return;
    }
    return this->value;
}

int main(void)
{
    int value_1 = 5;
    int value_2 = 5;

    object_t *object_int_1 = (object_t*)MutableIntegerInitInt(value_1);
    object_t *object_int_2 = (object_t*)MutableIntegerInitInt(value_2);

    int is_equal = ((equals_func_ptr_t)(object_int_1->class->vtable[2]))(object_int_1, object_int_2);
    if (1 == is_equal)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
    
    ((set_func_ptr_t)(object_int_1->class->vtable[3]))(object_int_1, 2);

    is_equal = ((equals_func_ptr_t)(object_int_1->class->vtable[2]))(object_int_1, object_int_2);
    if (1 == is_equal)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }

    is_equal = ((get_func_ptr_t)(object_int_1->class->vtable[4]))(object_int_1);
    if (2 == is_equal)
    {
        printf("value is indeed True\n");
    }
    else
    {
        printf("not true\n");
    }

    ObjectDestroyerObj(object_int_1);
    ObjectDestroyerObj(object_int_2);

    return 0;

}


