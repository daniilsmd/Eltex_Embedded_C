#include "includes.h"

abonent* create_array(unsigned int block_size)
{
    abonent* struct_init = (abonent*)malloc(sizeof(abonent));
    struct_init->count = 0;
    struct_init->block_size = block_size;
    struct_init->userdata = NULL;

    return struct_init;
}

void input_user_data(abonent* struct_init, void* hb)
{
    struct_init->count++;
    struct_init->userdata = (char*)realloc(struct_init->userdata, struct_init->count * struct_init->block_size);
    memcpy(&struct_init->userdata[(struct_init->count-1)*struct_init->block_size] , hb , struct_init->block_size);

    menu(struct_init);
}

void set_array(abonent* struct_init, unsigned int i, void* hb)
{
    memcpy(&struct_init->userdata[i*struct_init->block_size],hb, struct_init->block_size );
}

void delete_user_data(abonent* struct_init, unsigned int del_pos)
{

    if(struct_init->count < 1)
    {
            printf("Удалять нечего");
            menu(struct_init);
    }

   for(unsigned int j=1; j<struct_init->count-1; j++)
        set_array(struct_init, j, find_user_data(struct_init,j) );

    struct_init->count--;
    struct_init->userdata = (char*)realloc(struct_init->userdata,  struct_init->count*struct_init->block_size);

    menu(struct_init);
}


void* find_user_data(abonent* struct_init, unsigned int i)
{
   return &struct_init->userdata[i * struct_init->block_size];
}

void output_user_data(abonent* struct_init)
{
    for (unsigned int i = 0 ; i < struct_init->count ; i++)
    {

        printf("Абонент:[%d], %s\n",i, (char*)find_user_data(struct_init,i));

    }

    menu(struct_init);
}

void clear_array(abonent* struct_init)
{
    if(struct_init)
    {
        if(struct_init->userdata)
        {
            free(struct_init->userdata);
        };
      free(struct_init);
    };
}