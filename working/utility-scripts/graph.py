#! /usr/bin/python3

import os
import re


def parse_entry(entry, regex):
    # print(entry)
    m = None
    for line in entry.split('\n'):
        m = regex.match(line)
        if m:
            break
    # print(m.groups())
    t = m.groups()
    return ".".join(t)


def parse_file(file_handle):
    entries = file_handle.read().split('\n\n')
    regex = re.compile("(?:User CPU time: )?(\d+) s, (\d+) us")
    # print("Processing: ", entries)
    # print(len(entries))
    return [float(parse_entry(entry, regex)) for entry in entries]


def print_avg(results):
    print("Averages:")
    to_print = {f:sum(v)/len(v) for f, v in results.items()}
    for key, value in to_print.items():
        print("{}: {} s".format(key, value))


def main():
    results = {}
    for root, dirs, files in os.walk('.//runs'):
        for f in files:
            # print(f)
            if re.search(r'.log\Z', f):
                # print("good")
                results[f] = parse_file(open(os.path.join(root, f)))

    print_avg(results)
    return results

main()
