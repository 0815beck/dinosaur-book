/*
*   This kernel module adds a new entry /proc/seconds to the pseudo-file-system /proc
*   Reading /proc/seconds reports the number of seconds since the module was loaded
*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/param.h>
#include <linux/jiffies.h>


#define PROC_NAME "seconds"
#define BUFFER_SIZE 1024

ssize_t proc_read(struct file *file, char __user *user_buf, size_t count, loff_t *pos);

unsigned long start_jiffies;

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

int seconds_init(void) {
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    printk(KERN_INFO "Module Running was loaded");
    start_jiffies = jiffies;
    printk(KERN_INFO "We have that start_jiffies = %lu", start_jiffies);
    return 0;
}

void seconds_exit(void) {
    printk(KERN_INFO "The module running was removed.");
    remove_proc_entry(PROC_NAME, NULL);
}

ssize_t proc_read(struct file *file, char __user *user_buf, size_t count, loff_t *pos) {

    static int completed = 0;

    if (completed) {
        completed = 0;
        return 0;
    }

    completed = 1;

    printk(KERN_INFO "proc_read was called. HZ = %d, jiffies = %lu", HZ, jiffies);

    unsigned long seconds; 
    char buffer[BUFFER_SIZE];
    int rv;
    
    seconds = (jiffies - start_jiffies) / HZ;
    rv = sprintf(buffer, "The running module is running for %lu seconds.\n", seconds);
    copy_to_user(user_buf, buffer, rv);

    return rv;
}

module_init(seconds_init);
module_exit(seconds_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds is running for ..seconds");
MODULE_AUTHOR("Nico");