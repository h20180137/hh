#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
static dev_t first;
static struct cdev c_dev;
static struct class *cls;
static int my_open(struct inode *i,struct file *f)
{
printk(KERN_INFO "mychar:open()\n");
return 0;
}
static int my_close(struct inode *i,struct file *f)
{
printk(KERN_INFO "mychar:close()\n");
return 0;
}
static ssize_t my_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "mychar:read()\n");
return 0;
}
ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
printk(KERN_INFO "mychar:write()\n");
return 0;
}


//ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);


static struct file_operations fops =
{
.owner=THIS_MODULE,
.open=my_open,
.release=my_close,
.read=my_read,
.write=my_write
};
//static 
//4step

static char *mystr="chai peelo frnds";
static int a=1234;
module_param(mystr,charp,0);
module_param(a,int,0);
MODULE_PARM_DESC(a,"ganta");
//MODULE_PARM_DESC(mystr,"panta");


static __init int demo_init(void)
{
printk(KERN_INFO "my char registered\n\n");
if((alloc_chrdev_region(&first,0,1,"lol"))<0) return -1;


if((cls=class_create(THIS_MODULE,"chardev"))==NULL)
{
unregister_chrdev_region(first,3);
return -1;
}
if((device_create(cls,NULL,first,NULL,"kya"))==NULL)
{
class_destroy(cls);
unregister_chrdev_region(first,1);
return -1;
}
cdev_init(&c_dev,&fops);
if(cdev_add(&c_dev,first,1)==1)
{
device_destroy(cls,first);
class_destroy(cls);
unregister_chrdev_region(first,1);
return -1;
}
return 0;

}
static __exit void demo_exit(void)
{
//printk(KERN_ALERT "BYE WORLD\n");
cdev_del(&c_dev);
device_destroy(cls,first);
class_destroy(cls);
unregister_chrdev_region(first,1);
printk(KERN_INFO "my char nregistered\n\n");
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_DESCRIPTION("lULWA");
MODULE_AUTHOR("KONWA");
MODULE_LICENSE("GPL");
MODULE_INFO(SupportedChips,"laal,baal,paal");
