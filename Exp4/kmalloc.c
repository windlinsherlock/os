#include <linux/module.h>  
#include <linux/slab.h>
MODULE_LICENSE("GPL");

unsigned char *kmallocmem1;  
unsigned char *kmallocmem2;   
unsigned char *kmallocmem3;  
unsigned char *kmallocmem4;

static int __init mem_module_init(void)  
{   // 分配1KB的内存给kmallocmem1
    kmallocmem1 = kmalloc(1024, GFP_KERNEL); 

    if (!kmallocmem1) {
        printk(KERN_ALERT "Failed to allocate memory for kmallocmem1\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "kmallocmem1 pointer: %p\n", kmallocmem1);

    // 分配8KB的内存给kmallocmem2
    kmallocmem2 = kmalloc(8192, GFP_KERNEL); 

    if (!kmallocmem2) {
        printk(KERN_ALERT "Failed to allocate memory for kmallocmem2\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "kmallocmem2 pointer: %p\n", kmallocmem2);
    // 释放kmallocmem1和kmallocmem2
    kfree(kmallocmem2);
    kfree(kmallocmem1);
    // 使用二分法求解出可分配内存大小的上限
    size_t l = 0,r = (size_t)-1
    while (l < r){
        size_t mid = (l+r) >> 1;
        if (l+r % 2)    mid += 1;
        // 分配mid字节给kmallocmem3
        kmallocmem3 = kmalloc(mid, GFP_KERNEL);
        if (!kmallocmem3){
            r = mid-1;
        }
        else {
            kfree(kmallocmem3);
            l = mid;
        }
    }
    printk(KERN_INFO "The max size to malloc is: %zu\n", )
    /*
    kmallocmem3 = kmalloc((size_t)-1, GFP_KERNEL); // 分配允许的最大内存大小给kmallocmem3
    if (!kmallocmem3) {
        printk(KERN_ALERT "Failed to allocate memory for kmallocmem3\n");
        return -ENOMEM;
    }

    kmallocmem4 = kmalloc((size_t)-1, GFP_KERNEL); // 分配超过允许的最大内存大小给kmallocmem4
    if (!kmallocmem4) {
        printk(KERN_ALERT "Failed to allocate memory for kmallocmem4\n");
        kfree(kmallocmem3);
        kfree(kmallocmem2);
        kfree(kmallocmem1);
        return -ENOMEM;
    }

    printk(KERN_INFO "Memory allocation successful\n");
    */
    return 0;  
}

static void __exit mem_module_exit(void)  
{  
    printk(KERN_INFO "Memory deallocation successful\n");
}

module_init(mem_module_init);  
module_exit(mem_module_exit);
