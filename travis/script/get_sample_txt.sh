#!/bin/bash -ex

URL1="http://www.gutenberg.org/files/45/45-0.txt"
URL2="http://www.eresumes.com/download/eresumes_practice_erezsample_plaintext2.txt"
URL3="https://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-demo.txt"
URL4="https://textfiles.com/apple/ADC/adv.1988.index"
URL5="http://www.gutenberg.org/files/12345/12345-8.txt"
URL6="http://www.gutenberg.org/files/42/42.txt"

FILENAME="45-0.txt"

function shuffle () {
    RANDOM=$$
    declare -a ar=($@)
    declare -i k n=${#ar[@]}
    while [ $n -ge 0 ]; do
        let "k = RANDOM % (n + 1)"
        swap+=(${ar[$k]})
        ar[k]=${ar[$n]}
        ar[n]=$swap
        let "n--"
    done
    echo "${swap[0]}"
}

declare -a urls=`shuffle ${URL1} ${URL2} ${URL3}`

while [ ${#urls[@]} -ne 0 ]; do
    url=${urls[0]}
    unset urls[0]
    urls=(${urls[@]})
    result=`wget --spider -nv ${url} 2>&1 | grep -c '200 OK'`
    if [ ${result} -eq 1 ]; then
        wget -q -O ${FILENAME} ${url}
        break
    fi
done

if [ -e ${FILENAME} ]; then
    echo "Completed download"
    mv ${FILENAME} ../../tests/
else
    echo "All server downed"
fi
