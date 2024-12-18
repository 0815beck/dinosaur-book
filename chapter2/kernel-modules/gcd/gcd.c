/*
*   This kernel module prints out GOLDEN_RATIO_PRIME
*   in the init method and computes a greatest
*   common divisor in the exit method.
*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>

int gcd_init(void) {
    printk(KERN_INFO "Loading Kernel Module∖n");
    printk(KERN_INFO "GOLDEN_RATIO_PRIME = %lu∖n", GOLDEN_RATIO_PRIME);
    return 0;
}

void gcd_exit(void) {
    unsigned long x = gcd(3300ul, 24u);
    printk(KERN_INFO "Computation... gcd(3300, 24) = %lu\n", x);
    printk(KERN_INFO "Removing Kernel Module gcd\n");
}

module_init(gcd_init);
module_exit(gcd_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GCD Module");
MODULE_AUTHOR("Nico");