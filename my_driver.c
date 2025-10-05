#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "my_driver"
#define BUF_LEN 256

static char message[BUF_LEN] = "HEHE";//it will be overwritten
static size_t message_len = 0;

/* ---------- READ FUNCTION ---------- */
static ssize_t my_driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    return simple_read_from_buffer(buf, count, ppos, message, message_len);
}

/* ---------- WRITE FUNCTION ---------- */
static ssize_t my_driver_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    if (count >= BUF_LEN)
        return -EINVAL;

    if (copy_from_user(message, buf, count))
        return -EFAULT;

    message[count] = '\0';
    message_len = count;

    pr_info("my_driver: received message: %s\n", message);
    return count;
}

/* ---------- FILE OPERATIONS ---------- */
static const struct proc_ops my_driver_fops = {
    .proc_read  = my_driver_read,
    .proc_write = my_driver_write,
};

/* ---------- MODULE INIT ---------- */
static int my_driver_init(void)
{
    if (!proc_create(PROC_NAME, 0666, NULL, &my_driver_fops)) {
        pr_err("my_driver: Failed to create /proc/%s\n", PROC_NAME);
        return -ENOMEM;
    }
    pr_info("my_driver: /proc/%s created\n", PROC_NAME);
    return 0;
}

/* ---------- MODULE EXIT ---------- */
static void my_driver_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    pr_info("my_driver: /proc/%s removed\n", PROC_NAME);
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darshil Shah");
MODULE_DESCRIPTION("Simple /proc driver with read & write");

