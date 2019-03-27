
clear

while [ true ]; do
    # Select test
    printf "* Available tests: ";
    ls -p ./tests | grep -v / | sed -e 's/\..*$//'
    printf "* Select test: "
    read -p "" test

    # Select sample
    printf "* Available samples: ";
    ls ./samples
    printf "* Select sample: ";
    read -p "" sample

    # Compile and run test with sample
    make $test <samples/$sample

    read -p "Press any key to continue..."

    clear
done