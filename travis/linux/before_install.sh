#!/bin/bash -ex

if [ "$TRAVIS_OS_NAME" = "linux" ]; then 
    sudo apt-get remove -qq -y postgresql-9.1 postgresql-9.2 postgresql-9.3 postgresql-9.4 postgresql-9.6 postgresql-contrib-9.6 google-chrome-stable
    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 6B05F25D762E3157
    sudo apt-get -qq -y update
    sudo add-apt-repository -r ppa:webupd8team/java -y
    sudo apt-get -qq upgrade -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" --allow-unauthenticated
    sudo apt-get -qq dist-upgrade -y --allow-unauthenticated
    export CPU_NUM=$(egrep -c "^processor\s:\s[0-9]+$" /proc/cpuinfo);
fi
