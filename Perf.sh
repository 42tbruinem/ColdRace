rm output.prof
sample coldrace 1000 1 -wait -mayDie -fullPaths -f output.prof | ./coldrace < "$@" > /dev/null ; filtercalltree output.prof