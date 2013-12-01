#! /usr/bin/python3
import csv
import matplotlib.pyplot


def plot_series(algo_dict, ax, color):
    for algo_name, stats in series_dict.items():
        ax.bar(stats['Average'], 


def parse_file(r):
    ans = {}
    for line in r:
        try:
            ans[line['Size']]
        except KeyError:
            ans[line['Size']] = {}

        ans[line['Size']][line['Implementation']] = {
            'Average': line['Average'],
            'StdDev': line['Standard Deviation'],
        }


    return ans



def make_graph(d):
    names = [size.keys() for size in d]
    fig, ax = matplotlib.pyplot.subplots()
    for size, algos in d.items(), :
        plot_series(algos, ax)
    

def main(path):
    r = csv.DictReader(open(path))
    stats = parse_file(r)
    
    make_graph(stats)
    return stats



main("bsort.csv")
