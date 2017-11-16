/*
 * This is a gamepad driver Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <asm/signal.h>
#include <linux/poll.h>
#include <asm/siginfo.h>
#include <linux/signal.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>

#include "efm32gg.h"
#define DEVICE_NAME gamepad

static int gamepad_fasync(int, struct file*, int mode);
static int gamepad_open(struct inode *inode, struct file *filp);
static int gamepad_release(struct inode *inode, struct file *filp);
static ssize_t gamepad_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
static irqreturn_t interrupt_handler(int irq, void  *dev_id, struct pt_regs *regs);

dev_t deviceNumber;
struct fasync_struct* async_queue;
struct cdev *gamepad_cdev;
struct class *cl;

/* Possible file operations for this driver */
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = gamepad_read,
	.open = gamepad_open,
	.release = gamepad_release,
	.fasync = gamepad_fasync,
};

irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs) {
	iowrite32(0xff, GPIO_IFC);
	if (async_queue) {	
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	}
	return IRQ_HANDLED;
}

static int gamepad_fasync(int fd, struct file* filp, int mode) {
	return fasync_helper(fd, filp, mode, &async_queue);
}

/*
 * Function to insert this module into kernel space
 *
 * Returns 0 if successfull, otherwise -1
 */
static int __init gamepad_init(void)
{
	printk("Hello World, here is your module speaking\n");
	
	int err = alloc_chrdev_region(&deviceNumber, 0, 1, "gamepad");

	cdev_init(&gamepad_cdev, &fops);
	gamepad_cdev->owner = THIS_MODULE;
	cdev_add(&gamepad_cdev, deviceNumber, 1);

	cl = class_create(THIS_MODULE, "gamepad");
	device_create(cl, NULL, deviceNumber, NULL, "gamepad");

	request_mem_region(GPIO_PC_BASE, GPIO_IFC - GPIO_PA_BASE, "gamepad");
		
	/* Configure GPIO input and interrupts */
	iowrite32(0x33333333, GPIO_PC_MODEL);
	iowrite32(0xff, GPIO_PC_DOUT);
	iowrite32(0x22222222, GPIO_EXTIPSELL);
	iowrite32(0xff, GPIO_EXTIRISE);
	iowrite32(0xff, GPIO_EXTIFALL);
	iowrite32(0xff, GPIO_IEN);
	
	request_irq(17, (irq_handler_t) interrupt_handler, 0, "gamepad", &gamepad_cdev);
	request_irq(18, (irq_handler_t) interrupt_handler, 0, "gamepad", &gamepad_cdev);
	

	if (err < 0)  {
		printk(KERN_ERR "Failed to activate char device.\n");
	}
	return 0;
}

/*
 * Function to cleanup this module from kernel space
 */
static void __exit gamepad_cleanup(void)
{
	cdev_del(&gamepad_cdev);

	free_irq(17, &gamepad_cdev);
	free_irq(18, &gamepad_cdev);
	
	release_mem_region(GPIO_PC_BASE, GPIO_IFC - GPIO_PA_BASE);
	
	device_destroy(cl, deviceNumber);
	class_destroy(cl);
	
	unregister_chrdev_region(deviceNumber, 1);
}

static int gamepad_open(struct inode *inode, struct file *filp) {
	return 0;
}

static int gamepad_release(struct inode *inode, struct file *filp) {
	
	return 0;
}

static ssize_t gamepad_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
	uint32_t data = ioread32(GPIO_PC_DIN);
	copy_to_user(buff, &data, 1);
	return 1;
}


module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");
