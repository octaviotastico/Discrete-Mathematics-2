# Imports
import sys
import os

# Search for the projects folders.
# Creates them if they don't exist.
try:
    os.stat('bin')
except:
    os.mkdir('bin')

try:
    os.stat('obj')
except:
    os.mkdir('obj')

# Command line arguments
test = sys.argv[1] # Either 'performance' or 'penazzi'
sample = sys.argv[2] # Graph selection

# Input file
inp = 'samples/' + sample

if test == 'performance':

    # Output and Answer directories.
    out = 'out/performance'
    ans = 'ans/performance'

    # Search for the output folders.
    # Creates them if they don't exist.
    try:
        os.stat(out)
    except:
        os.mkdir(out)
    
    try:
        os.stat(ans)
    except:
        os.mkdir(ans)
    
    ans += '/' + sample
    out += '/' + sample

    try:
        os.mknod(out, 777)
    except:
        pass

    # Command for performance test
    command = ['make', test, 'SWITCH=', 'RMBC=', 'INPUT=', 'OUTPUT=']

    answers = open(ans, 'r')
    s, r = answers.readline().split()

    args = [s, r, inp, out]

    for i in range (2, 6):
        command[i] += args[i - 2]
    
    sh = ' '.join(command)
    os.system(sh)

    output = open(out, 'r')

    message = 'Runned ' + test + ' test with ' + s + ' switches and ' + r + ' RMBCs'

    print(message)

    print('Time spent creating graph: ' + output.readline())
    next(output)
    print('Time spent running Natural: ' + output.readline())
    next(output)
    print('Time spent running Welsh: ' + output.readline())
    next(output)
    print('Time spent running Switch: ' + output.readline())
    next(output)
    print('Time spent running RMBC: ' + output.readline())
    print('Time spent destroying graph: ' + output.readline())
    print('Penazzi time: ' + answers.readline())
    print('Your time: ' + output.readline())

    answers.close()
    output.close()


if test == 'penazzi':

    # Output and Answer directories.
    out = 'out/penazzi'
    ans = 'ans/penazzi'

    # Search for the output folders.
    # Creates them if they don't exist.
    try:
        os.stat(out)
    except:
        os.mkdir(out)
    
    try:
        os.stat(ans)
    except:
        os.mkdir(ans)
    
    ans += '/' + sample
    out += '/' + sample

    print(ans)
    print(out)

    try:
        os.mknod(out, 777)
    except:
        pass

    # Command for penazzi test
    command = ['make', test, 'SWITCH=', 'RMBC=', 'INPUT=', 'OUTPUT=']
    args = [inp, out]

    answers = open(ans, 'r')
    s, r = answers.readline().split()

    args = [s, r] + args

    for i in range (2, 6):
        command[i] += args[i - 2]

    command = ' '.join(command)
    os.system(command)

    output = open(out, 'r')

    message = 'Runned ' + test + ' test with ' + s + ' switches and ' + r + ' RMBCs'

    print(message)
    
    ansline = answers.readline()
    outline = output.readline()

    checks = ['GREEDY\n', 'WELSH\n', 'SWITCH\n', 'RMBC\n']
    expected = []
    given = []
    while ansline and outline:
        expected.append(ansline)
        given.append(outline)
        ansline, outline = answers.readline(), output.readline()

    for i in range (0, 4):
        checks[i] += 'Expected: ' + expected[i] + 'Given: ' + given[i]

    checks = '\n'.join(checks)
    print(checks)

    answers.close()
    output.close()

else:
    print('Wrong test.')
