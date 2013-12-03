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
    return ".".join([t[0], t[1].zfill(9)])


def parse_file(file_handle):
    entries = file_handle.read().split('\n\n')
    regex = re.compile("Wall time: (\d+) s, (\d+) ns")
    # print("Processing: ", entries)
    # print(len(entries))
    return [float(parse_entry(entry, regex)) for entry in entries]


def stats_of(vals):
    stddev = numpy.std(vals)
    avg = sum(vals)/len(vals)
    med = numpy.median(vals)
    return "{:.4f} s,{:.4f} s,{:.4f} s".format(avg, med, stddev)


def format_filename(filename):
    els = filename.split(".out")[0].split("-")
    algo_name  = " ".join(els[:2] + [els[-1] if els[-1].isdigit() else ""])
    size = list(filter(lambda x: x.isupper(), els))[0]
    return "{},{}".format(algo_name, size.lower())


def format_avgs(results):
    print("Implementation,Size,Average,Median,Standard Deviation")
    to_print = {f: "{}".format(stats_of(v)) for f, v in results.items()}
    out_strs = ["{},{}".format(format_filename(key), value) for key, value in
                to_print.items()]
    ans = "\n".join(sorted(out_strs,
                           key=lambda x: "".join(x.split(",")[0])))
#    print(ans)
    return ans


def sort_by_size(ans_str):
    to_proc = ans_str[:-1].split("\n")
#    print(to_proc)
    ret = []
    for s in ["verysmall", "small,", ",smaller_medium,",
              ",small_medium,",  ",medium",
              ",large_medium,", "larger_medium",
              "small_large", ",large ", "larger", ",xlarge", "xxlarge"]:
        ret += list(filter(lambda x: s in x, to_proc))
    return "\n".join([ans_str[-1]] + ret)


def main():
    results = {}
    for root, dirs, files in os.walk('.//runs'):
        if not "_" in root:
            for f in files:
                # print(f)
                path = os.path.join(root, f)
                if re.search(r'.log\Z', f) and os.path.getsize(path):
                    # print("good")
                    results[f] = parse_file(open(path))
    comma_sep = format_avgs(results)
    to_print = sort_by_size(comma_sep)
    print(to_print)
    return to_print

main()
