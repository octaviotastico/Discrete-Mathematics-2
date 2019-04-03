# Imports
import os
import sys
import optparse

def penazzi(graph, mode):
    # Command for penazzi test
    command = ['make penazzi', 'SWITCH=', 'RMBC=', 'INPUT=', 'OUTPUT=', 'OFLAG=']

    # Arguments for command
    sw, rm, inp, out, ans = None, None, 'samples/penazzi/' + graph, 'out/penazzi/' + graph, 'ans/penazzi/' + graph

    # Important files
    ansfile, outfile = None, None

    # Check that inputfile exits
    if not os.path.isfile(inp):
        print("Graph " + graph + " does not exist")
        exit(0)
    
    # We open ansfile
    try:
        ansfile = open(ans, 'r')
    except OSError:
        print("Answer file for " + graph + " not found.")
        exit(0)

    # Read SWITCH and RMBC
    try:
        sw, rm = ansfile.readline().split()
    except ValueError:
        print("Answer file has wrong format, 'sw rm' needed")
        exit(0)

    # We open outfile, creating it if necessary
    try:
        outfile = open(out, 'r')
    except OSError:
        if not os.path.isdir('out'):
            os.mkdir('out')
        os.mknod(out)

    args = [sw, rm, inp, out]

    for i in range(1, len(command) - 1):
        command[i] += args[i - 1]


    if(mode):
        command[-1] += '-DHARD'

    command = ' '.join(command)

    os.system(command)

    message = 'Runned penazzi test with ' + sw + ' switches and ' + rm + ' RMBCs'

    print(message)
    
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
    ansfile.close()
    outfile.close()

def performance(graph, mode):
    # Command for performance test
    command = ['make performance', 'SWITCH=', 'RMBC=', 'INPUT=', 'OUTPUT=', 'OFLAG=']

    # Arguments for command
    sw, rm, inp, out, ans = None, None, 'samples/performance/' + graph, 'out/performance/' + graph, 'ans/performance/' + graph

    # Important files
    ansfile, outfile = None, None

    # Check that inputfile exits
    if not os.path.isfile(inp):
        print("Graph " + graph + " does not exist")
        exit(0)
    
    # We open ansfile
    try:
        ansfile = open(ans, 'r')
    except OSError:
        print("Answer file for " + graph + " not found.")
        exit(0)

    # Read SWITCH and RMBC
    try:
        sw, rm = ansfile.readline().split()
    except ValueError:
        print("Answer file has wrong format, 'sw rm' needed")
        exit(0)

    # We open outfile, creating it if necessary
    try:
        outfile = open(out, 'r')
    except OSError:
        if not os.path.isdir('out'):
            os.mkdir('out')
        os.mknod(out)

    args = [sw, rm, inp, out]

    for i in range(1, len(command) - 1):
        command[i] += args[i - 1]

    if(mode):
        command[-1] += '-DHARD'

    command = ' '.join(command)

    os.system(command)

    message = 'Runned performance test with ' + sw + ' switches and ' + rm + ' RMBCs'

    print(message)

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

    ansfile.close()
    outfile.close()



# Search for the projects folders.
# Creates them if they don't exist.
# try:
#     os.stat('bin')
# except:
#     os.mkdir('bin')

# try:
#     os.stat('obj')
# except:
#     os.mkdir('obj')

# # Command line arguments
# test = sys.argv[1] # Either 'performance' or 'penazzi'
# sample = sys.argv[2] # Graph selection


# if test == 'performance':

#     # Output and Answer directories.
#     out = 'out/performance'
#     ans = 'ans/performance'
#     inp = 'samples/performance/' + sample

#     # Search for the output folders.
#     # Creates them if they don't exist.
#     try:
#         os.stat(out)
#     except:
#         os.mkdir(out)
    
#     ans += '/' + sample
#     out += '/' + sample

#     try:
#         os.stat(out)
#     except:
#         os.mknod(out, 777)

#     # Command for performance test
#     command = ['make', test, 'SWITCH=', 'RMBC=', 'INPUT=', 'OUTPUT=']

#     answers = open(ans, 'r')
#     s, r = answers.readline().split()

#     args = [s, r, inp, out]

#     for i in range (2, 6):
#         command[i] += args[i - 2]
    
#     sh = ' '.join(command)
#     os.system(sh)

#     output = open(out, 'r')

#     message = 'Runned ' + test + ' test with ' + s + ' switches and ' + r + ' RMBCs'

#     print(message)

#     print('Time spent creating graph: ' + output.readline())
#     next(output)
#     print('Time spent running Natural: ' + output.readline())
#     next(output)
#     print('Time spent running Welsh: ' + output.readline())
#     next(output)
#     print('Time spent running Switch: ' + output.readline())
#     next(output)
#     print('Time spent running RMBC: ' + output.readline())
#     print('Time spent destroying graph: ' + output.readline())
#     print('Penazzi time: ' + answers.readline())
#     print('Your time: ' + output.readline())

#     answers.close()
#     output.close()

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
    if test == 'penazzi':
        penazzi(graph, options.diff)        
    elif test == 'performance':
        performance(graph, options.diff)
    elif test == 'memory':
        pass
    else:
        print("Wrong test name")
        print("Available tests are penazzi, performance and memory")
    
    exit(0)

if __name__ == '__main__':
    main()

