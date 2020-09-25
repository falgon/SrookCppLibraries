FROM gcc:7.3.0
SHELL ["/bin/bash", "-c"]
USER root
LABEL maintainer="Roki <falgon53@gmail.com>"
ARG cpuproc=1
ARG sde_url
ENV DEBCONF_NOWARNINGS yes
RUN apt-get -qq update \
    && apt-get -qq -y upgrade \
    && apt-get install --no-install-recommends -qq -y \
        cppcheck \
        make \
    && apt-get -qq -y autoremove \
    && rm -rf /var/lib/apt/lists/*
RUN wget -q --no-check-certificate $sde_url -O sdetool.tar.bz2 \
    && tar -jxf sdetool.tar.bz2 \
    && wget -q -O boost_1_65_1.tar.gz http://sourceforge.net/projects/boost/files/boost/1.65.1/boost_1_65_1.tar.gz/download \
    && tar xzf boost_1_65_1.tar.gz \
    && cd boost_1_65_1 \
    && ./bootstrap.sh \
    && ./b2 link=static,shared install -d0 -j1 --prefix=/proj --with-program_options \
    && mv /proj/include/boost /usr/local/include/ \
    && mv /proj/lib/* /usr/local/lib/ \
    && cd / \
    && rm -r boost_1_65_1 boost_1_65_1.tar.gz sdetool.tar.bz2
ENV LD_LIBRARY_PATH /usr/local/lib:$LD_LIBRARY_PATH

WORKDIR /proj/tests
CMD ["./tests.sh"]
