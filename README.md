Introduction
========
The job-shop problem (abbreviated JSP) is an NP-hard problem in combinatorial optimisation.
In JSP we consider m machines on a production line with n defined jobs; each job consists of different tasks for any of the machines and each of them has its own duration t[i]. The goal is to find the shortest scheduling in which none of the jobs' tasks collide on all of the m machines.

The NP-hardness can be proved using travelling salesman problem (TSP) transforming JSP into it (knowing TSP is NP-hard too, of course): the salesman becomes a machine from JSP and cities become jobs.

Project description
========
The aim of the project (written for Combinatorial Optimisation laboratory) is to show two ways of dealing with NP-hardness: heuristics (giving results that are not the best ones but valid) and BB (branch and bound)/metaheuristics for getting results with better quality.
The source code is written in C++ and can be distrubuted under GPL v3.0 license: http://www.gnu.org/licenses/gpl-3.0.txt

Compilation
========
The easy Linux way:

make

the easy Windows way:

g++ src/job.cpp src/scheduler.cpp src/task.cpp src/main.cpp -o job-shop

the hard Windows way:

g++ src/job.cpp -o job.o
g++ src/scheduler.cpp -o scheduler.o
g++ src.cpp/task.cpp -o task.o
g++ src/main.cpp -o main.o
g++ -o bin/job-shop job.o scheduler.o task.o main.o
