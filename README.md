# Linux-Support-Process-Weights

## Linux Support for Process Weights (System call) from Userspace

### System Calls for Weights:
##### - set_weight:
   - syscall number: 334
   - Purpose:    change the weight of the current process to the given argument
   - Parameters: weight - a non-negative integer
   - Return:     on success - 0, otherwise - -EINVAL (the specified weight is negative)
##### - get_weight:
   - syscall number: 335
   - Purpose:    return the weight of the current process
   - Parameters: none
   - Return:     the weight of the current process
##### - get_leaf_children_sum:
   - syscall number: 336
   - Purpose:    returns the sum of the weights of all the current process leaf descendants
recursively
   - Parameters: none
   - Return:     on success - returns the sum of the weights of all the current process leaf descendants, otherwise - -ECHILD (current process does not have any un-waited children)
##### - get_heaviest_ancestor:
   - syscall number: 337
   - Purpose:    returns the process id of the ancestor of the current process with the heaviest
weight among all the current process’s ancestors (including itself)
   - Parameters: none
   - Return:     the process id of the ancestor of the current process with the heaviest
weight


### What are Process Weights?
- Each process hold a non-negative integer - *weight*
- The init process will have a weight of 0 by default
- When a process is forked, the child process should inherit its parent’s weight
- The user can change the current process weight


### Download:
    git clone https://github.com/Almogbs/Linux-Support-Process-Weights.git

### Installation:
    cp -a Linux-Support-Process-Weights/ {YOUR FORKED LINUX}/
    cd {YOUR FORKED LINUX}
    make -j $(nproc)
    sudo cp -f arch/x86/boot/bzImage /boot/vmlinuz-4.15.18-custom
    sudo reboot
    
### Usage Example (Userspace):
    /** file.c **/
    int main() {
      
      // print the weight of the current process
      printf("The weight of the current process: %d\n", get_weight());
      
      // check if the syscall return success
      if (set_weight(84) != 0) {
        printf("Weight must be non-negative integer\n");
        return 0;
      }
      
      // print the weight of the current process after the change
      printf("The new weight of the current process: %d\n", get_weight());
      
      return 0;
    }
    
##### output:
      0
      84
 
