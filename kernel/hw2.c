#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>

// our code
int recursiveWeights(struct task_struct *curr) {
    int res = 0;
    struct list_head* iter;
    if (list_empty(&curr->children)) {
        return curr->weight;
    }

    list_for_each(iter, &curr->children) {
        res += recursiveWeights(list_entry(iter, struct task_struct, sibling));
    }
    return res;
}

asmlinkage long sys_hello(void) {
    printk("Hello, World!\n");
    return 0;
}

asmlinkage long sys_set_weight(int weight) {
    if (weight < 0) {
        return -EINVAL;
    }
    current->weight = weight;
    return 0;
}

asmlinkage long sys_get_weight(void) {
    return current->weight;
}

asmlinkage long sys_get_leaf_children_sum(void) {
    if (list_empty(&current->children)) {
        return -ECHILD;
    }

    return recursiveWeights(current);
}

asmlinkage long sys_get_heaviest_ancestor(void){
    int max_weight = current->weight;
    pid_t max_weight_pid = current->pid;
    struct task_struct* iter = current;
    while(iter->pid != 0) {
        if (iter->weight > max_weight) {
            max_weight = iter->weight;
            max_weight_pid = iter->pid;
        }
        iter = iter->parent;
    }
    return max_weight_pid;
}


