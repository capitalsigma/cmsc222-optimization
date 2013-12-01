#! /usr/bin/python3
import csv
import matplotlib
import numpy
import os
import re

def main(path):
    r = csv.DictReader(open(path))
    ans = {}
    for line in r:
        if not ans[line['Implementation']]:
            ans[line['Implementation']] = {}
        ans[line['Implementation']] = ([line['size]'], line['Average']])
        

