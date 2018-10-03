Assignment 2 - Linux-style shell
==============================

## NOTE:
* The code for this assignment was written by me, but the assignment was originally created by Mike Gosnell @ MST

# Description
This assignment will emulate core functionality of a Linux-style shell with respect to managing a file system.
Your primary job is to develop data structures and algorithms for managing files and folders such that a user can interact with a limited set of commands via a command-line familiar to users of Linux.
You need NOT actually create files or folders or in any way manipulate data in a real file system – this assignment focuses on the management aspect only.

Interaction should be fairly close to the standard Linux behavior but need not be 100% identical.
The core functionality required will be documented below and highlights the creation, deletion, and modification of files and folders.
You may choose to add additional features such as persistence (storing the data in some way so the program can start up with the data entered previously), populating with an initial Linux-like structure, etc.

At this point things like users and groups can be arbitrarily assigned (you could own everything if you like).
However, the timestamps and permissions need to be working as expected.
That means the chmod command needs to update permissions and the creation/modification (via touch) should set the timestamp to the local system time/date.

## Commands to Support
* ls
* ls -l
* cd
* pwd
* mkdir
* rmdir
* rm
* chmod
* touch (create a file if it doesn't exsist, otherwise update timestamp)
* exit/quit
