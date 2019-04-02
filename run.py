import sys
import os

try:
    os.stat('bin')
except:
    os.mkdir('bin')

try:
    os.stat('obj')
except:
    os.mkdir('obj')

outdir = 'out/'
try:
    os.stat(outdir)
except:
    os.mkdir(outdir)

ansdir = 'ans/'


# Command line arguments test and sample
test = sys.argv[1]
sample = sys.argv[2]

_, dest = sample.split('/', 1)

# Three important files
inp = sample
out = outdir + dest
ans = ansdir + dest

try:
    os.stat(out)
except:
    os.touch(out)

if 'performance' in test:
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
