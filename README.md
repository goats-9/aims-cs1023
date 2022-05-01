# aims-cs1023
Submission for implementation of AIMS portal for CS1023 at IITH

# Installation
This program works only on Linux/macOS. If you're on Windows, get a VM. To install, open a terminal window, and type:

```git clone https://github.com/goats-9/aims-cs1023.git```

Then, to install or reinstall, type

```sh install.sh```

To reset the database only, type

```sh clean.sh```

To remove the program and database, type

```sh uninstall.sh```

To remove the whole cloned repo on your local system, type

```sh clean_uninstall.sh```

# Documentation
Mini-AIMS uses a filesystem and various integrity checks to prevent data redundancy and enhance data security in case of bad inputs. 

## User IDs, Course Codes and Passwords
1. User IDs must be of the following templates:
a. Students: <Branch Abbreviation in Capitals><Last two digits of year of joining>BTECH<5-digit ID> (e.g. CS21BTECH11018)
b. Faculty: <Branch Abbreviation in Capitals><Last two digits of year of joining>_F<3-digit ID> (e.g. CS12_F002)
c. Admin: <Branch Abbreviation in Capitals><Last two digits of year of joining>_A<3-digit ID> (e.g. CS12_A002)
2. Course codes must be a string of 6 characters, of the form <Branch Abbreviation>ABBC, where:
a. A denotes the year (from 1 to 5, for UG) when the course is offered.
b.
The various functionalities that can be done by a student, faculty, or admin appear as a list each time you have to input a number for performing the operation.

# Acknowledgements
I would like to thank the course instructor Dr. M. V. Panduranga Rao, Faculty Advisor, Computer Science and Engineering, IIT Hyderabad, for giving me this wonderful opportunity to have a crack at learning the rudimentary principles of developing reliable, solid and secure software.
