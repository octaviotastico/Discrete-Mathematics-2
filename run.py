import sys
import os

samdir = 'samples/'
try:
    os.stat(samdir)
except:
    os.mkdir(samdir)

outdir = 'out/'
try:
    os.stat(outdir)
except:
    os.mkdir(outdir)

ansdir = 'ans/'
try:
    os.stat(ansdir)
except:
    os.mkdir(ansdir)

# Command line arguments test and sample
test = sys.argv[1]
sample = sys.argv[2]

# Three important files
inp = samdir + sample
out = outdir + sample
ans = ansdir + sample

if 'performance' in test:
    # Command for performance test
    command = ['make', test, 'INPUT=', 'OUTPUT=']
    args = [inp, out]

    command[2] += args[0]
    command[3] += args[1]
    
    sh = ' '.join(command)
    os.system(sh)

    output = open(out, 'r')

    message = 'Runned ' + test + ' test'
    print("\n" + message + "\n")

    print('Time spent creating graph: ' + output.readline())
    next(output)
    print('Time spent running Natural: ' + output.readline())
    next(output)
    print('Time spent running Welsh: ' + output.readline())
    next(output)
    print('Time spent running Switch: ' + output.readline())
    next(output)
    print('Time spent running RMBC: ' + output.readline())


if 'penazzi' in test:
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
