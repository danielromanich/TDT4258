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

static int gamepad_fasync(int, struct file*, int mode);
static int gamepad_open(struct inode *inode, struct file *filp);
static int gamepad_release(struct inode *inode, struct file *filp);
static ssize_t gamepad_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
static irqreturn_t interrupt_handler(int irq, void  *dev_id, struct pt_regs *regs);

dev_t deviceNumber;
struct fasync_struct* async_queue;
struct cdev gamepad_cdev;
struct class *cl;

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = gamepad_read,
	.open = gamepad_open,
	.release = gamepad_release,
	.fasync = gamepad_fasync,
};

//The interrupt handler. Tells the processor that the processor that the interrupt has been handled by writing to IFC
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


static int __init gamepad_init(void)
{
	printk("Initializing gamepad module\n");
	
	
	alloc_chrdev_region(&deviceNumber, 0, 1, "gamepad");

	//gamepad_cdev = cdev_alloc();
	//gamepad_cdev->ops = &fops;
	cdev_init(&gamepad_cdev, &fops);
	gamepad_cdev.owner = THIS_MODULE;
	cdev_add(&gamepad_cdev, deviceNumber, 1);

	cl = class_create(THIS_MODULE, "gamepad");
	device_create(cl, NULL, deviceNumber, NULL, "gamepad");

	request_mem_region((int) GPIO_PC_BASE, (int) GPIO_IFC - GPIO_PA_BASE, "gamepad");
		
	//Writing to the registers to setup the interrupts
	iowrite32(0x33333333, GPIO_PC_MODEL);
	iowrite32(0xff, GPIO_PC_DOUT);
	iowrite32(0x22222222, GPIO_EXTIPSELL);
	iowrite32(0xff, GPIO_EXTIRISE);
	iowrite32(0xff, GPIO_EXTIFALL);
	iowrite32(0xff, GPIO_IEN);
	
	//Binds the interrupts to the interrupt handler
	request_irq(17, (irq_handler_t) interrupt_handler, 0, "gamepad", &gamepad_cdev);
	request_irq(18, (irq_handler_t) interrupt_handler, 0, "gamepad", &gamepad_cdev);
	
	return 0;
}

//Cleans up after the module
static void __exit gamepad_cleanup(void)
{
	cdev_del(&gamepad_cdev);

	free_irq(17, &gamepad_cdev);
	free_irq(18, &gamepad_cdev);
	
	release_mem_region((int) GPIO_PC_BASE, (int) GPIO_IFC - GPIO_PA_BASE);
	
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

//Reads the GPIO_PC_DIN register that contains the button data and writes it to the user buffer
static ssize_t gamepad_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
	uint32_t data = ioread32(GPIO_PC_DIN);
	copy_to_user(buff, &data, 1);
	return 1;
}


module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("Module for GPIO gamepad.");
MODULE_LICENSE("GPL");
