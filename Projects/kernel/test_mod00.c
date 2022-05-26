#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kern_levels.h>

MODULE_LICENSE("GPL");

int ece_init(void)
{
    printk(KERN_INFO " ECE 4310: Start here \n");
    return 0;
}

void ece_end(void)
{
    printk(KERN_INFO " ECE 4310: End here \n");
}

module_init(ece_init);
module_exit(ece_end);