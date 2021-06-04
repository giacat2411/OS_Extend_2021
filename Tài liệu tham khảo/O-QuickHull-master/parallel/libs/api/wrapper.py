import ctypes
import struct
import os
import csv
import warnings

ARCHITECTURE = struct.calcsize("P") * 8
OS_SHARED = 'dll' if os.name == 'nt' else 'so'

def findOrthogonalConvexHull(input_file_name, output_file_name):
    warnings.warn('unknown bug, use runnable instead')
    lib = ctypes.cdll.LoadLibrary('./{}/OrthogonalConvexHull_x{}.{}'.format(OS_SHARED, ARCHITECTURE, OS_SHARED))
    input_file = ctypes.create_string_buffer(bytes(input_file_name, encoding='ascii'))
    output_file = ctypes.create_string_buffer(bytes(output_file_name, encoding='ascii'))

    lib.findOrthogonalConvexHull(input_file, output_file)

    return read(output_file_name)

def findOrthogonalConvexHull_runable(input_file_name, output_file_name):
    EXECUTABLE = '.exe' if os.name == 'nt' else ''
    COMM = '.\\{}\\runnable_x{}{} {} {}' if os.name == 'nt' else './{}/runnable_x{}{} {} {}'

    os.system(COMM.format(OS_SHARED, ARCHITECTURE ,EXECUTABLE, input_file_name, output_file_name))
    return read(output_file_name)

def read(file_name):
    input_points = []
    with open(file_name) as f:
        csv_reader = csv.reader(f, delimiter=",")
        for row in csv_reader:
            input_points = input_points + [[float(row[0]), float(row[1])]]
    return input_points
