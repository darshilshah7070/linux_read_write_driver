Simple Linux Read & Write /proc Driver
======================================

This project demonstrates a minimal Linux kernel module that creates a custom file inside the /proc filesystem.
It supports both read and write operations:

- echo "message" > /proc/my_driver   -> writes a message into the kernel buffer
- cat /proc/my_driver                -> reads back the same message from kernel space


-------------------------------------------------
Step 1: Requirements
-------------------------------------------------
- Linux kernel 5.15+ (tested on Ubuntu 22.04)
- Kernel headers installed:
  
  sudo apt update
  sudo apt install build-essential linux-headers-$(uname -r)

- make and gcc toolchain installed

-------------------------------------------------
Step 2: Clone the Repository
-------------------------------------------------

git clone https://github.com/darshilshah7070/linux_read_write_driver.git
cd my_driver

-------------------------------------------------
Step 3: Build the Driver
-------------------------------------------------

Run:
  make

This will generate:
- my_driver.ko  -> the kernel module
- my_driver.o   -> object file
- my_driver.mod* files -> build metadata

-------------------------------------------------
Step 4: Handle Secure Boot (Important!)
-------------------------------------------------
If Secure Boot is enabled, unsigned modules cannot be loaded.

Solution:
- Reboot, enter BIOS/UEFI, and disable Secure Boot.

If you see this error:
  Lockdown: insmod: unsigned module loading is restricted
→ Secure Boot is still enabled.

-------------------------------------------------
Step 5: Insert the Module
-------------------------------------------------

sudo insmod my_driver.ko
dmesg | tail

Expected message:
  my_driver: /proc/my_driver created

Check that the file exists:
  ls -l /proc/my_driver

-------------------------------------------------
Step 6: Write Data into /proc
-------------------------------------------------

echo "Hello from user space!" | sudo tee /proc/my_driver

-------------------------------------------------
Step 7: Read Data Back
-------------------------------------------------

cat /proc/my_driver

Expected output:
  Hello from user space!

-------------------------------------------------
Step 8: Verify Kernel Logs
-------------------------------------------------

dmesg | tail

Example:
  my_driver: received message: Hello from user space!

-------------------------------------------------
Step 9: Remove the Module
-------------------------------------------------

sudo rmmod my_driver
dmesg | tail

Expected message:
  my_driver: /proc/my_driver removed

Check that file is gone:
  ls /proc/my_driver
  (should show: No such file or directory)

-------------------------------------------------
Summary
-------------------------------------------------
- "echo" writes a string to kernel space via /proc/my_driver
- "cat" reads the stored string from kernel space
- Kernel log (dmesg) shows messages when writing
- Clean removal deletes /proc/my_driver

