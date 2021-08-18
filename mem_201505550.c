//Fundamental libraries
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

//other libraries
#include <linux/fs.h>
#include <linux/hugetlb.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_AUTHOR("OS2_A2_grupo6");
MODULE_DESCRIPTION("MEMORY MONITOR");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");




static int getmemory(struct seq_file *m, void *v)
{
    struct sysinfo i;
    unsigned long pages[NR_LRU_LISTS];
    int lru;
    #define K(x) ((x) << (PAGE_SHIFT - 10))
        si_meminfo(&i);
        for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++){
            pages[lru] = global_numa_state(NR_LRU_BASE + lru);
        }       
        seq_printf(m, "\n***************MEMORIA*******************\n");
        seq_printf(m, "TOTAL: %8lu kB\n",K(i.totalram));
        seq_printf(m, "LIBRE: %8lu kB\n",K(i.freeram));
        seq_printf(m, "USADA: %8lu kB\n",K(i.totalram)-K(i.freeram)-K(i.bufferram));
        seq_printf(m, "****************END**********************\n\n");
    #undef K
    return 0;
}

static int memory_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, getmemory, NULL);
}

static const struct proc_ops memory_proc_fops = {
    .proc_open = memory_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

// Main event
static int __init memory_init(void)
{
    struct proc_dir_entry *entry;
    entry = proc_create("mem_201505550", 0, NULL, &memory_proc_fops);

    if(!entry){
        return -1;
    }else{
        printk(KERN_INFO "hola_201612408");
        return 0;
    }
    
}

// exit event
static void __exit memory_exit(void)
{
    
    remove_proc_entry("mem_201505550", NULL);
    printk(KERN_INFO "adios_201505550 \n");
    
}

// this call mounts the init function that will be executed in init
module_init(memory_init);
// this call mounts the exit function that will be executed in exit
module_exit(memory_exit);




