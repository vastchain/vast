FROM everitoken/builder:latest as builder
ARG branch=master
ARG rootkey
ARG bjobs=$(nproc)
ARG awskey
ARG awssecret

RUN git clone -b $branch https://github.com/vastchain/vast.git --recursive \
    && cd vast && echo "$branch:$(git rev-parse HEAD)" > /etc/vast-version \
    && cmake -H. -B"/tmp/build" -G"Ninja" \
       -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/tmp/build \
       -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ \
       -DCMAKE_AR=/usr/bin/gcc-ar -DCMAKE_RANLIB=/usr/bin/gcc-ranlib \
       -DSecp256k1_ROOT_DIR=/usr/local \
       -DENABLE_POSTGRES_SUPPORT=ON -DENABLE_BREAKPAD_SUPPORT=ON -DENABLE_BUILD_LTO=OFF  \
       -DVAST_ROOT_KEY=$rootkey
RUN ninja -C /tmp/build -j $bjobs vastd vastwd vastc && ninja -C /tmp/build install

RUN echo 'APT::Install-Recommends 0;' >> /etc/apt/apt.conf.d/01norecommends \
    && echo 'APT::Install-Suggests 0;' >> /etc/apt/apt.conf.d/01norecommends \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y python3 python3-click python3-boto3

RUN mkdir /tmp/build/symbols

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

RUN python3 /vast/scripts/symbol_ops.py export -s /tmp/build/symbols /tmp/build/bin/vastd
RUN python3 /vast/scripts/symbol_ops.py export -s /tmp/build/symbols /tmp/build/bin/vastc
RUN python3 /vast/scripts/symbol_ops.py export -s /tmp/build/symbols /tmp/build/bin/vastwd

RUN python3 /vast/scripts/symbol_ops.py upload -f /tmp/build/symbols -k $awskey -s $awssecret -r vast -b vast-symbols

FROM debian:buster-slim

RUN apt-get update && DEBIAN_FRONTEND=noninteractive && apt-get install -y openssl libssl1.1 libllvm7 && rm -rf /var/lib/apt/lists/*

COPY --from=builder /usr/local/lib/* /usr/local/lib/
COPY --from=builder /tmp/build/bin /opt/vast/bin
COPY --from=builder /etc/vast-version /etc
COPY --from=builder /vast/LICENSE.txt /opt/vast/

COPY config.ini /
COPY vastd.sh  /opt/vast/bin/vastd.sh
COPY vastwd.sh /opt/vast/bin/vastwd.sh
RUN  chmod +x /opt/vast/bin/vastd.sh
RUN  chmod +x /opt/vast/bin/vastwd.sh

ENV VAST_ROOT=/opt/vast
ENV LD_LIBRARY_PATH /usr/local/lib

RUN mkdir /opt/vast/data
VOLUME /opt/vast/data

RUN mkdir /opt/vast/snapshots
VOLUME /opt/vast/snapshots

ENV PATH /opt/vast/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
