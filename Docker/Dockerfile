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
