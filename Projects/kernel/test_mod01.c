#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kern_levels.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cache.h>
#include <linux/seqlock.h>
#include <linux/jiffies.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");

#define ECE_BUF_SIZE 4096

static char bank[5][5] = { "chair" , "juice" , "board", "grape" , "mouse"};

static char ece_buffer[ECE_BUF_SIZE];
static char transfer[ECE_BUF_SIZE];
static char word[ECE_BUF_SIZE];
//static char bank1[ECE_BUF_SIZE] = "chair";
int isReg;
int major;
int ece_offset_w;
int ece_offset_r;
int ece_size;
int num;
int ece_offset_follow_end;
int ece_offset_follow_start;
int c; // short for
int r; //short for random num location

static ssize_t ece_read(struct file *fp, char *buf,
    size_t count, loff_t *offset)
{
    int ret = 0;
    if(ece_offset_r + count >= ECE_BUF_SIZE)
    {
        printk(KERN_INFO " ECE4310: Read OverFlow. Abort. \n");
        return -1;
    }
    printk(KERN_INFO " ECE4310: Copy to user. \n");
    ret = copy_to_user(buf, transfer, count);
    //printk(ret);
    if(ret != 0)
    {
        printk(KERN_INFO " ECE4310: ERR copy to user. \n");
        return -1;
    }
    
    ece_offset_r = ece_offset_r + count;

    return count;
}

static ssize_t ece_write(struct file *fp, const char *buf,
    size_t count, loff_t *op)
{
    int ret = 0;
    for(;ret < 5; ret++)
    {
        transfer[ret] = 'x';
    }
    ret = 0; //reset
    if(ece_offset_w + count >= ECE_BUF_SIZE)
    {
        printk(KERN_INFO " ECE4310: Write OverFlow. Abort. \n");
        return -1;
    }
    printk(KERN_INFO " ECE4310: Copy from user. \n");
    ret = copy_from_user(ece_buffer, buf, count);
    //printk(ret);
    if(ret != 0)
    {
        printk(KERN_INFO " ECE4310: ERR copy from user. \n");
        return -1;
    }
    //ece_offset_follow_start = ece_offset_w;
    //ece_offset_w = ece_offset_w + count;
    //ece_offset_follow_end = ece_offset_w;
    int i = 0;
    int j = 0;
    printk(KERN_INFO "%s", ece_buffer);
    for(i=0;i < 5;i++)
    {
        //now do for i values
        printk(KERN_INFO " check for i \n");
        for(j=0; j < 5;j++)
        {
            if(ece_buffer[i] == word[j])
            {
                transfer[i] = 'i';// lower case i
            }
        }
        
        printk(KERN_INFO " check for o \n");
        if(ece_buffer[i] == word[i])
        {
            transfer[i] = 'o';// lower case o
        }
        else if(ece_buffer[i] != word[i] && transfer[i] != 'i' ) //start with x for not in word
        {
            transfer[i] = 'x'; //120 is lower case x
        }
    }
    /*int k = ece_offset_follow_start;
    for(; k < ece_offset_follow_end;k++)
    {
        ece_buffer[k] = transfer[k];
    }*/
    return count;
}
/*
static ssize_t ece_write(struct file *fp, const char *buf,
    size_t count, loff_t *op)
{
    int ret = 0;
    if(ece_offset_w + count >= ECE_BUF_SIZE)
    {
        printk(KERN_INFO " ECE4310: Write OverFlow. Abort. \n");
        return -1;
    }
    printk(KERN_INFO " ECE4310: Copy from user. \n");
    ret = copy_from_user(&ece_buffer[ece_offset_w], buf, count);
    //printk(ret);
    if(ret != 0)
    {
        printk(KERN_INFO " ECE4310: ERR copy from user. \n");
        return -1;
    }
    //ece_offset_follow_start = ece_offset_w;
    //ece_offset_w = ece_offset_w + count;
    //ece_offset_follow_end = ece_offset_w;
    int i = 0;
    int j = 0;
    for(;i < 5;i++)
    {
        //now do for i values
        printk(KERN_INFO " check for i \n");
        for(; j < 5;j++)
        {
            if(ece_buffer[i] == word[j] && transfer[i] != 'o')
            {
                transfer[i] = 'i';// lower case i
            }
        }
        
        printk(KERN_INFO " check for o \n");
        if(ece_buffer[i] == word[i])
        {
            transfer[i] = 'o';// lower case o
        }
        else if(ece_buffer[i] != word[i] && transfer[i] != 'i' ) //start with x for not in word
        {
            transfer[i] = 'x'; //120 is lower case x
        }
    }
    int k = 0;
    for(; k < 5;k++)
    {
        ece_buffer[k] = transfer[k];
    }
    return count;
}
*/

static struct file_operations ece_fops =
{
    .read = ece_read,
    .write = ece_write,
};

int ece_init(void)
{
    int ret = 0;
    major = register_chrdev(0, "test_mod01", &ece_fops);
    ece_offset_w = 0;
    ece_offset_r = 0;
    ece_size = 0;
    ece_offset_follow_end = 0;
    ece_offset_follow_start = 0;
    r = jiffies % 5;
    for(;ret < 5; ret++)
    {
        transfer[ret] = 'x';
    }
    ret = 0; //reset
    if(major < 0)
    {
        isReg = 0;
        printk(KERN_INFO " ECE4310: Start FAIL \n");
    }
    else
    {
        isReg = 1;
        printk(KERN_INFO " ECE4310: Start here \n");
    }

    //get_randon_bytes(&num, sizeof(num));
    //num = num % 5;
    int n;
    for(n = 0; n<5;n++)
    {
        word[n] = bank[r][n];
    }
    printk(KERN_INFO " the word is %s \n", word);
    return 0;
}

void ece_end(void)
{
    if(isReg)
    {
        unregister_chrdev(major, "test_mod01");
    }
    printk(KERN_INFO " ECE4310: End here \n");
}

module_init(ece_init);
module_exit(ece_end);