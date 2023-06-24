#!/bin/bash

sshpass -p "student" ssh student@192.168.10.2 
sshpass -p scp ./src/cat/s21_cat student@192.168.10.2:/usr/local/bin/
sshpass -p scp ./src/grep/s21_grep student@192.168.10.2:/usr/local/bin/ 
