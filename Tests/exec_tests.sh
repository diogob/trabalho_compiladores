#bin/bash 

for i in $( ls teste_ll1*txt ); do
    echo      
    echo "FILE  ->  $i"
    echo "INPUT -> $(cat $i)"
    ./pico $i
    echo 
done

