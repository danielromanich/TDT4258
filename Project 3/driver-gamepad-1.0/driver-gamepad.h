static int gamepad_fasync(int, struct file*, int mode);
int gamepad_open(struct inode *inode, struct file *filp);
int gamepad_release(struct inode *inode, struct file *filp);
ssize_t gamepad_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
loff_t gamepad_llseek(struct file *filp, loff_t off, int);
int gamepad_mmap(struct file *filp, struct vm_area_struct *vmarea);
irqreturn_t interrupt_handler(int irq, void  *dev_id, struct pt_regs *regs);
