Simple Linux /proc Read & Write Kernel Module
=============================================

This project demonstrates a minimal Linux kernel module that creates a custom file inside the /proc filesystem.
It supports both read and write operations:

  ```
  echo "message" > /proc/my_driver   # Writes message to the kernel module
  cat /proc/my_driver                # Reads message back from kernel space
```

STEP 1: Install Required Packages
------------

- Linux kernel 5.15+ (tested on Ubuntu 22.04)
- Kernel headers:
  
  ```
    sudo apt update
    sudo apt install build-essential linux-headers-$(uname -r)
  ```
  


STEP 2: Clone the Repository
--------------------

    git clone https://github.com/darshilshah7070/linux_read_write_driver.git
    cd linux_read_write_driver


STEP 3: Build the Kernel Module
----------------

    make

This will generate:
- my_driver.ko       -> the kernel module
- my_driver.o        -> object file
- my_driver.mod*     -> build metadata files


STEP 4: (Optional) Disable Secure Boot if Needed
-------------------------------

Note: Secure Boot must be disabled to load unsigned kernel modules.

If you see this error:
    Lockdown: insmod: unsigned module loading is restricted

Then:
    Reboot your system, enter BIOS/UEFI, and disable Secure Boot.


STEP 5: Insert the Kernel Module
------------------------

    sudo insmod my_driver.ko
    dmesg | tail

Expected output:

    my_driver: /proc/my_driver created

Check that the file exists:

    ls -l /proc/my_driver


STEP 6: Write to /proc Interface
------------------------

    echo "Hello from user space!" | sudo tee /proc/my_driver

STEP 7: Read from /proc Interface
-------------------------

    cat /proc/my_driver

Expected output:

    Hello from user space!


STEP 8: Check Kernel Logs
-----------------

    dmesg | tail

Example log:

    my_driver: received message: Hello from user space!


STEP 9: Remove the Kernel Module
-----------------

    sudo rmmod my_driver
    dmesg | tail

Expected output:

    my_driver: /proc/my_driver removed

Verify removal:

    ls /proc/my_driver
    # Should say: No such file or directory


Summary
-------

- "echo" writes a string to /proc/my_driver (into kernel space)
- "cat" reads the stored string from the kernel
- Kernel logs show each write using dmesg
- Module can be removed cleanly, deleting the /proc entry
