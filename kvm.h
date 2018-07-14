#ifndef KVM_H
#define KVM_H

#include <stdint.h>
#include <cstring>

struct vcpu {
    int fd;
    struct kvm_run *kvm_run;
};

struct vm {
    int sys_fd;
    int fd;
    bool stopped;
    struct vcpu vcpu;
};

extern struct vm *current_kvm;

uint32_t kvm_reg_read(struct vm *vm, int id);
void kvm_reg_write(struct vm *vm, int id, uint32_t value);
void kvm_mem_map_ptr(struct vm *vm, uint64_t address, size_t size, uint32_t perms, void *ptr);
uint32_t kvm_run(struct vm *kvm, uint32_t image_addr, void* image_mem, uint32_t image_mem_size, uint32_t stack_addr, uint32_t stack_size, uint32_t start_addr, uint32_t end_addr, uint32_t esp);
void kvm_stop(struct vm *kvm);

#endif // KVM_H
