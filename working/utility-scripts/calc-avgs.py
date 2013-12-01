#! /usr/bin/python3
import os
import re
import numpy


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


def stats_of(vals):
    stddev = numpy.std(vals)
    avg = sum(vals)/len(vals)
    med = numpy.median(vals)
    return "{:.4f} s,{:.4f} s,{:.4f} s".format(avg, med, stddev)


def format_filename(filename):
    algo_name, size = filename.split(".out")[0].rsplit("-", 1)
    return "{},{}".format(algo_name.replace("-", " "), size.lower())


def print_avg(results):
    print("Implementation,Size,Average,Median,Standard Deviation")
    to_print = {f:"{}".format(stats_of(v)) for f, v in results.items()}
    out_strs = ["{},{}".format(format_filename(key), value) for key, value in
                to_print.items()]
    print("\n".join(sorted(out_strs,
                           key=lambda x: "".join(x.split(",")[0]))))


def main():
    results = {}
    for root, dirs, files in os.walk('.//runs'):
        for f in files:
            # print(f)
            path = os.path.join(root, f)
            if re.search(r'.log\Z', f) and os.path.getsize(path):
                # print("good")
                results[f] = parse_file(open(path))

    print_avg(results)
    return results

main()
