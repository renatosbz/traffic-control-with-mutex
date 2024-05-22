# Implementing Mutex in C for Traffic Control Simulation

## The Problem:
Create a traffic simulation where two cars (represented by two different threads) try to cross the same junction. 
Implement a mutex to prevent the race condition where the two threads try to access the junction at the same time, as that would lead to a collision.

## Solution:
Code implemented in C using pthreads. The interface function prints the traffic simulation on the console and shows how the traffic works.
The mutex represents a red or green traffic light which prevents cars from coliding when crossing the junction. 
This code was developed for the Operational Systems 1 class at Universidade Católica de Pernambuco in colaboration with @Brenorp and @custafo
