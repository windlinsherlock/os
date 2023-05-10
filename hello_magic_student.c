/* Hello from Kernel! */
#include <linux/module.h>

MODULE_LICENSE("GPL");

/*id*/
static char* id = "student id";
module_param(id, charp, 0644);
MODULE_PARM_DESC(id, "char* param\n");

/*name*/
static char* name = "student name";
module_param(name, charp, 0644);
MODULE_PARM_DESC(name, "char* param\n");

/*age*/
static int age = 18;
module_param(age, int, 0644);
MODULE_PARM_DESC(age, "int param\n");


/*--------------begin-请在此处定义函数 hello student(...)----------*/

void hello_student(char* id,char* name,int age)
{
    printk(KERN_ALERT "My name is %s, student id is %s. I am %d years old.\n", name, id, age);
}




/*----------------------end-----------------*/



/*--------------begin--请在此处定义函数 my magic number(.)---------*/


void my_magic_number(char* id,int age)
{
    int magic_number = age;
    int i = 0;
    while (id[i] != '\0'){
        age += id[i] - '0';
        i ++;
    }
    magic_number = magic_number % 10;
    printk(KERN_ALERT "My magic number is %d.\n", magic_number);
}


/*----------------------end-----------------*/


int __init hello_init(void)
{
	printk(KERN_ALERT "Init module.\n");
	hello_student(id, name,age);
	my_magic_number(id,age);
	return 0;
}


void __exit hello_exit(void)
{
	printk(KERN_ALERT "Exit module.\n");
}
module_init(hello_init);
module_exit(hello_exit);
