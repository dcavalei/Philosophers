#	!/bin/bash
args=("$@")
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ${args[0]} ${args[1]} ${args[2]} ${args[3]} ${args[4]} ${args[5]}