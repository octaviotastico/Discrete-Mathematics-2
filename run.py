# Imports
import os
import sys
import optparse

def run_test(graph, test, mode):
    # Command for performance and penazzi test
    command = ['make ' + test, 'SWITCH=', 'RMBC=', 'INPUT=', 'OUTPUT=', 'OFLAG=']

    # Arguments for command
    sw, rm, inp, out, ans = None, None, 'samples/' + test + '/' + graph, 'out/' + test + '/' + graph, 'ans/' + test + '/' + graph

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

    # Create the paths out/$(test)/graph, bin and obj
    if not os.path.isdir('out'):
        os.mkdir('out')
    if not os.path.isdir('out/' + test):
        os.mkdir('out/' + test)
    if not os.path.isfile(out):
        os.mknod(out)
    if not os.path.isdir('bin'):
        os.mkdir('bin')
    if not os.path.isdir('obj'):
        os.mkdir('obj')

    # Open output file
    outfile = open(out, 'r')

    # Read SWITCH and RMBC
    try:
        sw, rm = ansfile.readline().split()
    except ValueError:
        print("Answer file has wrong format, 'sw rm' needed")
        exit(0)

    # Make arguments
    args = [sw, rm, inp, out]

    # Merge command with arguments
    for i in range(1, len(command) - 1):
        command[i] += args[i - 1]

    if(mode):
        command[-1] += '-DHARD'

    # Convert command to string
    command = ' '.join(command)

    # Launch command
    os.system(command)

    # What have we done?
    message = 'Runned ' + test + ' test with ' + sw + ' switches and ' + rm + ' RMBCs'
    print(message)

    # Collect data depending on test
    if test == 'penazzi':
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
    else:
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

    # Close files
    ansfile.close()
    outfile.close()


def main():
    """
    Interfaz simple para correr los tests y obtener los resultados
    """

    # Parsear argumentos
    parser = optparse.OptionParser(usage="%prog [options] test graph")
    parser.add_option("-t", "--test",
                      help="Run tests with hard difficulty", action="store_true", default=False, dest="diff")
    options, args = parser.parse_args()

    if(len(args) != 2):
        print("Usage: run.py [options] test graph")
        exit(0)

    test, graph = args
    if test == 'penazzi' or test == 'performance':
        run_test(graph, test, options.diff)
    elif test == 'memory':
        pass
    else:
        print("Wrong test name")
        print("Available tests are penazzi, performance and memory")
    
    exit(0)

if __name__ == '__main__':
    main()

