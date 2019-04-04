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
            print("Answer file has wrong format, 'gr sw rm' needed")
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

    if mem:
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
        checks = ['GREEDY\n', 'WELSH\n', 'SWITCH\n', 'RMBC\n', 'Bipartito\n']
        expected = []
        given = []
        while ansline and outline:
            expected.append(ansline)
            given.append(outline)
            ansline, outline = ansfile.readline(), outfile.readline()
        for i in range (0, 5):
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
        next(outfile)
        print('Time spent running Bipartito: ' + outfile.readline())
        print('Time spent destroying graph: ' + outfile.readline())
        print('Penazzi time: ' + ansfile.readline())
        print('Your time: ' + outfile.readline())
    
    if 'memory' == test or mem:
        vfile = open('out/memory/' + graph, 'r')
        for line in vfile:
            if 'HEAP SUMMARY' in line:
                info = line
                break
        nextl = vfile.readline()
        while nextl: # Search the first char
            i = 9
            while info[i] == ' ':
                i += 1
            print(info[i:])
            info = vfile.readline()
            nextl = vfile.readline()
        
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
                      help="Run tests with valgrind", action="store_true", default=False, dest="mem")
    
    options, args = parser.parse_args()

    diff = '.difficulty'

    if not os.path.isfile(diff):
        os.mknod(diff)
        d = open(diff, 'w')
        d.write('EASY')
        d.close()

    # Read difficulty
    diffile = open(diff, 'r')
    mode = diffile.readline()
    diffile.close()

    # Change it if necessary, and do make clean
    if 'EASY' in mode and options.diff:
        os.system('make clean')
        diffile = open(diff,'w')
        diffile.write('HARD')
        diffile.close()
    elif 'HARD' in mode and not options.diff:
        os.system('make clean')
        diffile = open(diff,'w')
        diffile.write('EASY')
        diffile.close()

    # Load the arguments in the variables
    # if args[1] == 'memory': gr sw rm
    test, graph = args

    # Check if the arguments are valid
    # if test == 'memory' and len(args) != 3:
    #     print("Usage: run.py [options] test graph")
    #     exit(0)
    if len(args) != 2:
        print("Usage: run.py [options] test graph")
        exit(0)

    if valid(test):
        run_test(graph, test, options.diff, options.mem)
    else:
        print("Wrong test name")
        print("Available tests are penazzi, performance and memory")
    
    #os.system('make clean')
    exit(0)

if __name__ == '__main__':
    main()

