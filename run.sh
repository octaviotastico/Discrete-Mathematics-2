
clear

while [ true ]; do

    printf "\n"
    echo "* T -> Run test"; printf "*\n"
    echo "* G -> Run graph"; printf "*\n"
    echo "* N -> Run own test"; printf "*\n"
    echo "* Q -> Quit"; printf "* \n"
    read -p "* " selection

    clear

    if [ "$selection" == 'T' ] || [ "$selection" == 't' ]; then
        echo "This are the avaible tests:"
        ls ./tests; printf "\n"
        read -p "Wich test would you like to run? " test
        ./test/"$test"

    elif [ "$selection" == 'G' ] || [ "$selection" == 'g' ]; then
        echo "This are the avaible graphs:"
        ls ./samples
        printf "\n"
        read -p "Wich graph would you like to run? " graph
        make general < ./samples/$graph

    elif [ "$selection" == 'N' ] || [ "$selection" == 'n' ]; then
            echo "Insert the graph you want to test:";
            echo "It has to have this format:"; printf "\n"
            echo "First line: 'p edge n m'";
            echo "Next m lines: 'e v1 v2'"; printf "\n"
            make general

    elif [ "$selection" == 'Q' ] || [ "$selection" == 'q' ]; then
        echo "Exiting"
        make clean
        exit 0

    else
        printf "\n"
        echo "That's not an option"
        printf "\n"

    fi

done