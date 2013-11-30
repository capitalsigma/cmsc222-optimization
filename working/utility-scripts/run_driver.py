#! /usr/bin/python3
from sys import argv
from multiprocessing import Pool
import time
import datetime
import subprocess


USAGE = '''{} executable #runs'''

ENTRY_FORMAT = "%H:%M:%S"
FILE_NAME_FORMAT = "%m-%d-{}.log".format(ENTRY_FORMAT)
POOL_SIZE = 50


def make_timestamp(fmt):
    return datetime.datetime.fromtimestamp(time.time()).strftime(fmt)


def set_file_name(ex_path):
    return "{}{}".format(ex_path, make_timestamp(FILE_NAME_FORMAT))


def run_timestamp():
    return make_timestamp(ENTRY_FORMAT)


def do_run(n):
    return subprocess.check_output((ex_path)).decode()


def header(ex_path):
    return

ex_path, runs = argv[1:]
f = open(set_file_name(ex_path), "w")
p = Pool(POOL_SIZE)
ans = p.map(do_run, range(0, int(runs)))
f.write('\n'.join(ans))
