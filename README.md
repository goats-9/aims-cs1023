# aims-cs1023
Submission for implementation of AIMS portal for CS1023 at IITH

# Installation
This program works only on Linux/macOS. It has been tested on Arch Linux and Ubuntu WSL. If you're on Windows, get a VM. To install, open a terminal window, and type:

`$ git clone https://github.com/goats-9/aims-cs1023.git && cd aims-cs1023`

Then, to install or reinstall, type

`$ sh install.sh`

To reset the database only, type

`$ sh clean.sh`

To remove the program and database, type

`$ sh uninstall.sh`

To remove the whole cloned repo on your local system, type

`$ sh clean_uninstall.sh`

# Documentation
Mini-AIMS uses a filesystem and various integrity checks to prevent data redundancy and enhance data security in case of bad inputs. 

## User IDs, Course Codes and Passwords
1. User IDs must be of the following templates:

  * Students: \<Branch Abbreviation in Capitals\>\<Last two digits of year of joining\>BTECH\<5-digit ID\> (e.g. CS21BTECH11018)

  * Faculty: \<Branch Abbreviation in Capitals\>\<Last two digits of year of joining\>\_F\<3-digit ID\> (e.g. CS12\_F002)

  * Admin: AD\<Last two digits of year of joining\>\<3-digit ID\> (e.g. AD12002)

2. Course codes must be a string of 6 characters, of the form \<Branch Abbreviation\>ABBC, where _A_ denotes the year (from 1 to 5, for UG) when the course is offered, _BB_ denotes a unique 2-digit code for that course, _C_ denotes the type of course as follows:
  
  Value of C | Type of Course
  :--------: | :------------:
  0          | Theory
  1          | Lab
  2          | Design
  3          | Theory + Lab
  4          | Design and Tutorial/Lab
  5          | Project/Thesis
  6          | Seminar
    
## Scope and Functionality
This implementation of the student portal focusses on B.Tech courses for durations upto 5 years. The various functionalities that can be done by a student, faculty, or admin appear as a list each time you have to input a number for performing the operation.

## Features
1. Input handlers prevent hacking by safely flushing input stream `stdin` using `getchar`.
2. Data integrity checks set in place to prevent accepting inputs not conforming to templates, and to prevent data repetition and/or redundancy, thereby enhancing data security.
3. Data stored in as minimal a filesystem as possible, making it easy to port and use. Also facilitates views for members of all clearances.
4. Random cryptosecure initial password generation, using `/dev/urandom`. Logins are not persistent, thereby enhancing security at the (minor) cost of convenience.
5. Use of error messages as backtrace stacks 

# Acknowledgements
I would like to thank the course instructor Dr. M. V. Panduranga Rao, Faculty Advisor, Computer Science and Engineering, IIT Hyderabad, for giving me this wonderful opportunity to have a crack at learning the rudimentary principles of developing reliable, solid and secure software.
