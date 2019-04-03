# Imports
import os
import sys
import optparse

def run_test(graph, test, diff, mem):

    # Command for performance and penazzi test
    command = ['make ' + test, 'GRAPHS=', 'SWITCH=', 'RMBC=', 'INPUT=', 'OUTPUT=', 'OFLAG=']

    # Arguments for command
    gr, sw, rm, inp, out, ans = "", "", "", 'samples/' + test + '/' + graph, 'out/' + test + '/' + graph, 'ans/' + test + '/' + graph

    # Important files
    ansfile, outfile = None, None

    # Check that inputfile exits
    if not os.path.isfile(inp):
        print("Graph " + graph + " does not exist")
        exit(0)
    
    # We open ansfile
    try:
        ansfile = open(ans, 'r')
    except IOError:
        print("Answer file for " + graph + " not found.")
        exit(0)

    # Create the paths out/$(test)/graph
    if not os.path.isdir('out/' + test):
        os.mkdir('out/' + test)
    if not os.path.isfile(out):
        os.mknod(out)
    if mem and not os.path.isdir('out/memory'):
        os.mkdir('out/memory')


    # Open output file
    outfile = open(out, 'r')

    #if memory read graphs too
    if test == 'memory':
        try:
            gr, sw, rm = ansfile.readline().split()
        except ValueError:
            print("Answer file has wrong format, 'sw rm' needed")
            exit(0)
    else:
        try:
            sw, rm = ansfile.readline().split()
        except ValueError:
            print("Answer file has wrong format, 'sw rm' needed")
            exit(0)

    # Make arguments
    args = [gr, sw, rm, inp, out]

    # Merge command with arguments
    for i in range(1, len(command) - 1):
        command[i] += args[i - 1]

    if diff:
        command[-1] += '-DHARD'

    if mem or test == 'memory':
        command[0] += '.v'

    # Convert command to string
    command = ' '.join(command)

    # Launch command
    os.system(command)

    # What have we done?
    message = 'Runned ' + test + ' test with ' + sw + ' switches and ' + rm + ' RMBCs'
    print(message)

    # Collect data depending on test
    if 'penazzi' == test:
        ansline = ansfile.readline()
        outline = outfile.readline()
        checks = ['GREEDY\n', 'WELSH\n', 'SWITCH\n', 'RMBC\n']
        expected = []
        given = []
        while ansline and outline:
            expected.append(ansline)
            given.append(outline)
            ansline, outline = ansfile.readline(), outfile.readline()
        for i in range (0, 4):
            checks[i] += 'Expected: ' + expected[i] + 'Given: ' + given[i]
        checks = '\n'.join(checks)
        print(checks)
    
    if 'performance' == test:
        print('Time spent creating graph: ' + outfile.readline())
        next(outfile)
        print('Time spent running Natural: ' + outfile.readline())
        next(outfile)
        print('Time spent running Welsh: ' + outfile.readline())
        next(outfile)
        print('Time spent running Switch: ' + outfile.readline())
        next(outfile)
        print('Time spent running RMBC: ' + outfile.readline())
        print('Time spent destroying graph: ' + outfile.readline())
        print('Penazzi time: ' + ansfile.readline())
        print('Your time: ' + outfile.readline())
    
    if 'memory' == test or mem:
        vfile = open('out/memory/' + graph, 'r')
        for line in vfile:
            if 'total heap usage' in line:
                info = line
                break
        print(info[11:])
        vfile.close()
    
    # Close files
    ansfile.close()
    outfile.close()

def valid(str):
    if str == 'penazzi':
        return True
    elif str == 'performance':
        return True
    elif str == 'memory':
        return True

def main():
    """
    Interfaz simple para correr los tests y obtener los resultados
    """
    # Crea los directorios si no existen.
    if not os.path.isdir('bin'):
        os.mkdir('bin')
    if not os.path.isdir('obj'):
        os.mkdir('obj')
    if not os.path.isdir('out'):
        os.mkdir('out')

    # Parsear argumentos-
    parser = optparse.OptionParser(usage="%prog [options] test graph")
    parser.add_option("-t", "--test",
                      help="Run tests with hard difficulty", action="store_true", default=False, dest="diff")
    parser.add_option("-v", "--valgrind",
                      help="", action="store_true", default=False, dest="mem")
    options, args = parser.parse_args()

    if(len(args) != 2):
        print("Usage: run.py [options] test graph")
        exit(0)

    test, graph = args
    if valid(test):
        run_test(graph, test, options.diff, options.mem)
    else:
        print("Wrong test name")
        print("Available tests are penazzi, performance and memory")
    
    #os.system('make clean')
    exit(0)

if __name__ == '__main__':
    main()

